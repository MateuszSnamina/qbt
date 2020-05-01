#ifndef BOSON_ALGEBRA_TRANSFORM_EXPAND_HPP
#define BOSON_ALGEBRA_TRANSFORM_EXPAND_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Standard Expand
 * Transformation example: ❪a◦❪b+c❫◦d❫ => ❪❪a◦b◦d❫+❪a◦c◦d❫❫
 */
ExpressionHandlerOptional transform_expand(const ExpressionHandler&);

}  // namespace boson_algebra

#endif