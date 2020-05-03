#ifndef BOSON_ALGEBRA_MODIFY_FLATTEN_FACTOR_HPP
#define BOSON_ALGEBRA_MODIFY_FLATTEN_FACTOR_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Perform simplification due to factor product associativity.
 * Transformation example: ❪5❪3a❫❫ => ❪15a❫
 */

ModificationResult modify_flatten_factor_new_api(ExpressionHandler&&);

}  // namespace boson_algebra

#endif