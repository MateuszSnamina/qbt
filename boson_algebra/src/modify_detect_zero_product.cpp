// MY HEADER:
#include <boson_algebra/modify_detect_zero_product.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/range/algorithm/find_if.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_detect_zero_product(const ExpressionHandler& expression) {
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression.crange();
    const auto subproduct_iter = boost::find_if(range, [](const ExpressionHandler& expression) {
        return expression.is_of_type<SumExpression>() && expression.casted_target<SumExpression>().unwrap().get().is_zero();
    });
    if (subproduct_iter == boost::end(range)) {
        return std::nullopt;
    }
    return SumExpression::make_zero();
}

ModificationResult modify_detect_zero_product_new_api(ExpressionHandler&& expression) {
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto& range = expression.crange();
    const auto subproduct_iter = boost::find_if(range, [](const ExpressionHandler& expression) {
        return expression.is_of_type<SumExpression>() && expression.casted_target<SumExpression>().unwrap().get().is_zero();
    });
    if (subproduct_iter == boost::end(range)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    return ModificationResult::make_generated_result(SumExpression::make_zero());
}

}  // namespace boson_algebra