#ifndef BOSON_ALGEBRA_TRANSFORM_DETECT_ZERO_FACTOR_HPP
#define BOSON_ALGEBRA_TRANSFORM_DETECT_ZERO_FACTOR_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Detect when a factor expression has the zero factor
 * Transfomration example: (0a) => 𝟘,  (5*𝟘) => 𝟘
 */

ExpressionHandlerOptional transform_detect_zero_factor(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif
