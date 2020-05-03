#ifndef BOSON_ALGEBRA_MODIFY_FLATTEN_PRODUCT_HPP
#define BOSON_ALGEBRA_MODIFY_FLATTEN_PRODUCT_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Perform simplification due to product associativity.
 * Transformation example: ❪a◦b◦❪c◦d❫◦e◦❪f◦g❫❫ => ❪a◦b◦c◦d◦e◦f◦g❫
 */

ExpressionHandlerOptional modify_flatten_product(const ExpressionHandler&);
ModificationResult modify_flatten_product_new_api(ExpressionHandler&&);

}  // namespace boson_algebra

#endif