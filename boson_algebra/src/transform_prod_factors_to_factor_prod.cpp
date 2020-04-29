//MY HEADER:
#include <boson_algebra/transform_prod_factors_to_factor_prod.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
//BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
//STD:
#include <numeric>

namespace boson_algebra {

ExpressionHandlerOptional transform_prod_factors_to_factor_prod(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.crange();
    const bool are_any_subexpression_factors =
        boost::algorithm::any_of(range, [](const ExpressionHandler& expression_hdl) {
            return expression_hdl.is_of_type<IntegerFactoredExpression>();
        });
    if (!are_any_subexpression_factors) {
        return std::nullopt;
    }
    ExpressionHandlerVector new_subexpressions;
    long long accumulated_factor = 1;
    for (const auto& subexpression : range) {
        if (subexpression.is_of_type<IntegerFactoredExpression>()) {
            accumulated_factor *= subexpression.casted_target<IntegerFactoredExpression>().factor();
            new_subexpressions.push_back(subexpression.casted_target<IntegerFactoredExpression>().subexpression(0).clone());
        } else {
            new_subexpressions.push_back(subexpression.clone());
        }
    }
    auto new_prod = ProductExpression::make(std::move(new_subexpressions));
    return IntegerFactoredExpression::make(accumulated_factor, std::move(new_prod));
}

}  // namespace boson_algebra