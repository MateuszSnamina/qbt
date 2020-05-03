#ifndef BOSON_ALGEBRA_MODIFY_DETECT_ZERO_FACTOR_HPP
#define BOSON_ALGEBRA_MODIFY_DETECT_ZERO_FACTOR_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect when a factor expression has the zero factor or the zero subexpression
 * Transformation example: ❪0a❫ => 𝟘
 * Transformation example: ❪5𝟘❫ => 𝟘
 */

ModificationResult modify_detect_zero_factor_new_api(ExpressionHandler&&);

}  // namespace boson_algebra

#endif
