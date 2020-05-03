#ifndef BOSON_ALGEBRA_MODIFY_REMOVE_BRIDGE_SUM_HPP
#define BOSON_ALGEBRA_MODIFY_REMOVE_BRIDGE_SUM_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect sum of one ingredient and eliminate the not needed structural block
 * Transformation example: ❴a❵ => a
 */

ModificationResult modify_remove_bridge_sum(ExpressionHandler&&);

}  // namespace boson_algebra

#endif