#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_SUM_HPP
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_SUM_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Perform simplification due to sum associativity.
 * Transfomration example: a+b+(c+d)+e+(f+g) => a+b+c+d+e+f+g
 */

ExpressionHandlerOptional transform_simplify_sum(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif