// MY HEADER:
#include <boson_algebra/transform_flatten_sum.hpp>
// SELF:
#include <boson_algebra/transform_flatten_numerous_expression.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_flatten_sum(const ExpressionHandler& expression) {
    return transform_flatten_numerous_expression<SumExpression>(expression);
}

}  // namespace boson_algebra