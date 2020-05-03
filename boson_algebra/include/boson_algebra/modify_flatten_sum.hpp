#ifndef BOSON_ALGEBRA_MODIFY_FLATTEN_SUM_HPP
#define BOSON_ALGEBRA_MODIFY_FLATTEN_SUM_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Perform simplification due to sum associativity.
 * Transformation example: ❪a+b+❪c+d❫+e+❪f+g❫❫ => ❪a+b+c+d+e+f+g❫
 */

ExpressionHandlerOptional modify_flatten_sum(const ExpressionHandler&);
ModificationResult modify_flatten_sum_new_api(ExpressionHandler&&);

}  // namespace boson_algebra

#endif