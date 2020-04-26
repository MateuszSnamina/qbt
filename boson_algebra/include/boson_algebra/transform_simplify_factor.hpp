#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FACTOR_HPP
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FACTOR_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Perform simplification due to product associativity.
 * Transfomration example: 5*(3*a) => 15*a
 */

ExpressionHandlerOptional transform_simplify_factor(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif