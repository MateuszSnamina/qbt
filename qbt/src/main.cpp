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
    //std::cout << "INPUT: " << expression.str() << std::endl;
    // Do the job:
    ba::safe_dfs_transform_new_api(expression, ba::modify_sort_product_of_boson_primitive_operators_0_new_api);
    //std::cout << "Sort0:  " << expression.str() << std::endl;
    ba::safe_dfs_transform_new_api(expression, ba::modify_sort_product_of_boson_primitive_operators_1_new_api);
    //std::cout << "Sort1:  " << expression.str() << std::endl;
    unsigned n_replacements = ba::safe_dfs_transform_new_api(expression, ba::modify_sort_product_of_boson_primitive_operators_2_new_api);
    //std::cout << "Sort2:  " << expression.str() << std::endl;
    // Transform to the canonical form:
    ba::safe_dfs_transform_new_api(expression, ba::modify_canonical_math_new_api, ba::GreedinessLevel::DoDfsForReplacedExpressions);
    //std::cout << "CanMath:" << expression.str() << std::endl;
    // Sum up the same expressions:
    ba::safe_dfs_transform_new_api(expression, ba::modify_rebuild_sum_into_linear_combination_new_api);
    // std::cout << "S->LA:  " << expression.str() << std::endl;
    ba::safe_dfs_transform_new_api(expression, ba::modify_simplify_linear_combination_new_api);
    // std::cout << "SimpLA: " << expression.str() << std::endl;
    ba::safe_dfs_transform_new_api(expression, ba::modify_detect_one_factor_new_api);
    // std::cout << "1Factor:" << expression.str() << std::endl;
    ba::safe_dfs_transform_new_api(expression, ba::modify_detect_zero_factor_new_api);
    // std::cout << "0Factor:" << expression.str() << std::endl;
    // Print output:
    //std::cout << "n_replacements: " << n_replacements << std::endl;
    //std::cout << "OUTPUT:" << expression.str() << std::endl;
    // Return
    return n_replacements;
    // return 0; //DOTO
}

int main() {
    ba::ExpressionHandler expression = 'a'_an * 'c'_cr * 'a'_cr * 'b'_cr;
    //ba::ExpressionHandler expression = 'a'_an * 'a'_cr * 'a'_an * 'a'_cr;
    //ba::ExpressionHandler expression = 'a'_cr * 'a'_cr * 'a'_an * 'a'_an * 'b'_an * 'b'_cr;
    //ba::ExpressionHandler expression = 'a'_an * 'a'_an * 'a'_cr * 'a'_cr * 'b'_an * 'b'_cr;

    std::cout << "PREINPUT: " << expression.str() << std::endl;
    ba::safe_dfs_transform_new_api(expression, ba::modify_flatten_product_new_api);
    std::cout << "INPUT:    " << expression.str() << std::endl;
    while (do_simplification(expression) != 0) {
    };
    std::cout << "OUTPUT:   " << expression.str() << std::endl;
}