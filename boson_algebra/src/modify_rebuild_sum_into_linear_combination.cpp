// MY HEADER:
#include <boson_algebra/modify_rebuild_sum_into_linear_combination.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
// STD:
#include <numeric>

namespace boson_algebra {

ModificationResult modify_rebuild_sum_into_linear_combination(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to sum expressions       **
    // ***************************************************************
    if (!expression.is_of_type<SumExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    // ***************************************************************
    // *** the transformation applies only to sun expressions       **
    // *** with ingredients not already arranged to be              **
    // *** a linear combination                                     **
    // ***************************************************************
    const auto is_integer_factored_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<IntegerFactoredExpression>();
    };
    const bool are_all_subexpression_factors =
        boost::algorithm::all_of(range, is_integer_factored_expression);
    if (are_all_subexpression_factors) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    for (auto& subexpression : range) {
        if (subexpression.is_of_type<IntegerFactoredExpression>()) {
            new_subexpressions.push_back(std::move(subexpression));
        } else {
            new_subexpressions.push_back(IntegerFactoredExpression::make(1, std::move(subexpression)));
        }
    }
    // ***************************************************************
    // *** return the sum expression with subexpressions            **
    // *** arranged to be like in a linear combination              **
    // ***************************************************************
    auto linear_combination_expression = SumExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(linear_combination_expression));
}

}  // namespace boson_algebra