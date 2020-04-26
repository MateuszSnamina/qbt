#ifndef BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FLATTEN_HPP
#define BOSON_ALGEBRA_TRANSFORM_SIMPLIFY_FLATTEN_HPP

//SELF
#include <boson_algebra/expression_common.hpp>
//BOOST:
#include <boost/range/algorithm.hpp>

namespace boson_algebra {

template<class VectorNumerousExpressionDerrivedClass>
ExpressionHandlerOptional transform_simplify_flatten(const ExpressionHandler& expression_hdl) {
    static_assert(std::is_base_of_v<VectorNumerousExpression, VectorNumerousExpressionDerrivedClass>);
    if (!expression_hdl.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.target().crange();
    const auto subproduct_hdl_iter = boost::find_if(range, [](const ExpressionHandler& expression_hdl) {
        return expression_hdl.is_of_type<VectorNumerousExpressionDerrivedClass>();
    });
    if (subproduct_hdl_iter == boost::end(range)) {
        return std::nullopt;
    }
    ExpressionHandlerVector v;
    for (const auto& subexpression_hdl : range) {
        if (subexpression_hdl.is_of_type<VectorNumerousExpressionDerrivedClass>()) {
            for (const auto& subsubexpression_hdl : subexpression_hdl.target().crange()) {
                v.emplace_back(std::move(subsubexpression_hdl.clone()));
            }
        } else {
            v.emplace_back(std::move(subexpression_hdl.clone()));
        }
    }
    return VectorNumerousExpressionDerrivedClass::make(std::move(v));
}

}  // namespace boson_algebra

#endif