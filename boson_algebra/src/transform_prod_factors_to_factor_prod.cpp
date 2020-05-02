// MY HEADER:
#include <boson_algebra/transform_prod_factors_to_factor_prod.hpp>
// SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <numeric>

namespace boson_algebra {

ExpressionHandlerOptional transform_prod_factors_to_factor_prod(const ExpressionHandler& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression.crange();
    // ***************************************************************
    // *** the transformation applies only if                       **
    // *** there is at least one factor being                       **
    // *** of IntegerFactoredExpression type                        **
    // ***************************************************************
    const auto is_integer_factored_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<IntegerFactoredExpression>();
    };
    const bool are_any_subexpression_factors =
        boost::algorithm::any_of(range, is_integer_factored_expression);
    if (!are_any_subexpression_factors) {
        return std::nullopt;
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    long long accumulated_factor = 1;
    for (const auto& subexpression : range) {
        if (subexpression.is_of_type<IntegerFactoredExpression>()) {
            accumulated_factor *= subexpression.casted_target<IntegerFactoredExpression>().unwrap().get().factor();
            new_subexpressions.push_back(subexpression.subexpression(0).clone());
        } else {
            new_subexpressions.push_back(subexpression.clone());
        }
    }
    // ***************************************************************
    // *** return the factored product                              **
    // ***************************************************************
    auto new_prod = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    return IntegerFactoredExpression::make(accumulated_factor, std::move(new_prod));
}

}  // namespace boson_algebra