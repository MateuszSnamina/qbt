// MY HEADER:
#include <boson_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <numeric>

namespace boson_algebra {

ModificationResult modify_rebuild_prod_factors_into_factor_prod_new_api(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.range();
    // ***************************************************************
    // *** the transformation applies only if                       **
    // *** there is at least one factor being                       **
    // *** of IntegerFactoredExpression type                        **
    // ***************************************************************
    const auto is_integer_factored_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<IntegerFactoredExpression>();
    };
    const bool are_any_subexpression_factors =
        boost::algorithm::any_of(range, is_integer_factored_expression);
    if (!are_any_subexpression_factors) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    long long accumulated_factor = 1;
    for (auto& subexpression : range) {
        if (subexpression.is_of_type<IntegerFactoredExpression>()) {
            accumulated_factor *= subexpression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
            new_subexpressions.push_back(std::move(subexpression.subexpression(0)));
        } else {
            new_subexpressions.push_back(std::move(subexpression));
        }
    }
    // ***************************************************************
    // *** return the factored product                              **
    // ***************************************************************
    auto new_prod = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    auto new_factor_product = IntegerFactoredExpression::make(accumulated_factor, std::move(new_prod));
    return ModificationResult::make_generated_result(std::move(new_factor_product));
}

}  // namespace boson_algebra