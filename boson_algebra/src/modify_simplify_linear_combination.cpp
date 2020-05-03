// MY HEADER:
#include <boson_algebra/modify_simplify_linear_combination.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
// STD:
#include <numeric>

namespace boson_algebra {

ModificationResult modify_simplify_linear_combination_new_api(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to sum expressions       **
    // ***************************************************************
    if (!expression.is_of_type<SumExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** of factors being of IntegerFactoredExpression type       **
    // ***************************************************************
    const bool are_all_subexpression_factors =
        boost::algorithm::all_of(range, [](const ExpressionHandler& expression) {
            return expression.is_of_type<IntegerFactoredExpression>();
        });
    if (!are_all_subexpression_factors) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** build new ingrediends with theaccumulated factors        **
    // ***************************************************************
    std::list<std::size_t> indices(expression.n_subexpressions());
    std::iota(indices.begin(), indices.end(), 0);
    ExpressionHandlerVector new_subexpressions;
    while (!indices.empty()) {
        const auto processed_idx = indices.front();
        auto& processed_subexpression = expression.subexpression(processed_idx);
        auto& processed_subsubexpression = processed_subexpression.subexpression(0);
        long accumulated_factor = 0l;
        auto it = indices.begin();
        while (it != indices.end()) {
            const auto& subexpression = expression.subexpression(*it);
            const auto& subsubexpression = subexpression.subexpression(0);
            if (processed_subsubexpression.equals(subsubexpression)) {
                accumulated_factor += subexpression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
                it = indices.erase(it);
            } else {
                it++;
            }
        }
        auto new_subsubexpression = std::move(processed_subsubexpression);
        auto new_subexpression = IntegerFactoredExpression::make(accumulated_factor, std::move(new_subsubexpression));
        new_subexpressions.push_back(std::move(new_subexpression));
    }
    // ***************************************************************
    // *** return the simplified sum                                **
    // ***************************************************************
    auto linear_combination_expression = SumExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(linear_combination_expression));
}

}  // namespace boson_algebra