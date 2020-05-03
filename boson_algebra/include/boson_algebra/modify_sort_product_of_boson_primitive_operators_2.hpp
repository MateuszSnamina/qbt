#ifndef BOSON_ALGEBRA_MODIFY_SORT_PRODUCT_OF_BOSON_PRIMITIVE_OPERATORS_2_HPP
#define BOSON_ALGEBRA_MODIFY_SORT_PRODUCT_OF_BOSON_PRIMITIVE_OPERATORS_2_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transformation goal: Make the product more like the "desired" product
 * Transformation example: ❪♭a◦♭a◦♯a❫ => ❪❪♭a◦♯a◦♭a❫ + ❪♭a◦𝕀❫❫
 * Transformation example: ❪♯b◦♯b◦♭b◦♭b◦♭b❫ => ❪❪♯b◦♭b◦♯b◦♭b◦♭b❫+❪-❪♯b◦𝕀◦♭b◦♭b❫❫❫
 * 
 * Full explanation:
 * For every product of creation operators and annihilation operators defined for one boson
 * we define the "desired product" of the operators.
 * 
 * The "desired product":
 * - is build up the same creation operators and annihilation operators,
 * - the number of factors being creation (annihilation) operator
 *    is just the same as in the original product.
 * - the "original product" and the "desired product" differ in the operator factors ordering.
 * - the desired product factors are (mentally) grouped into the contiguous chunks.
 * -- the first chunk consist of only factors being creation operator,
 * -- the second chunk consist of only factors alternately being creation operator and factors being annihilation operator
 * -- the third chunk consist of only factors being annihilation operator,
 * - the chunks may be degenerated (there is no operator in it),
 * - given the original product having n_an annihilation operators and n_cr creation operators, then:
 * -- the first chunk consists of n_cr - min(n_cr, n_an),
 * -- the second chunk consists of 2 * min(n_cr, n_an),
 * -- the third chunk consists of n_an - min(n_cr, n_an),
 * For example for "original product" ♭a◦♭a◦♯a the "desired product is": ♭a◦♯a◦♭a,
 * with first  chunk being ♭a, the second chunk being ♯a◦♭a,  and the third chunk being degenerated.
 * 
 * The transformation finds the first factor the "original" product and "desired" product differ
 * (search "from left to right"). For the mismatch place it considers the desired factor type (creation or annihilation).
 * Then transformation finds the first factor in the "original" product of the desired factor type  
 * (search "from left to right" starting from the found mismatch place).
 * Having the latter factor, it "transposes" with its predecessor (the neighbor factor from the left side).
 * The transposition transforms the "original product" into transformed one that is "closer" to the desired one.
 * 
 * Of course the transposition is not possible without a side effect (the transposed operator do not commute).
 * The transformation introduces a new term to keep the transformed expression algebraically equivalent.
 */

ModificationResult modify_sort_product_of_boson_primitive_operators_2(ExpressionHandler&& expression);

}  // namespace boson_algebra

#endif