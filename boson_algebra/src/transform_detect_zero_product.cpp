// MY HEADER:
#include <boson_algebra/transform_detect_zero_product.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/range/algorithm/find_if.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_detect_zero_product(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.crange();
    const auto subproduct_hdl_iter = boost::find_if(range, [](const ExpressionHandler& expression_hdl) {
        return expression_hdl.is_of_type<SumExpression>() && expression_hdl.casted_target_new_api<SumExpression>().unwrap().get().is_zero();
    });
    if (subproduct_hdl_iter == boost::end(range)) {
        return std::nullopt;
    }
    return SumExpression::make_zero();
}

}  // namespace boson_algebra