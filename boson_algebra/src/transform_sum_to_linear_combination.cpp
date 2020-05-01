//MY HEADER:
#include <boson_algebra/transform_sum_to_linear_combination.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
//BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
//STD:
#include <numeric>

namespace boson_algebra {

ExpressionHandlerOptional transform_sum_to_linear_combination(const ExpressionHandler& expression) {
    // ***************************************************************
    // *** the transformation applies only to sum expressions       **
    // ***************************************************************
    if (!expression.is_of_type<SumExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression.crange();
    // ***************************************************************
    // *** the transformation applies only to sun expressions       **
    // *** with ingredients not already arranged to be              **
    // *** a linear combination                                     **
    // ***************************************************************
    const auto is_integer_factored_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<IntegerFactoredExpression>();
    };
    const bool are_all_subexpression_factors =
        boost::algorithm::all_of(range, is_integer_factored_expression);
    if (are_all_subexpression_factors) {
        return std::nullopt;
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    for (const auto& subexpression : range) {
        if (subexpression.is_of_type<IntegerFactoredExpression>()) {
            new_subexpressions.push_back(subexpression.clone());
        } else {
            new_subexpressions.push_back(IntegerFactoredExpression::make(1, subexpression.clone()));
        }
    }
    // ***************************************************************
    // *** return the sum expression with subexpressions            **
    // *** arranged to be like in a linear combination              **
    // ***************************************************************
    return SumExpression::make(std::move(new_subexpressions));
}

}  // namespace boson_algebra