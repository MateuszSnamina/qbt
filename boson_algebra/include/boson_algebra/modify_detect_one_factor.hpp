#ifndef BOSON_ALGEBRA_MODIFY_DETECT_ONE_FACTOR_HPP
#define BOSON_ALGEBRA_MODIFY_DETECT_ONE_FACTOR_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect when a factor expression has the factor equal to one and eliminate the not needed factor expression
 * Transformation example: ❪1a❫ => a
 */

ModificationResult modify_detect_one_factor(ExpressionHandler&&);

}  // namespace boson_algebra

#endif
