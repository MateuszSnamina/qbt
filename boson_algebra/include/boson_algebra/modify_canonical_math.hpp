#ifndef BOSON_ALGEBRA_MODIFY_CANONICAL_MATH_HPP
#define BOSON_ALGEBRA_MODIFY_CANONICAL_MATH_HPP

// SELF:
#include <boson_algebra/algorithm_dfs.hpp>
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

ExpressionHandlerOptional modify_canonical_math(const ExpressionHandler& expression);
ModificationResult modify_canonical_math_new_api(ExpressionHandler&& expression);

}  // namespace boson_algebra

#endif