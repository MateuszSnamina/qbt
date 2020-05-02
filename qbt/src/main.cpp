// BOSON ALGEBRA:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_all.hpp>
// #include <boson_algebra/transform_detect_one_factor.hpp>
// #include <boson_algebra/transform_detect_bridge_sum.hpp>
// #include <boson_algebra/transform_detect_bridge_product.hpp>
// #include <boson_algebra/transform_expand.hpp>
// #include <boson_algebra/transform_flatten_product.hpp>
// #include <boson_algebra/transform_flatten_sum.hpp>
// #include <boson_algebra/transform_simplify_linear_combination.hpp>
// #include <boson_algebra/transform_sort_product_of_boson_primitive_operators_0.hpp>
// #include <boson_algebra/transform_sort_product_of_boson_primitive_operators_1.hpp>
// #include <boson_algebra/transform_sort_product_of_boson_primitive_operators_2.hpp>
// #include <boson_algebra/transform_sum_to_linear_combination.hpp>
#include <boson_algebra/algorithm_dfs.hpp>
// STD:
#include <iostream>

using namespace boson_algebra::operators;
using namespace boson_algebra::literals;
namespace ba = boson_algebra;

unsigned do_simplification(ba::ExpressionHandler& expression) {
    std::cout << "INPUT: " << expression.str() << std::endl;
    // Do the job:
    ba::safe_dfs_transform(expression, ba::transform_sort_product_of_boson_primitive_operators_0);
    //std::cout << "Sort0:  " << expression.str() << std::endl;
    ba::safe_dfs_transform(expression, ba::transform_sort_product_of_boson_primitive_operators_1);
    //std::cout << "Sort1:  " << expression.str() << std::endl;
    unsigned n_replacements = ba::safe_dfs_transform(expression, ba::transform_sort_product_of_boson_primitive_operators_2);
    //std::cout << "Sort2:  " << expression.str() << std::endl;
    // Transform to the canonical form:
    ba::safe_dfs_transform(expression, ba::transform_canonical_math, ba::GreedinessLevel::DoDfsForReplacedExpressions);
    std::cout << "CanMath:" << expression.str() << std::endl;
    // Sum up the same expressions:
    ba::safe_dfs_transform(expression, ba::transform_sum_to_linear_combination);
    // std::cout << "S->LA:  " << expression.str() << std::endl;
    ba::safe_dfs_transform(expression, ba::transform_simplify_linear_combination);
    // std::cout << "SimpLA: " << expression.str() << std::endl;
    ba::safe_dfs_transform(expression, ba::transform_detect_one_factor);
    // std::cout << "1Factor:" << expression.str() << std::endl;
    ba::safe_dfs_transform(expression, ba::transform_detect_zero_factor);
    // std::cout << "0Factor:" << expression.str() << std::endl;
    // Print output:
    std::cout << "n_replacements: " << n_replacements << std::endl;
    std::cout << "OUTPUT:" << expression.str() << std::endl;
    // Return
    return n_replacements;
}

int main() {
    //ba::ExpressionHandler expression = 'a'_an * 'c'_cr * 'a'_cr * 'b'_cr;
    //ba::ExpressionHandler expression = 'a'_an * 'a'_cr * 'a'_an * 'a'_cr;
    //ba::ExpressionHandler expression = 'a'_cr * 'a'_cr * 'a'_an * 'a'_an * 'b'_an * 'b'_cr;
    ba::ExpressionHandler expression = 'a'_an * 'a'_an * 'a'_cr * 'a'_cr * 'b'_an * 'b'_cr;

    ba::safe_dfs_transform(expression, ba::transform_flatten_product);
    while (do_simplification(expression) != 0) {
    };

    //std::cout << "OUTPUT:" << expression.str() << std::endl;
}