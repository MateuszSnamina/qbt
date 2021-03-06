#ifndef BOSON_ALGEBRA_MODIFY_SIMPLIFY_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_MODIFY_SIMPLIFY_LINEAR_COMBINATION_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Simplify linear combination expressions
 * Transformation example: ❴❪3*a❫+❪1*b❫+❪2*a❫+❪1*c❫+❪1*c❫❵ => ❴❪5*a❫+❪1*b❫+❪2*c❫❵
 */

ModificationResult modify_simplify_linear_combination(ExpressionHandler&&);

}  // namespace boson_algebra

#endif