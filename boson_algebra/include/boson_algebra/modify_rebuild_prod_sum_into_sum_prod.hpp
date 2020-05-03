#ifndef BOSON_ALGEBRA_MODIFY_REBUILD_PROD_SUM_INTO_SUM_PROD_HPP
#define BOSON_ALGEBRA_MODIFY_REBUILD_PROD_SUM_INTO_SUM_PROD_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Standard Rebuild_prod_sum_into_sum_prod
 * Transformation example: ❪a◦❪b+c❫◦d❫ => ❪❪a◦b◦d❫+❪a◦c◦d❫❫
 */
ModificationResult modify_rebuild_prod_sum_into_sum_prod(ExpressionHandler&&);

}  // namespace boson_algebra

#endif