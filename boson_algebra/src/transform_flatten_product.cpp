//MY HEADER:
#include <boson_algebra/transform_flatten_product.hpp>
//SELF:
#include <boson_algebra/transform_simplify_flatten.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_flatten_product(const ExpressionHandler& expression) {
    return transform_simplify_flatten<ProductExpression>(expression);
}

}  // namespace boson_algebra