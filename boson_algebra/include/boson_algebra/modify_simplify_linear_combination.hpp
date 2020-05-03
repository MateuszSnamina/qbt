#ifndef BOSON_ALGEBRA_MODIFY_SIMPLIFY_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_MODIFY_SIMPLIFY_LINEAR_COMBINATION_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Simplify linear combination expressions
 * Transformation example: ❪❪3*a❫+❪1*b❫+❪2*a❫❫ => ❪❪5*a❫+❪1*b❫❫
 */

ExpressionHandlerOptional modify_simplify_linear_combination(const ExpressionHandler&);
ModificationResult modify_simplify_linear_combination_new_api(ExpressionHandler&&);

}  // namespace boson_algebra

#endif