#ifndef BOSON_ALGEBRA_MODIFY_REBUILD_FACTOR_SUM_INTO_SUM_FACTORS_HPP
#define BOSON_ALGEBRA_MODIFY_REBUILD_FACTOR_SUM_INTO_SUM_FACTORS_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: standard expand
 * Transformation example: 4❴a+b+c❵ => ❴❪4a❫+❪4b❫+❪4a❫❵
 * 
 */

ModificationResult modify_rebuild_factor_sum_into_sum_factors(ExpressionHandler&&);

}  // namespace boson_algebra

#endif