// BOSON ALGEBRA:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_detect_one_factor.hpp>
#include <boson_algebra/transform_detect_bridge_sum.hpp>
#include <boson_algebra/transform_detect_bridge_product.hpp>
#include <boson_algebra/transform_expand.hpp>
#include <boson_algebra/transform_flatten_product.hpp>
#include <boson_algebra/transform_flatten_sum.hpp>
#include <boson_algebra/transform_simplify_linear_combination.hpp>
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_0.hpp>
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_1.hpp>
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_2.hpp>
#include <boson_algebra/transform_sum_to_linear_combination.hpp>
// STD:
#include <iostream>

using namespace boson_algebra::operators;
using namespace boson_algebra::literals;
namespace ba = boson_algebra;

ba::ExpressionHandler do_simplification(ba::ExpressionHandler&& expression) {
    expression.safe_dfs_transform(ba::transform_sort_product_of_boson_primitive_operators_0, false);
    std::cout << "Sort0:  " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_sort_product_of_boson_primitive_operators_1, false);
    std::cout << "Sort1:  " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_sort_product_of_boson_primitive_operators_2, false);
    std::cout << "Sort2:  " << expression.str() << std::endl;

    expression.safe_dfs_transform(ba::transform_detect_bridge_product, false);
    std::cout << "BridgP:  " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_detect_bridge_sum, false);
    std::cout << "BridgS:  " << expression.str() << std::endl;

    expression.safe_dfs_transform(ba::transform_expand, false);
    std::cout << "Expand: " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_flatten_product, false);
    std::cout << "FlatP:  " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_flatten_sum, false);
    std::cout << "FlatS:  " << expression.str() << std::endl;

    expression.safe_dfs_transform(ba::transform_sum_to_linear_combination, false);
    std::cout << "S->LA:  " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_simplify_linear_combination, false);
    std::cout << "SimpLA: " << expression.str() << std::endl;
    expression.safe_dfs_transform(ba::transform_detect_one_factor, false);
    std::cout << "1Factor:" << expression.str() << std::endl;
    return std::move(expression);
}

int main() {
    ba::ExpressionHandler expression = 'a'_an * 'c'_cr * 'a'_cr * 'b'_cr;
    //ba::ExpressionHandler expression = 'a'_an * 'a'_cr * 'a'_an * 'a'_cr;
    expression.safe_dfs_transform(ba::transform_flatten_product);
    
    std::cout << "INPUT:" << expression.str() << std::endl;
    expression = do_simplification(std::move(expression));
    std::cout << "OUTPUT:" << expression.str() << std::endl;

    expression = do_simplification(std::move(expression));
    std::cout << "OUTPUT:" << expression.str() << std::endl;
}