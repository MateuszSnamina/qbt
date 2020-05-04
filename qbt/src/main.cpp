// BOSON ALGEBRA:
#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_all.hpp>
// STD:
#include <iostream>

using namespace boson_algebra::operators;
using namespace boson_algebra::literals;
namespace ba = boson_algebra;

unsigned do_simplification(ba::ExpressionHandler& expression) {
    // Do the job:
    ba::dfs_transform(expression, ba::modify_sort_product_of_boson_primitive_operators_0);
    ba::dfs_transform(expression, ba::modify_sort_product_of_boson_primitive_operators_1);
    const unsigned n_replacements = ba::dfs_transform(expression, ba::modify_sort_product_of_boson_primitive_operators_2);
    // Transform to the canonical form:
    ba::dfs_transform(expression, ba::modify_canonical_math, ba::GreedinessLevel::DoDfsForReplacedExpressions);
    // Sum up the same expressions:
    ba::dfs_transform(expression, ba::modify_rebuild_sum_into_linear_combination);
    ba::dfs_transform(expression, ba::modify_simplify_linear_combination);
    ba::dfs_transform(expression, ba::modify_detect_one_factor);
    ba::dfs_transform(expression, ba::modify_detect_zero_factor);
    // Return
    return n_replacements;
}

int main() {
    //ba::ExpressionHandler expression = 'a'_an * 'c'_cr * 'a'_cr * 'b'_cr;
    //ba::ExpressionHandler expression = 'a'_an * 'a'_cr * 'a'_an * 'a'_cr;
    //ba::ExpressionHandler expression = 'a'_cr * 'a'_cr * 'a'_an * 'a'_an * 'b'_an * 'b'_cr;
    ba::ExpressionHandler expression = 'a'_an * 'a'_an * 'a'_cr * 'a'_cr * 'b'_an * 'b'_cr;

    ba::dfs_transform(expression, ba::modify_flatten_product);
    std::cout << "INPUT   :    " << expression.str() << std::endl;
    while (do_simplification(expression) != 0) {
    };
    std::cout << "OUTPUT1 :   " << expression.str() << std::endl;
    ba::dfs_transform(expression, ba::modify_substitute_cr_an_with_no);
    std::cout << "OUTPUT2 :   " << expression.str() << std::endl;
}