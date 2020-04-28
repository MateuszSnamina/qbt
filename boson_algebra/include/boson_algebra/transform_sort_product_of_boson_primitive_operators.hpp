#ifndef BOSON_ALGEBRA_TRANSFORM_SORT_PRODUCT_OF_BOSON_PRIMITIVE_OPERATORS_HPP
#define BOSON_ALGEBRA_TRANSFORM_SORT_PRODUCT_OF_BOSON_PRIMITIVE_OPERATORS_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Stable sort of boson primitive operators regarding bosons id.
 * Transfomration example: ♭a◦♯b◦ℕa◦♭a◦ℕc◦♯a◦♭b => ♭a◦ℕa◦♭a◦♯a◦♯b◦♭b◦ℕc
 */

ExpressionHandlerOptional transform_sort_product_of_boson_primitive_operators(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif