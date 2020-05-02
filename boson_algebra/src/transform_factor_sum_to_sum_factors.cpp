// MY HEADER:
#include <boson_algebra/transform_factor_sum_to_sum_factors.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <numeric>

namespace boson_algebra {

ExpressionHandlerOptional transform_factor_sum_to_sum_factors(const ExpressionHandler& expression) {
    // ***************************************************************
    // *** the transformation applies only to                       **
    // *** IntegerFactoredExpression expressions                    **
    // ***************************************************************
    if (!expression.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto& subexpression = expression.subexpression(0);
    const auto factor = expression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
    // ***************************************************************
    // *** the transformation applies only when                     **
    // *** the subexpression is SumExpression                       **
    // ***************************************************************
    if (!subexpression.is_of_type<SumExpression>()) {
        return std::nullopt;
    }
    const auto& range = subexpression.crange();
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    for (const auto& subsubexpression : range) {
        auto new_subexpression = IntegerFactoredExpression::make(factor, subsubexpression.clone());
        new_subexpressions.push_back(std::move(new_subexpression));
    }
    // ***************************************************************
    // *** return the expanded expression                           **
    // ***************************************************************
    return SumExpression::make_from_buffer(std::move(new_subexpressions));
}

}  // namespace boson_algebra