#ifndef BOSON_ALGEBRA_TRANSFORM_SUM_TO_LINEAR_COMBINATION_HPP
#define BOSON_ALGEBRA_TRANSFORM_SUM_TO_LINEAR_COMBINATION_HPP

#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

/*
 * Transfomration goal: Transform sum to lineal combination
 * Transfomration example: a+(3*a)+b+c => (1*a)+(3*a)+(1*b)+(1*c)
 */

ExpressionHandlerOptional transform_sum_to_linear_combination(const ExpressionHandler& expression_hdl);

}  // namespace boson_algebra

#endif