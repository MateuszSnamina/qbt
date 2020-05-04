#ifndef BOSON_ALGEBRA_MODIFY_SUBSTITUTE_CR_AN_WITH_NO_HPP
#define BOSON_ALGEBRA_MODIFY_SUBSTITUTE_CR_AN_WITH_NO_HPP

#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/modify_substitute_cr_an_with_no.hpp>

namespace boson_algebra {

/*
 * Transformation goal: In froduct of boson operators -- substitude ♭b◦♯b adjacent factor pair with ℕb.
 * Transformation example: ❪♭a◦♯a◦♭a❫ => ❪♭a◦ℕa❫
 * Transformation example: ❪♯b◦♯b◦♭b◦♯a◦♭a❫ => ❪♯b◦ℕb◦ℕa❫
 * 
 */

ModificationResult modify_substitute_cr_an_with_no(ExpressionHandler&& expression);

}  // namespace boson_algebra

#endif