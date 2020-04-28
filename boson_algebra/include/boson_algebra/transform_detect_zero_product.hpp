#ifndef BOSON_ALGEBRA_TRANSFORM_DETECT_ZERO_PRODUCT_HPP
#define BOSON_ALGEBRA_TRANSFORM_DETECT_ZERO_PRODUCT_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Detect when product expression has the zero factor
 * Transfomration example: a◦b◦𝟘◦c◦d => 𝟘
 */

ExpressionHandlerOptional transform_detect_zero_product(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif