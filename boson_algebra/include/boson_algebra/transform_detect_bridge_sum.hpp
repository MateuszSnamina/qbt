#ifndef BOSON_ALGEBRA_TRANSFORM_DETECT_BRIDGE_PRODUCT_HPP
#define BOSON_ALGEBRA_TRANSFORM_DETECT_BRIDGE_PRODUCT_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect product of one factor and ommit the not needed structural block
 * Transformation example: ❪a❫ => a
 */

ExpressionHandlerOptional transform_detect_bridge_product(const ExpressionHandler&);
//ExpressionHandlerOptional transform_detect_bridge_product(ExpressionHandler&&);

}  // namespace boson_algebra

#endif