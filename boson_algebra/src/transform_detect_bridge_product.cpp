//MY HEADER:
#include <boson_algebra/transform_detect_bridge_product.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_detect_bridge_product(const ExpressionHandler& expression) {
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto is_bridge = (expression.n_subexpressions() == 1);
    if (!is_bridge) {
        return std::nullopt;
    }
    const auto& subexpression = expression.subexpression(0);
    return subexpression.clone();
}

}  // namespace boson_algebra