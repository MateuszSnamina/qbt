#ifndef BOSON_ALGEBRA_TRANSFORM_FACTOR_SUM_TO_SUM_FACTORS_HPP
#define BOSON_ALGEBRA_TRANSFORM_FACTOR_SUM_TO_SUM_FACTORS_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: expand factor of sum
 * Transformation example: 4❴a+b+c❵ => ❴❪4a❫+❪4b❫+❪4a❫❵
 * 
 */

ExpressionHandlerOptional transform_factor_sum_to_sum_factors(const ExpressionHandler&);

}  // namespace boson_algebra

#endif