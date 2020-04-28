//MY HEADER:
#include <boson_algebra/transform_detect_zero_factor.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_detect_zero_factor(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto expression_factor = expression_hdl.casted_target<IntegerFactoredExpression>().factor();
    const auto& subexpression_hdl = expression_hdl.target().subexpression(0);
    const auto is_expression_factor_zero = (expression_factor == 0);
    const auto is_subexpression_zero = subexpression_hdl.is_of_type<SumExpression>() && subexpression_hdl.casted_target<SumExpression>().is_zero();
    if ((!is_subexpression_zero) && (!is_expression_factor_zero)) {
        return std::nullopt;
    }
    return SumExpression::make_zero();
}

}  // namespace boson_algebra