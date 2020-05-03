#ifndef BOSON_ALGEBRA_MODIFY_REMOVE_BRIDGE_PRODUCT_HPP
#define BOSON_ALGEBRA_MODIFY_REMOVE_BRIDGE_PRODUCT_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect product of one factor and ommit the not needed structural block
 * Transformation example: ❪a❫ => a
 */

ModificationResult modify_remove_bridge_product_new_api(ExpressionHandler&&);

}  // namespace boson_algebra

#endif