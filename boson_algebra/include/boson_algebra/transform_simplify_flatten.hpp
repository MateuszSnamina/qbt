#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FLATTEN_HPP //TODO remove SIMPLIFY WORD!!
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FLATTEN_HPP

// SELF
#include <boson_algebra/expression_common.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
// STD:
#include <type_traits>

namespace boson_algebra {

template<class VectorNumerousExpressionDerrivedClass>
ExpressionHandlerOptional transform_simplify_flatten(const ExpressionHandler& expression) {
    static_assert(std::is_base_of_v<VectorNumerousExpression, VectorNumerousExpressionDerrivedClass>);
    // ***************************************************************
    // *** the transformation applies only to expressions being     **
    // *** of VectorNumerousExpressionDerrivedClass type            **
    // ***************************************************************
    if (!expression.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
        return std::nullopt;
    }
    const auto& range = expression.crange();
    // ***************************************************************
    // *** the transformation applies only to expressions           **
    // *** with at least one subexpressions being                   **
    // *** of VectorNumerousExpressionDerrivedClass type            **
    // ***************************************************************
    const auto is_given_type_expression = [](const ExpressionHandler& expression) {
        return expression.is_of_type<VectorNumerousExpressionDerrivedClass>();
    };
    const bool is_any_of_subexpressions_of_given_type = boost::algorithm::any_of(range, is_given_type_expression);
    if (!is_any_of_subexpressions_of_given_type) {
        return std::nullopt;
    }
    // ***************************************************************
    // *** make the new subexpressions                              **
    // ***************************************************************
    ExpressionHandlerVector v;
    for (const auto& subexpression : range) {
        if (subexpression.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
            for (const auto& subsubexpression : subexpression.crange()) {
                v.emplace_back(std::move(subsubexpression.clone()));
            }
        } else {
            v.emplace_back(std::move(subexpression.clone()));
        }
    }
    // ***************************************************************
    // *** return the flattened expression                          **
    // ***************************************************************
    return VectorNumerousExpressionDerrivedClass::make_from_buffer(std::move(v));
}

}  // namespace boson_algebra

#endif