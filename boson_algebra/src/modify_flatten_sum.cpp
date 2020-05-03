// MY HEADER:
#include <boson_algebra/modify_flatten_sum.hpp>
// SELF:
#include <boson_algebra/modify_flatten_numerous_expression.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_flatten_sum(const ExpressionHandler& expression) {
    return modify_flatten_numerous_expression<SumExpression>(expression);
}

ModificationResult modify_flatten_sum_new_api(ExpressionHandler&& expression){
    return modify_flatten_numerous_expression_new_api<SumExpression>(std::move(expression));
}

}  // namespace boson_algebra