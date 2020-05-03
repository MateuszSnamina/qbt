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

namespace boson_algebra {

ModificationResult modify_canonical_math(ExpressionHandler&& expression) {
    if (modify_in_place(expression, modify_remove_bridge_product)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_remove_bridge_sum)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }

    if (modify_in_place(expression, modify_detect_one_factor)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_detect_zero_factor)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_detect_zero_product)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }

    if (modify_in_place(expression, modify_flatten_product)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_flatten_sum)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_flatten_factor)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }

    if (modify_in_place(expression, modify_rebuild_prod_factors_into_factor_prod)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_rebuild_prod_sum_into_sum_prod)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }
    if (modify_in_place(expression, modify_rebuild_factor_sum_into_sum_factors)) {
        return ModificationResult::make_generated_result(std::move(expression));
    }

    return ModificationResult::make_passed_through_result(std::move(expression));
}

}  // namespace boson_algebra