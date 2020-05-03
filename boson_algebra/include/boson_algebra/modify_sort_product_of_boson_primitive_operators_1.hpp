#ifndef BOSON_ALGEBRA_MODIFY_SORT_PRODUCT_OF_BOSON_PRIMITIVE_OPERATORS_1_HPP
#define BOSON_ALGEBRA_MODIFY_SORT_PRODUCT_OF_BOSON_PRIMITIVE_OPERATORS_1_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: stable sort of boson primitive operators product factors regarding the bosons id.
 * Transformation example: ❪♭a◦ℕa◦♭a◦♯a◦♯b◦♭b◦ℕc❫ => ❪❪♭a◦ℕa◦♭a◦♯a❫◦❪♯b◦♭b❫◦❪ℕc❫❫
 */

ExpressionHandlerOptional modify_sort_product_of_boson_primitive_operators_1(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif