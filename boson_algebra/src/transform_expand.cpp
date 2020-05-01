//MY HEADER:
#include <boson_algebra/transform_expand.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/range/algorithm.hpp>
#include <boost/range/sub_range.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_expand(const ExpressionHandler& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression.crange();
    const auto& range_begin = boost::begin(range);
    const auto& range_end = boost::end(range);
    // ***************************************************************
    // *** the transformation applies only if                       **
    // *** there is at least one factor being                       **
    // *** of SumExpression type                                    **
    // ***************************************************************
    const auto is_sum_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<SumExpression>();
    };
    const auto subproduct_iter = boost::find_if(range, is_sum_expression);
    if (subproduct_iter == range_end) {
        return std::nullopt;
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    using ConstExpressionHandlerSinglePassSubRange = boost::sub_range<ConstExpressionHandlerSinglePassRange>;
    const ConstExpressionHandlerSinglePassSubRange range1(range_begin, subproduct_iter);
    const ConstExpressionHandlerSinglePassSubRange range2(subproduct_iter + 1, range_end);
    const auto& subproduct = *subproduct_iter;
    const auto subproduct_range = subproduct.crange();
    ExpressionHandlerVector new_subexpressions;
    for (const auto& subsubexpression : subproduct_range) {
        ExpressionHandlerVector new_subsubexpressions;
        for (auto& subexpression : range1) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subsubexpressions.push_back(subsubexpression.clone());
        for (auto& subexpression : range2) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subexpressions.push_back(ProductExpression::make(std::move(new_subsubexpressions)));
    }
    // ***************************************************************
    // *** return the expression in the expanded form               **
    // ***************************************************************
    return SumExpression::make(std::move(new_subexpressions));
}

}  // namespace boson_algebra