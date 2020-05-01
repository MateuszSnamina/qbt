#ifndef BOSON_ALGEBRA_TRANSFORM_SUM_TO_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_TRANSFORM_SUM_TO_LINEAR_COMBINATION_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Transform sum expression to the corresponding linear combination expression 
 * Transformation example: ❪a+❪3a❫+b+c❫ => ❪❪1a❫+❪3a❫+❪1b❫+(1c❫❫
 */

ExpressionHandlerOptional transform_sum_to_linear_combination(const ExpressionHandler&);
//ExpressionHandlerOptional transform_sum_to_linear_combination(ExpressionHandler&&);

}  // namespace boson_algebra

#endif