//MY HEADER:
#include <boson_algebra/transform_detect_one_factor.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_detect_one_factor(const ExpressionHandler& expression) {
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto expression_factor = expression.casted_target<IntegerFactoredExpression>().factor();
    const auto& subexpression = expression.subexpression(0);
    const auto is_expression_factor_one = (expression_factor == 1);
    if (!is_expression_factor_one) {
        return std::nullopt;
    }
    return subexpression.clone();
}

}  // namespace boson_algebra