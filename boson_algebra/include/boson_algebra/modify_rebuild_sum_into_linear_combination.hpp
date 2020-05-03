#ifndef BOSON_ALGEBRA_MODIFY_REBUILD_SUM_INTO_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_MODIFY_REBUILD_SUM_INTO_LINEAR_COMBINATION_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Transform sum expression to the corresponding linear combination expression 
 * Transformation example: ❪a+❪3a❫+b+c❫ => ❪❪1a❫+❪3a❫+❪1b❫+(1c❫❫
 */

ModificationResult modify_rebuild_sum_into_linear_combination(ExpressionHandler&&);

}  // namespace boson_algebra

#endif