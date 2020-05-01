#ifndef BOSON_ALGEBRA_TRANSFORM_SUM_TO_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_TRANSFORM_SUM_TO_LINEAR_COMBINATION_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Transform sum expression to the corresponding linear combination expression 
 * Transformation example: a+(3*a)+b+c => (1*a)+(3*a)+(1*b)+(1*c)
 */

ExpressionHandlerOptional transform_sum_to_linear_combination(const ExpressionHandler&);
//ExpressionHandlerOptional transform_sum_to_linear_combination(ExpressionHandler&&);

}  // namespace boson_algebra

#endif