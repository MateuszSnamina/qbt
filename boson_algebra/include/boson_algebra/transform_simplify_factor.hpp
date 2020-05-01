#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FACTOR_HPP
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FACTOR_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Perform simplification due to factor product associativity.
 * Transformation example: ❪5❪3a❫❫ => ❪15a❫
 */

ExpressionHandlerOptional transform_simplify_factor(const ExpressionHandler&);
//ExpressionHandlerOptional transform_simplify_factor(ExpressionHandler&&);

}  // namespace boson_algebra

#endif