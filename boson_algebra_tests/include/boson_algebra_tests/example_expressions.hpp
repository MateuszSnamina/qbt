#ifndef BOSON_ALGEBRA_TEST_EXAMPLE_EXPRESSION_HPP
#define BOSON_ALGEBRA_TEST_EXAMPLE_EXPRESSION_HPP

#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

inline boson_algebra::ExpressionHandler make_expression_1() {
    boson_algebra::ExpressionHandler expr01 = boson_algebra::ProductExpression::make('a'_cr, 'b'_an, (2 * 'c'_cr));
    boson_algebra::ExpressionHandler expr02 = ('c'_cr + 'c'_cr);
    boson_algebra::ExpressionHandler expr03 = ('d'_an * 'd'_no);
    boson_algebra::ExpressionHandler expr04 = (('a'_an + 'b'_no) + ('c'_an + 'd'_no));
    boson_algebra::ExpressionHandler expr0 = boson_algebra::ProductExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

inline boson_algebra::ExpressionHandler make_expression_2() {
    boson_algebra::ExpressionHandler expr01 = boson_algebra::ProductExpression::make('a'_cr, 'b'_an, (2 * 'c'_cr));
    boson_algebra::ExpressionHandler expr02 = ('c'_cr + 'c'_cr);
    boson_algebra::ExpressionHandler expr03 = ('d'_an * 'd'_no);
    boson_algebra::ExpressionHandler expr04 = (('a'_an + 'b'_no) + ('c'_an + 'd'_no));
    boson_algebra::ExpressionHandler expr0 = boson_algebra::SumExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

#endif