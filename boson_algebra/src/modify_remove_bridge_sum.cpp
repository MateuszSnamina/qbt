// MY HEADER:
#include <boson_algebra/modify_remove_bridge_sum.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
#include <boson_algebra/modify_remove_bridge_numerous_expression.hpp>

namespace boson_algebra {

ModificationResult modify_remove_bridge_sum_new_api(ExpressionHandler&& expression) {
    return modify_remove_bridge_numerous_expression_new_api<SumExpression>(std::move(expression));
}

}  // namespace boson_algebra