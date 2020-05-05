// BOSON ALGEBRA:
#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_all.hpp>
#include <boson_algebra/util_make.hpp>

// STD:
#include <iostream>

using namespace boson_algebra::operators;
using namespace boson_algebra::literals;
namespace ba = boson_algebra;

unsigned do_unification_step(ba::ExpressionHandler& expression) {
    // Do the unification step:
    ba::dfs_transform(expression, ba::modify_sort_product_of_boson_primitive_operators_0);
    ba::dfs_transform(expression, ba::modify_sort_product_of_boson_primitive_operators_1);
    const unsigned n_replacements = ba::dfs_transform(expression, ba::modify_sort_product_of_boson_primitive_operators_2);
    // Clean the AST -- transform to the canonical form:
    ba::dfs_transform(expression, ba::modify_canonical_math, ba::GreedinessLevel::DoDfsForReplacedExpressions);
    // Sum up the same expressions:
    ba::dfs_transform(expression, ba::modify_rebuild_sum_into_linear_combination);
    ba::dfs_transform(expression, ba::modify_simplify_linear_combination);
    ba::dfs_transform(expression, ba::modify_detect_one_factor);
    ba::dfs_transform(expression, ba::modify_detect_zero_factor);
    // Return
    return n_replacements;
}

ba::ExpressionHandler do_unification(const ba::ExpressionHandler& expression) {
    auto new_expression = expression.clone();
    while (do_unification_step(new_expression) != 0) {
    };
    return std::move(new_expression);
}

ba::ExpressionHandler substitute_cr_an_with_no(const ba::ExpressionHandler& expression) {
    auto new_expression = expression.clone();
    ba::dfs_transform(new_expression, ba::modify_substitute_cr_an_with_no);
    return new_expression;
}

ba::ExpressionHandler make_la(const ba::ExpressionHandler& expression) {
    auto new_expression = expression.clone();
    if (!new_expression.is_of_type<ba::SumExpression>()) {
        new_expression = ba::SumExpression::make(new_expression.clone());
    }
    ba::modify_in_place(new_expression, ba::modify_rebuild_sum_into_linear_combination);
    return new_expression;
}

int main() {
    //ba::ExpressionHandler expression = 'a'_an * 'c'_cr * 'a'_cr * 'b'_cr;
    //ba::ExpressionHandler expression = 'a'_an * 'a'_cr * 'a'_an * 'a'_cr;
    //ba::ExpressionHandler expression = 'a'_cr * 'a'_cr * 'a'_an * 'a'_an * 'b'_an * 'b'_cr;
    ba::ExpressionHandler expression = 'a'_an * 'a'_an * 'a'_cr * 'a'_cr * 'b'_an * 'b'_cr;

    ba::dfs_transform(expression, ba::modify_flatten_product);
    std::cout << "INPUT   :    " << expression.str() << std::endl;
    const auto unified_expression_1 = do_unification(expression);
    std::cout << "OUTPUT1 :   " << unified_expression_1.str() << std::endl;
    const auto unified_expression_2 = substitute_cr_an_with_no(unified_expression_1);
    std::cout << "OUTPUT2 :   " << unified_expression_2.str() << std::endl;

    ba::ExpressionHandlerVector bits = ba::util::make<ba::ExpressionHandlerVector>(
        'a'_cr, 'a'_an,
        'b'_cr, 'b'_an,
        'c'_cr, 'c'_an,
        'd'_cr, 'd'_an);
    for (int i1 = 0; i1 < 8; i1++) {
        for (int i2 = 0; i2 < 8; i2++) {
            for (int i3 = 0; i3 < 8; i3++) {
                for (int i4 = 0; i4 < 8; i4++) {
                    const auto expression = ba::ProductExpression::make(bits[i1].clone(), bits[i2].clone(), bits[i3].clone(), bits[i4].clone());
                    //std::cout << "IN  :" << expression.str() << std::endl;
                    const auto unified_expression_1 = do_unification(expression);
                    const auto unified_expression_2 = substitute_cr_an_with_no(unified_expression_1);
                    //std::cout << "OUT: " << unified_expression_2.str() << std::endl;
                    const auto la_expression = make_la(unified_expression_2);
                    std::cout << expression.str()
                              << " = " << la_expression.str()
                              << " = " << unified_expression_2.str()
                              << std::endl;
                }
            }
        }
    }
}