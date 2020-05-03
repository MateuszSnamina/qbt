#ifndef BOSON_ALGEBRA_MODIFY_FLATTEN_FACTOR_HPP
#define BOSON_ALGEBRA_MODIFY_FLATTEN_FACTOR_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Perform simplification due to factor product associativity.
 * Transformation example: ❪5❪3a❫❫ => ❪15a❫
 */

ExpressionHandlerOptional modify_flatten_factor(const ExpressionHandler&);
//ExpressionHandlerOptional modify_flatten_factor(ExpressionHandler&&);

}  // namespace boson_algebra

#endif