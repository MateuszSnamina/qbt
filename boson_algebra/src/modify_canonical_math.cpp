// MY HEADER:
#include <boson_algebra/modify_canonical_math.hpp>
// SELF:
#include <boson_algebra/modify_detect_one_factor.hpp>
#include <boson_algebra/modify_detect_zero_factor.hpp>
#include <boson_algebra/modify_detect_zero_product.hpp>
#include <boson_algebra/modify_flatten_factor.hpp>
#include <boson_algebra/modify_flatten_product.hpp>
#include <boson_algebra/modify_flatten_sum.hpp>
#include <boson_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
#include <boson_algebra/modify_rebuild_prod_factors_into_factor_prod.hpp>
#include <boson_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
#include <boson_algebra/modify_remove_bridge_product.hpp>
#include <boson_algebra/modify_remove_bridge_sum.hpp>
// STD:
#include <iostream>  //DEBUG

namespace boson_algebra {

ModificationResult modify_canonical_math_new_api(ExpressionHandler&& expression) {
    if (modify_in_place(expression, modify_remove_bridge_product_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_remove_bridge_sum_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }


    if (modify_in_place(expression, modify_detect_one_factor_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_detect_zero_factor_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_detect_zero_product_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }


    if (modify_in_place(expression, modify_flatten_product_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_flatten_sum_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_flatten_factor_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }

    if (modify_in_place(expression, modify_rebuild_prod_factors_into_factor_prod_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_rebuild_prod_sum_into_sum_prod_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_rebuild_factor_sum_into_sum_factors_new_api)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }

    return ModificationResult::make_passed_through_result(std::move(expression));
}

}  // namespace boson_algebra