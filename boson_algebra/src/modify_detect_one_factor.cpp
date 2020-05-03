// MY HEADER:
#include <boson_algebra/modify_detect_one_factor.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_detect_one_factor(const ExpressionHandler& expression) {
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto expression_factor = expression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
    const auto& subexpression = expression.subexpression(0);
    const auto is_expression_factor_one = (expression_factor == 1);
    if (!is_expression_factor_one) {
        return std::nullopt;
    }
    return subexpression.clone();
}

ModificationResult modify_detect_one_factor_new_api(ExpressionHandler&& expression) {
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto expression_factor = expression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
    auto subexpression = std::move(expression.subexpression(0));
    const auto is_expression_factor_one = (expression_factor == 1);
    if (!is_expression_factor_one) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    return ModificationResult::make_generated_result(std::move(subexpression));
}

}  // namespace boson_algebra