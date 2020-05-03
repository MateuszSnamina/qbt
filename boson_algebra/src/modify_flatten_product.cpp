// MY HEADER:
#include <boson_algebra/modify_flatten_product.hpp>
// SELF:
#include <boson_algebra/modify_flatten_numerous_expression.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ModificationResult modify_flatten_product(ExpressionHandler&& expression){
    return modify_flatten_numerous_expression<ProductExpression>(std::move(expression));
}

}  // namespace boson_algebra