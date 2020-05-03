// MY HEADER:
#include <boson_algebra/modify_flatten_factor.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_flatten_factor(const ExpressionHandler& expression) {
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto& subexpression = expression.target().subexpression(0);
    if (!subexpression.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto& subsubexpression = subexpression.target().subexpression(0);
    const auto expression_factor = expression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
    const auto subexpression_factor =  subexpression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
    return IntegerFactoredExpression::make(expression_factor*subexpression_factor, subsubexpression.clone());
}

}  // namespace boson_algebra