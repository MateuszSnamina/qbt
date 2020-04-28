#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_LINEAR_COMBINATION_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Simplify linear combination
 * Transfomration example: (3*a)+(1*b)+(2*a) => (5*a)+(1*b)
 */

ExpressionHandlerOptional transform_simplify_linear_combination(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif