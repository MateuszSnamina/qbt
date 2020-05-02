// MY HEADER:
#include <boson_algebra/transform_detect_bridge_sum.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
#include <boson_algebra/transform_detect_bridge_numerous_expression.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_detect_bridge_sum(const ExpressionHandler& expression) {
    return transform_detect_bridge_numerous_expression<SumExpression>(expression);
}

}  // namespace boson_algebra