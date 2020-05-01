// MY HEADER:
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_1.hpp>
// SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/adjacent_find.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/sub_range.hpp>
// STD
#include <iostream>  // debug
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
    // *** the transformation does apply to product expressions     **
    // *** with zero factors or only one factor                     **
    // ***************************************************************
    if (expression.n_subexpressions() < 2) {
        return std::nullopt;
    };
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
    // *** calculate split points --                                **
    // *** they segregate the product factors into groups           **
    // *** of operators sharing the same underlying bodon           **
    // ***************************************************************
    using ConstExpressionHandlerRandomAccessRangeIterator = boost::range_iterator<ConstExpressionHandlerRandomAccessRange>::type;  //TODO move to upper header
    using ConstExpressionHandlerRandomAccessRangeIteratorVector = std::vector<ConstExpressionHandlerRandomAccessRangeIterator>;
    const auto& get_split_points = [&range]() -> ConstExpressionHandlerRandomAccessRangeIteratorVector {
        const auto have_different_bosons = [](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
            const auto boson1 = expression1.casted_target<BosonPrimitiveOperators>().boson();
            const auto boson2 = expression2.casted_target<BosonPrimitiveOperators>().boson();
            return boson1->id() != boson2->id();
        };
        assert(boost::size(range) >= 2);
        ConstExpressionHandlerRandomAccessRangeIteratorVector split_points;
        auto it = boost::begin(range);
        while (true) {
            split_points.push_back(it);
            const boost::sub_range<ConstExpressionHandlerRandomAccessRange> rest_range{it, boost::end(range)};
            it = boost::adjacent_find(rest_range, have_different_bosons);
            if (it != boost::end(range)) {
                it++;
                assert(it != boost::end(range));
            } else {
                break;
            }
        }
        split_points.push_back(boost::end(range));
        return split_points;
    };
    ConstExpressionHandlerRandomAccessRangeIteratorVector split_points = get_split_points();
    // ***************************************************************
    // ***  make the new subexpressions                             **
    // ***************************************************************
    const unsigned n_split_points = split_points.size();
    assert(n_split_points > 0);
    const auto split_points_pairs_range = boost::combine(
        split_points | boost::adaptors::sliced(0u, n_split_points - 1u),
        split_points | boost::adaptors::sliced(1u, n_split_points));
    ExpressionHandlerVector new_subexpressions;
    for (const auto& _ : split_points_pairs_range) {
        ConstExpressionHandlerRandomAccessRangeIterator b = _.get<0>();
        ConstExpressionHandlerRandomAccessRangeIterator e = _.get<1>();
        const boost::sub_range<ConstExpressionHandlerRandomAccessRange> chunk_range{b, e};
        ExpressionHandlerVector new_subsubexpressions;
        for (const auto& subexpression : chunk_range) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        // for (ConstExpressionHandlerRandomAccessRangeIterator it = e; it != e; it++) {
        //     const ExpressionHandler& subexpression = *it;
        //     new_subsubexpressions.push_back(subexpression.clone());
        // }
        ExpressionHandler new_subexpression = ProductExpression::make_from_buffer(std::move(new_subsubexpressions));
        new_subexpressions.push_back(std::move(new_subexpression));
    }
    // assert(false);  //TODO: implement
    // ***************************************************************
    // *** return the product of sorted operators                   **
    // ***************************************************************
    return ProductExpression::make_from_buffer(std::move(new_subexpressions));
}

}  // namespace boson_algebra