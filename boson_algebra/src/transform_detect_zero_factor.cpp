//MY HEADER:
#include <boson_algebra/transform_detect_zero_factor.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_detect_zero_factor(const ExpressionHandler& expression) {
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto expression_factor = expression.casted_target<IntegerFactoredExpression>().factor();
    const auto& subexpression = expression.subexpression(0);
    const auto is_expression_factor_zero = (expression_factor == 0);
    const auto is_subexpression_zero = subexpression.is_of_type<SumExpression>() && subexpression.casted_target<SumExpression>().is_zero();
    if ((!is_subexpression_zero) && (!is_expression_factor_zero)) {
        return std::nullopt;
    }
    return SumExpression::make_zero();
}

}  // namespace boson_algebra