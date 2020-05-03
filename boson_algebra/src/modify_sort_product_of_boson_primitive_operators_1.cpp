// MY HEADER:
#include <boson_algebra/modify_sort_product_of_boson_primitive_operators_1.hpp>
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
#include <iostream>  // debug TODO
#include <iterator>

namespace boson_algebra {

ModificationResult modify_sort_product_of_boson_primitive_operators_1_new_api(ExpressionHandler&& expression){
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** the transformation does apply to product expressions     **
    // *** with zero factors or only one factor                     **
    // ***************************************************************
    if (expression.n_subexpressions() < 2) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    };
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** with factors being of BosonPrimitiveOperators type       **
    // ***************************************************************
    const auto is_boson_primitive_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonPrimitiveOperators>();
    };
    const auto& range = expression.range();
    if (!boost::algorithm::all_of(range, is_boson_primitive_operator)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** calculate split points --                                **
    // *** they segregate the product factors into groups           **
    // *** of operators sharing the same underlying bodon           **
    // ***************************************************************
    using ExpressionHandlerRandomAccessRangeIteratorVector = std::vector<ExpressionHandlerRandomAccessRangeIterator>;
    const auto& get_split_points = [&range]() -> ExpressionHandlerRandomAccessRangeIteratorVector {
        const auto have_different_bosons = [](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
            const auto boson1 = expression1.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
            const auto boson2 = expression2.casted_target<BosonPrimitiveOperators>().unwrap().get().boson();
            return boson1->id() != boson2->id();
        };
        assert(boost::size(range) >= 2);
        ExpressionHandlerRandomAccessRangeIteratorVector split_points;
        auto it = boost::begin(range);
        while (true) {
            split_points.push_back(it);
            const boost::sub_range<ExpressionHandlerRandomAccessRange> rest_range{it, boost::end(range)};
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
    ExpressionHandlerRandomAccessRangeIteratorVector split_points = get_split_points();
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
        ExpressionHandlerRandomAccessRangeIterator b = _.get<0>();
        ExpressionHandlerRandomAccessRangeIterator e = _.get<1>();
        const boost::sub_range<ExpressionHandlerRandomAccessRange> chunk_range{b, e};
        ExpressionHandlerVector new_subsubexpressions;
        for (auto& subexpression : chunk_range) {
            new_subsubexpressions.push_back(std::move(subexpression));
        }
        ExpressionHandler new_subexpression = ProductExpression::make_from_buffer(std::move(new_subsubexpressions));
        new_subexpressions.push_back(std::move(new_subexpression));
    }
    // ***************************************************************
    // *** return the product of grouped operators                  **
    // ***************************************************************
    auto new_product = ProductExpression::make_from_buffer(std::move(new_subexpressions));
    return ModificationResult::make_generated_result(std::move(new_product));
}

}  // namespace boson_algebra