#ifndef BOSON_ALGEBRA_TRANSFORM_DETECT_ZERO_FACTOR_HPP
#define BOSON_ALGEBRA_TRANSFORM_DETECT_ZERO_FACTOR_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect when a factor expression has the zero factor or the zero subexpression
 * Transformation example: ❪0a❫ => 𝟘
 * Transformation example: ❪5𝟘❫ => 𝟘
 */

ExpressionHandlerOptional transform_detect_zero_factor(const ExpressionHandler&);
//ExpressionHandlerOptional transform_detect_zero_factor(ExpressionHandler&&);

}  // namespace boson_algebra

#endif
