#ifndef BOSON_ALGEBRA_MODIFY_REBUILD_PROD_FACTORS_INTO_FACTOR_PROD_HPP
#define BOSON_ALGEBRA_MODIFY_REBUILD_PROD_FACTORS_INTO_FACTOR_PROD_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Take out the accumulated factor of factors
 * Transformation example: ❪❪3a❫◦❪1b❫◦❪2a❫❫ => ❪6❪a◦b◦a❫❫
 * 
 */

ExpressionHandlerOptional modify_rebuild_prod_factors_into_factor_prod(const ExpressionHandler&);

}  // namespace boson_algebra

#endif