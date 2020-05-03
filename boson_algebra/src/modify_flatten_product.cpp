// MY HEADER:
#include <boson_algebra/modify_flatten_product.hpp>
// SELF:
#include <boson_algebra/modify_flatten_numerous_expression.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_flatten_product(const ExpressionHandler& expression) {
    return modify_flatten_numerous_expression<ProductExpression>(expression);
}

ModificationResult modify_flatten_product_new_api(ExpressionHandler&& expression){
    return modify_flatten_numerous_expression_new_api<ProductExpression>(std::move(expression));
}

}  // namespace boson_algebra