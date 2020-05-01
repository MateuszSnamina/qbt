// MY HEADER:
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_0.hpp>
// SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm/stable_sort.hpp>
#include <boost/range/algorithm/transform.hpp>
// STD
//#include <iostream>  // debug
#include <iterator>

namespace boson_algebra {

ExpressionHandlerOptional transform_sort_product_of_boson_primitive_operators_0(const ExpressionHandler& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** with factors being of BosonPrimitiveOperators type       **
    // ***************************************************************
    const auto is_boson_primitive_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonPrimitiveOperators>();
    };
    const auto& range = expression.crange();
    if (!boost::algorithm::all_of(range, is_boson_primitive_operator)) {
        return std::nullopt;
    }
    // ***************************************************************
    // ***  stable sort of the operators                            **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    boost::transform(range, std::back_inserter(new_subexpressions), [](const ExpressionHandler& _) { return _.clone(); });
    const auto sort_predicate = [](const ExpressionHandler& lhs_exp, const ExpressionHandler& rhs_exp) {
        const auto& lhs_boson = lhs_exp.casted_target<BosonPrimitiveOperators>().boson();
        const auto& rhs_boson = rhs_exp.casted_target<BosonPrimitiveOperators>().boson();
        return lhs_boson->id() < rhs_boson->id();
    };
    boost::stable_sort(new_subexpressions, sort_predicate);
    // ***************************************************************
    // *** return the product of sorted operators                   **
    // ***************************************************************
    return ProductExpression::make(std::move(new_subexpressions));
}

}  // namespace boson_algebra