//MY HEADER:
#include <boson_algebra/transform_simplify_product.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
//BOOST:
#include <boost/range/algorithm.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_simplify_product(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.target().crange();
    const auto& range_begin = boost::begin(range);
    const auto& range_end = boost::end(range);
    const auto subproduct_hdl_iter = boost::find_if(range, [](const ExpressionHandler& expression_hdl) {
        return expression_hdl.is_of_type<ProductExpression>();
    });
    if (subproduct_hdl_iter == range_end) {
        return std::nullopt;
    }
    ExpressionHandlerVector v;
    for (const auto& subexpression_hdl : expression_hdl.target().crange()) {
        if (subexpression_hdl.is_of_type<ProductExpression>()) {
            for (const auto& subsubexpression_hdl : subexpression_hdl.target().crange()) {
                v.emplace_back(std::move(subsubexpression_hdl.clone()));
            }
        } else {
            v.emplace_back(std::move(subexpression_hdl.clone()));
        }
    }
    ExpressionHandler product = ProductExpression::make(std::move(v));
    return std::move(product);
}

// ExpressionHandlerOptional transform_simplify_product_one(const ExpressionHandler& expression_hdl) {
//     if (!expression_hdl.is_of_type<ProductExpression>()) {
//         return std::nullopt;
//     }
//     const auto& range = expression_hdl.target().crange();
//     const auto& range_begin = boost::begin(range);
//     const auto& range_end = boost::end(range);
//     const auto subproduct_hdl_iter = boost::find_if(range, [](const ExpressionHandler& expression_hdl) {
//         return expression_hdl.is_of_type<ProductExpression>();
//     });
//     if (subproduct_hdl_iter == range_end) {
//         return std::nullopt;
//     }
//     const auto& subproduct_expr_hdl = *subproduct_hdl_iter;
//     ConstExpressionHandlerRandomAccessRange range1{range_begin, subproduct_hdl_iter};
//     ConstExpressionHandlerRandomAccessRange range2{subproduct_expr_hdl.target().crange()};
//     ConstExpressionHandlerRandomAccessRange range3{subproduct_hdl_iter + 1, range_end};
//     ExpressionHandlerVector v;
//     for (const auto& subexpression_hdl : range1) {
//         v.emplace_back(std::move(subexpression_hdl.clone()));
//     }
//     for (const auto& subexpression_hdl : range2) {
//         v.emplace_back(std::move(subexpression_hdl.clone()));
//     }
//     for (const auto& subexpression_hdl : range3) {
//         v.emplace_back(std::move(subexpression_hdl.clone()));
//     }
//     ExpressionHandler product = ProductExpression::make(std::move(v));
//     return std::move(product);
// }

}  // namespace boson_algebra