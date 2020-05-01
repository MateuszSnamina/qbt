#ifndef BOSON_ALGEBRA_TRANSFORM_PROD_FACTORS_TO_FACTOR_PROD_HPP
#define BOSON_ALGEBRA_TRANSFORM_PROD_FACTORS_TO_FACTOR_PROD_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Take out the accumulated factor of factors
 * Transformation example: (3*a)◦(1*b)◦(2*a) => 6(a◦b◦a)
 */

ExpressionHandlerOptional transform_prod_factors_to_factor_prod(const ExpressionHandler&);

}  // namespace boson_algebra

#endif