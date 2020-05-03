#ifndef BOSON_ALGEBRA_MODIFY_DETECT_ZERO_PRODUCT_HPP
#define BOSON_ALGEBRA_MODIFY_DETECT_ZERO_PRODUCT_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Detect when product expression has the zero factor
 * Transformation example: ❪a◦b◦𝟘◦c◦d❫ => 𝟘
 */

ModificationResult modify_detect_zero_product(ExpressionHandler&&);

}  // namespace boson_algebra

#endif