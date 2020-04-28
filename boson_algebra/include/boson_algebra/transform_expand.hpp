#ifndef BOSON_ALGEBRA_TRANSFORM_EXPAND_HPP
#define BOSON_ALGEBRA_TRANSFORM_EXPAND_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Standard Expand
 * Transfomration example: a*(b+c)*d => a*b*d + a*c*d
 */

ExpressionHandlerOptional transform_expand(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif