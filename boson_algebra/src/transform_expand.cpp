//MY HEADER:
#include <boson_algebra/transform_simplify_product.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/range/algorithm.hpp>
#include <boost/range/sub_range.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_expand(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.crange();
    const auto& range_begin = boost::begin(range);
    const auto& range_end = boost::end(range);
    const auto subproduct_hdl_iter = boost::find_if(range, [](const ExpressionHandler& expression_hdl) {
        return expression_hdl.is_of_type<SumExpression>();
    });
    if (subproduct_hdl_iter == range_end) {
        return std::nullopt;
    }
    using ConstExpressionHandlerSinglePassSubRange = boost::sub_range<ConstExpressionHandlerSinglePassRange>;
    const ConstExpressionHandlerSinglePassSubRange range1(range_begin, subproduct_hdl_iter);
    const ConstExpressionHandlerSinglePassSubRange range2(subproduct_hdl_iter + 1, range_end);
    const auto& subproduct_hdl = *subproduct_hdl_iter;
    const auto subproduct_range = subproduct_hdl.crange();
    ExpressionHandlerVector new_subexpressions;
    for (const auto& subsubexpression_hdl : subproduct_range) {
        ExpressionHandlerVector new_subsubexpressions;
        for (auto& subexpression_hdl : range1) {
            new_subsubexpressions.push_back(subexpression_hdl.clone());
        }
        new_subsubexpressions.push_back(subsubexpression_hdl.clone());
        for (auto& subexpression_hdl : range2) {
            new_subsubexpressions.push_back(subexpression_hdl.clone());
        }
        new_subexpressions.push_back(ProductExpression::make(std::move(new_subsubexpressions)));
    }
    return SumExpression::make(std::move(new_subexpressions));
}

}  // namespace boson_algebra