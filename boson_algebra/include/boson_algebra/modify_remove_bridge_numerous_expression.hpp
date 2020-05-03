#ifndef BOSON_ALGEBRA_MODIFY_REMOVE_BRIDGE_NUMEROUS_EXPRESSION_HPP
#define BOSON_ALGEBRA_MODIFY_REMOVE_BRIDGE_NUMEROUS_EXPRESSION_HPP

// SELF:
#include <boson_algebra/expression_abstract.hpp>
// STD:
#include <type_traits>

namespace boson_algebra {

template<class VectorNumerousExpressionDerrivedClass>
ExpressionHandlerOptional modify_remove_bridge_numerous_expression(const ExpressionHandler& expression) {
    static_assert(std::is_base_of_v<VectorNumerousExpression, VectorNumerousExpressionDerrivedClass>);
    if (!expression.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
        return std::nullopt;
    }
    const auto is_bridge = (expression.n_subexpressions() == 1);
    if (!is_bridge) {
        return std::nullopt;
    }
    const auto& subexpression = expression.subexpression(0);
    return subexpression.clone();
}

}  // namespace boson_algebra

#endif