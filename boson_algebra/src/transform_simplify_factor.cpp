//MY HEADER:
#include <boson_algebra/transform_simplify_factor.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

ExpressionHandlerOptional transform_simplify_factor(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto& subexpression_hdl = expression_hdl.target().subexpression(0);
    if (!subexpression_hdl.is_of_type<IntegerFactoredExpression>()) {
        return std::nullopt;
    }
    const auto& subsubexpression_hdl = subexpression_hdl.target().subexpression(0);
    const auto expression_factor = expression_hdl.casted_target<IntegerFactoredExpression>().factor();
    const auto subexpression_factor =  subexpression_hdl.casted_target<IntegerFactoredExpression>().factor();
    return IntegerFactoredExpression::make(expression_factor*subexpression_factor, subsubexpression_hdl.clone());
}

}  // namespace boson_algebra