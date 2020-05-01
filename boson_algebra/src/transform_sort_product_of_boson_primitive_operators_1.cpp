// MY HEADER:
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_1.hpp>
// SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm/stable_sort.hpp>
#include <boost/range/algorithm/transform.hpp>
// STD
//#include <iostream>  // debug
#include <iterator>

namespace boson_algebra {

ExpressionHandlerOptional transform_sort_product_of_boson_primitive_operators_1(const ExpressionHandler& expression) {
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** with factors being of BosonPrimitiveOperators type       **
    // ***************************************************************
    const auto is_boson_primitive_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonPrimitiveOperators>();
    };
    const auto& range = expression.crange();
    if (!boost::algorithm::all_of(range, is_boson_primitive_operator)) {
        return std::nullopt;
    }
    // ***************************************************************
    // ***  make the new subexpressions                             **
    // ***************************************************************
    // ExpressionHandlerVector new_subexpressions;
    // for (const auto& subsubexpression : subproduct_range) {
    //     ExpressionHandlerVector new_subsubexpressions;
    //     new_subexpressions.push_back(ProductExpression::make_from_buffer(std::move(new_subsubexpressions)));
    // }
    assert(false);//TODO: implement
    // ***************************************************************
    // *** return the product of sorted operators                   **
    // ***************************************************************
    // return ProductExpression::make_from_buffer(std::move(new_subexpressions));
}

}  // namespace boson_algebra