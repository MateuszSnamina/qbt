// MY HEADER:
#include <boson_algebra/modify_remove_bridge_product.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
#include <boson_algebra/modify_remove_bridge_numerous_expression.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_remove_bridge_product(const ExpressionHandler& expression) {
    return modify_remove_bridge_numerous_expression<ProductExpression>(expression);
}

}  // namespace boson_algebra