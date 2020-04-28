//MY HEADER:
#include <boson_algebra/transform_flatten_product.hpp>
//SELF:
#include <boson_algebra/transform_simplify_flatten.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_flatten_product(const ExpressionHandler& expression_hdl) {
    return transform_simplify_flatten<ProductExpression>(expression_hdl);
}

}  // namespace boson_algebra