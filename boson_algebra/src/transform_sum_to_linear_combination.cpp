//MY HEADER:
#include <boson_algebra/transform_sum_to_linear_combination.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
//BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
//STD:
#include <numeric>

namespace boson_algebra {

ExpressionHandlerOptional transform_sum_to_linear_combination(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<SumExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.crange();
    const bool are_all_subexpression_factors =
        boost::algorithm::all_of(range, [](const ExpressionHandler& expression_hdl) {
            return expression_hdl.is_of_type<IntegerFactoredExpression>();
        });
    if (are_all_subexpression_factors) {
        return std::nullopt;
    }
    ExpressionHandlerVector new_subexpressions;
    for (const auto& subexpression : range) {
        if (subexpression.is_of_type<IntegerFactoredExpression>()) {
            new_subexpressions.push_back(subexpression.clone());
        } else {
            new_subexpressions.push_back(IntegerFactoredExpression::make(1, subexpression.clone()));
        }
    }
    return SumExpression::make(std::move(new_subexpressions));
}

}  // namespace boson_algebra