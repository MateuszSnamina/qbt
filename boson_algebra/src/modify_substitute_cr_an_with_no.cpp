// // MY HEADER:
#include <boson_algebra/modify_substitute_cr_an_with_no.hpp>
// SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/adjacent_find.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/sub_range.hpp>
// STD
#include <iostream>  // debug TODO
#include <iterator>

namespace boson_algebra {

ModificationResult modify_substitute_cr_an_with_no(ExpressionHandler&& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** the transformation does apply to product expressions     **
    // *** with zero factors or only one factor                     **
    // ***************************************************************
    if (expression.n_subexpressions() < 2) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    };
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
    // ***  Find whether there is an adjacent factors pair such that *
    // ***  - the first operator the pair is                        **
    // ***    of type BosonCreationOperator,                        **
    // ***  - the second operator in the pair is                    **
    // ***    of type BosonAnnihilationOperator,                    **
    // ***  - and the both operator have the same underlying boson. **
    // ***************************************************************
    const auto is_creation_annihilation_pair = [](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
        const bool first_operator_in_pair_is_creation = expression1.is_of_type<BosonCreationOperator>();
        const bool second_operator_in_pair_is_annihilation = expression2.is_of_type<BosonAnnihilationOperator>();
        return first_operator_in_pair_is_creation && second_operator_in_pair_is_annihilation;
    };
    const auto have_the_same_boson = [](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
        const auto boson1 = expression1.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
        const auto boson2 = expression2.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
        return boson1->id() == boson2->id();
    };
    const auto is_the_right_pair = [&is_creation_annihilation_pair, &have_the_same_boson](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
        return is_creation_annihilation_pair(expression1, expression2) && have_the_same_boson(expression1, expression2);
    };
    if (boost::adjacent_find(range, is_the_right_pair) == boost::end(range)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // ***  make the new subexpressions                             **
    // ***************************************************************
    const auto do_subsitituon = [&is_the_right_pair, &range](ExpressionHandlerRandomAccessRangeIterator it) {
        if (it + 1 == boost::end(range)) {
            return false;
        }
        const auto& subexpression1 = *it;
        const auto& subexpression2 = *(it + 1);
        return is_the_right_pair(subexpression1, subexpression2);
    };
    ExpressionHandlerVector new_subexpressions;
    for (auto it = boost::begin(range); it < boost::end(range);) {
        if (do_subsitituon(it)) {
            const auto& boson = (*it).casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
            new_subexpressions.push_back(BosonNumberOperator::make(boson));
            it += 2;
        } else {
            new_subexpressions.push_back(std::move(*it));
            it++;
        }
    }
    // ***************************************************************
    // *** return the product of grouped operators                  **
    // ***************************************************************
    auto new_product_expression = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(new_product_expression));
}

}  // namespace boson_algebra