// MY HEADER:
#include <boson_algebra/modify_sort_product_of_boson_primitive_operators_0.hpp>
// SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm/stable_sort.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>// DOTO fast exit when already sorted.
// STD
//#include <iostream>  // debug
#include <iterator>

namespace boson_algebra {

ExpressionHandlerOptional modify_sort_product_of_boson_primitive_operators_0(const ExpressionHandler& expression) {
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
    // ***  the boson driven operators sort predictate              **
    // ***************************************************************
    const auto sort_predicate = [](const ExpressionHandler& lhs_exp, const ExpressionHandler& rhs_exp) {
        const auto& lhs_boson = lhs_exp.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
        const auto& rhs_boson = rhs_exp.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
        return lhs_boson->id() < rhs_boson->id();
    };
    // ***************************************************************
    // ***  the transformation applies only                         **
    // ***  if the operators are not already sorted                 **
    // ***************************************************************
    // TODO:
    // if(boost::is_sorted(range, sort_predicate)){
    //  return std::nullopt;
    //}

    // ***************************************************************
    // ***  stable sort of the operators                            **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    boost::transform(range, std::back_inserter(new_subexpressions), [](const ExpressionHandler& _) { return _.clone(); });
    boost::stable_sort(new_subexpressions, sort_predicate);
    // ***************************************************************
    // *** return the product of sorted operators                   **
    // ***************************************************************
    return ProductExpression::make_from_buffer(std::move(new_subexpressions));
}

ModificationResult modify_sort_product_of_boson_primitive_operators_0_new_api(ExpressionHandler&& expression){
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** with factors being of BosonPrimitiveOperators type       **
    // ***************************************************************
    const auto is_boson_primitive_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonPrimitiveOperators>();
    };
    const auto& range = expression.range();
    if (!boost::algorithm::all_of(range, is_boson_primitive_operator)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // ***  the boson driven operators sort predictate              **
    // ***************************************************************
    const auto sort_predicate = [](const ExpressionHandler& lhs_exp, const ExpressionHandler& rhs_exp) {
        const auto& lhs_boson = lhs_exp.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
        const auto& rhs_boson = rhs_exp.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
        return lhs_boson->id() < rhs_boson->id();
    };
    // ***************************************************************
    // ***  the transformation applies only                         **
    // ***  if the operators are not already sorted                 **
    // ***************************************************************
    // TODO:
    // if(boost::is_sorted(range, sort_predicate)){
    //  return std::nullopt;
    //}
    // ***************************************************************
    // ***  stable sort of the operators                            **
    // ***************************************************************
    ExpressionHandlerVector new_subexpressions;
    for (auto& subexpressions : range){
        new_subexpressions.push_back(std::move(subexpressions));
    }
    //boost::transform(range, std::back_inserter(new_subexpressions), [](const ExpressionHandler& _) { return _.clone(); });
    boost::stable_sort(new_subexpressions, sort_predicate);
    // ***************************************************************
    // *** return the product of sorted operators                   **
    // ***************************************************************
    auto new_product_expression = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(new_product_expression));
}

}  // namespace boson_algebra