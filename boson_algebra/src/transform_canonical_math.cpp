// MY HEADER:
#include <boson_algebra/transform_canonical_math.hpp>
// SELF:
#include <boson_algebra/transform_detect_bridge_product.hpp>
#include <boson_algebra/transform_detect_bridge_sum.hpp>
#include <boson_algebra/transform_detect_one_factor.hpp>
#include <boson_algebra/transform_detect_zero_factor.hpp>
#include <boson_algebra/transform_detect_zero_product.hpp>
#include <boson_algebra/transform_expand.hpp>
#include <boson_algebra/transform_factor_sum_to_sum_factors.hpp>
#include <boson_algebra/transform_flatten_product.hpp>
#include <boson_algebra/transform_flatten_sum.hpp>
#include <boson_algebra/transform_prod_factors_to_factor_prod.hpp>
#include <boson_algebra/transform_simplify_factor.hpp>
// STD:
#include <iostream>  //DEBUG

namespace boson_algebra {

ExpressionHandlerOptional transform_canonical_math(const ExpressionHandler& expression) {
    //std::cout << "                   IN: " << expression.str() << std::endl; //DOTO remove
    if (auto result = transform_detect_bridge_product(expression)) {
        //std::cout << "                   USE transform_detect_bridge_product" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_detect_bridge_sum(expression)) {
        //std::cout << "                   USE transform_detect_bridge_sum" << std::endl; //DOTO remove
        return std::move(*result);
    }

    if (auto result = transform_detect_one_factor(expression)) {
        //std::cout << "                   USE transform_detect_one_factor" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_detect_zero_factor(expression)) {
        //std::cout << "                   USE transform_detect_zero_factor" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_detect_zero_product(expression)) {
        //std::cout << "                   USE transform_detect_zero_product" << std::endl; //DOTO remove
        return std::move(*result);
    }

    if (auto result = transform_flatten_product(expression)) {
        //std::cout << "                   USE transform_flatten_product" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_flatten_sum(expression)) {
        //std::cout << "                   USE transform_flatten_sum" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_simplify_factor(expression)) {
        //std::cout << "                   USE transform_simplify_factor" << std::endl; //DOTO remove
        return std::move(*result);
    }

    if (auto result = transform_prod_factors_to_factor_prod(expression)) {
        //std::cout << "                   USE transform_prod_factors_to_factor_prod" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_expand(expression)) {
        //std::cout << "                   USE transform_expand" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = transform_factor_sum_to_sum_factors(expression)) {
        //std::cout << "                   USE transform_factor_sum_to_sum_factors" << std::endl; //DOTO remove
        return std::move(*result);
    }
    //std::cout << "                   USE null" << std::endl; //DOTO remove
    return std::nullopt;
}

}  // namespace boson_algebra