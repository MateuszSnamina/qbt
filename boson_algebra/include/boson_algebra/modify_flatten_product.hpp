#ifndef BOSON_ALGEBRA_MODIFY_FLATTEN_PRODUCT_HPP
#define BOSON_ALGEBRA_MODIFY_FLATTEN_PRODUCT_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Perform simplification due to product associativity.
 * Transformation example: ❪a◦b◦❪c◦d❫◦e◦❪f◦g❫❫ => ❪a◦b◦c◦d◦e◦f◦g❫
 */

ModificationResult modify_flatten_product(ExpressionHandler&&);

}  // namespace boson_algebra

#endif