#ifndef BOSON_ALGEBRA_TEST_ABCD_HPP
#define BOSON_ALGEBRA_TEST_ABCD_HPP

#include <boson_algebra/expression_all.hpp>

const std::shared_ptr<boson_algebra::Boson> a = boson_algebra::CharBoson::make('a');
const std::shared_ptr<boson_algebra::Boson> b = boson_algebra::CharBoson::make('b');
const std::shared_ptr<boson_algebra::Boson> c = boson_algebra::CharBoson::make('c');
const std::shared_ptr<boson_algebra::Boson> d = boson_algebra::CharBoson::make('d');

inline boson_algebra::ExpressionHandler cr_a() {
    return boson_algebra::BosonCreationOperator::make(a);
}

inline boson_algebra::ExpressionHandler an_a() {
    return boson_algebra::BosonAnihilationOperator::make(a);
}

inline boson_algebra::ExpressionHandler n_a() {
    return boson_algebra::BosonNumberOperator::make(a);
}

inline boson_algebra::ExpressionHandler cr_b() {
    return boson_algebra::BosonCreationOperator::make(b);
}

inline boson_algebra::ExpressionHandler an_b() {
    return boson_algebra::BosonAnihilationOperator::make(b);
}

inline boson_algebra::ExpressionHandler n_b() {
    return boson_algebra::BosonNumberOperator::make(b);
}

inline boson_algebra::ExpressionHandler cr_c() {
    return boson_algebra::BosonCreationOperator::make(c);
}

inline boson_algebra::ExpressionHandler an_c() {
    return boson_algebra::BosonAnihilationOperator::make(c);
}

inline boson_algebra::ExpressionHandler n_c() {
    return boson_algebra::BosonNumberOperator::make(c);
}

inline boson_algebra::ExpressionHandler cr_d() {
    return boson_algebra::BosonCreationOperator::make(d);
}

inline boson_algebra::ExpressionHandler an_d() {
    return boson_algebra::BosonAnihilationOperator::make(d);
}

inline boson_algebra::ExpressionHandler n_d() {
    return boson_algebra::BosonNumberOperator::make(d);
}

inline boson_algebra::ExpressionHandler make_expression_1() {
    boson_algebra::ExpressionHandler double_cr_c = boson_algebra::IntegerFactoredExpression::make(2, cr_c());
    boson_algebra::ExpressionHandler expr01 = boson_algebra::ProductExpression::make(cr_a(), an_b(), std::move(double_cr_c));
    boson_algebra::ExpressionHandler expr02 = boson_algebra::SumExpression::make(cr_c(), cr_c());
    boson_algebra::ExpressionHandler expr03 = boson_algebra::ProductExpression::make(an_d(), n_d());
    boson_algebra::ExpressionHandler expr040 = boson_algebra::SumExpression::make(an_a(), n_b());
    boson_algebra::ExpressionHandler expr041 = boson_algebra::SumExpression::make(an_c(), n_d());
    boson_algebra::ExpressionHandler expr04 = boson_algebra::SumExpression::make(std::move(expr040), std::move(expr041));
    boson_algebra::ExpressionHandler expr0 = boson_algebra::ProductExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

inline boson_algebra::ExpressionHandler make_expression_2() {
    boson_algebra::ExpressionHandler double_cr_c = boson_algebra::IntegerFactoredExpression::make(2, cr_c());
    boson_algebra::ExpressionHandler expr01 = boson_algebra::ProductExpression::make(cr_a(), an_b(), std::move(double_cr_c));
    boson_algebra::ExpressionHandler expr02 = boson_algebra::SumExpression::make(cr_c(), cr_c());
    boson_algebra::ExpressionHandler expr03 = boson_algebra::ProductExpression::make(an_d(), n_d());
    boson_algebra::ExpressionHandler expr040 = boson_algebra::SumExpression::make(an_a(), n_b());
    boson_algebra::ExpressionHandler expr041 = boson_algebra::SumExpression::make(an_c(), n_d());
    boson_algebra::ExpressionHandler expr04 = boson_algebra::SumExpression::make(std::move(expr040), std::move(expr041));
    boson_algebra::ExpressionHandler expr0 = boson_algebra::SumExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

#endif