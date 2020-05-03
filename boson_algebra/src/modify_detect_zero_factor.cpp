// MY HEADER:
#include <boson_algebra/modify_detect_zero_factor.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ModificationResult modify_detect_zero_factor_new_api(ExpressionHandler&& expression) {
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));;
    }
    const auto expression_factor = expression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
    const auto& subexpression = expression.subexpression(0);
    const auto is_expression_factor_zero = (expression_factor == 0);
    const auto is_subexpression_zero = subexpression.is_of_type<SumExpression>() && subexpression.casted_target<SumExpression>().unwrap().get().is_zero();
    if ((!is_subexpression_zero) && (!is_expression_factor_zero)) {
        return ModificationResult::make_passed_through_result(std::move(expression));;
    }
    return ModificationResult::make_generated_result(SumExpression::make_zero());
}

}  // namespace boson_algebra