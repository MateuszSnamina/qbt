// MY HEADER:
#include <boson_algebra/modify_canonical_math.hpp>
// SELF:
#include <boson_algebra/modify_remove_bridge_product.hpp>
#include <boson_algebra/modify_remove_bridge_sum.hpp>
#include <boson_algebra/modify_detect_one_factor.hpp>
#include <boson_algebra/modify_detect_zero_factor.hpp>
#include <boson_algebra/modify_detect_zero_product.hpp>
#include <boson_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
#include <boson_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
#include <boson_algebra/modify_flatten_product.hpp>
#include <boson_algebra/modify_flatten_sum.hpp>
#include <boson_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
#include <boson_algebra/modify_flatten_factor.hpp>
// STD:
#include <iostream>  //DEBUG

namespace boson_algebra {

ExpressionHandlerOptional modify_canonical_math(const ExpressionHandler& expression) {
    //std::cout << "                   IN: " << expression.str() << std::endl; //DOTO remove
    if (auto result = modify_remove_bridge_product(expression)) {
        //std::cout << "                   USE modify_remove_bridge_product" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_remove_bridge_sum(expression)) {
        //std::cout << "                   USE modify_remove_bridge_sum" << std::endl; //DOTO remove
        return std::move(*result);
    }

    if (auto result = modify_detect_one_factor(expression)) {
        //std::cout << "                   USE modify_detect_one_factor" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_detect_zero_factor(expression)) {
        //std::cout << "                   USE modify_detect_zero_factor" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_detect_zero_product(expression)) {
        //std::cout << "                   USE modify_detect_zero_product" << std::endl; //DOTO remove
        return std::move(*result);
    }

    if (auto result = modify_flatten_product(expression)) {
        //std::cout << "                   USE modify_flatten_product" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_flatten_sum(expression)) {
        //std::cout << "                   USE modify_flatten_sum" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_flatten_factor(expression)) {
        //std::cout << "                   USE modify_flatten_factor" << std::endl; //DOTO remove
        return std::move(*result);
    }

    if (auto result = modify_rebuild_prod_factors_into_factor_prod(expression)) {
        //std::cout << "                   USE modify_rebuild_prod_factors_into_factor_prod" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_rebuild_prod_sum_into_sum_prod(expression)) {
        //std::cout << "                   USE modify_rebuild_prod_sum_into_sum_prod" << std::endl; //DOTO remove
        return std::move(*result);
    }
    if (auto result = modify_rebuild_factor_sum_into_sum_factors(expression)) {
        //std::cout << "                   USE modify_rebuild_factor_sum_into_sum_factors" << std::endl; //DOTO remove
        return std::move(*result);
    }
    //std::cout << "                   USE null" << std::endl; //DOTO remove
    return std::nullopt;
}

}  // namespace boson_algebra