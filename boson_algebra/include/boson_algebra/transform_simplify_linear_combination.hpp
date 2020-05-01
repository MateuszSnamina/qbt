#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_LINEAR_COMBINATION_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Simplify linear combination expressions
 * Transformation example: (3*a)+(1*b)+(2*a) => (5*a)+(1*b)
 */

ExpressionHandlerOptional transform_simplify_linear_combination(const ExpressionHandler&);
//ExpressionHandlerOptional transform_simplify_linear_combination(ExpressionHandler&&);

}  // namespace boson_algebra

#endif