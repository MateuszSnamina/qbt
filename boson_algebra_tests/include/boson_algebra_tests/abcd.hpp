#ifndef BOSON_ALGEBRA_TEST_ABCD_HPP
#define BOSON_ALGEBRA_TEST_ABCD_HPP

#include <boson_algebra/expression_all.hpp>

namespace ba = boson_algebra;

extern const std::shared_ptr<boson_algebra::Boson> a;
extern const std::shared_ptr<boson_algebra::Boson> b;
extern const std::shared_ptr<boson_algebra::Boson> c;
extern const std::shared_ptr<boson_algebra::Boson> d;

inline boson_algebra::ExpressionHandler cr_a() {
    return boson_algebra::BosonCreationOperator::make(a);
}

inline boson_algebra::ExpressionHandler an_a() {
    return boson_algebra::BosonAnnihilationOperator::make(a);
}

inline boson_algebra::ExpressionHandler n_a() {
    return boson_algebra::BosonNumberOperator::make(a);
}

inline boson_algebra::ExpressionHandler cr_b() {
    return boson_algebra::BosonCreationOperator::make(b);
}

inline boson_algebra::ExpressionHandler an_b() {
    return boson_algebra::BosonAnnihilationOperator::make(b);
}

inline boson_algebra::ExpressionHandler n_b() {
    return boson_algebra::BosonNumberOperator::make(b);
}

inline boson_algebra::ExpressionHandler cr_c() {
    return boson_algebra::BosonCreationOperator::make(c);
}

inline boson_algebra::ExpressionHandler an_c() {
    return boson_algebra::BosonAnnihilationOperator::make(c);
}

inline boson_algebra::ExpressionHandler n_c() {
    return boson_algebra::BosonNumberOperator::make(c);
}

inline boson_algebra::ExpressionHandler cr_d() {
    return boson_algebra::BosonCreationOperator::make(d);
}

inline boson_algebra::ExpressionHandler an_d() {
    return boson_algebra::BosonAnnihilationOperator::make(d);
}

inline boson_algebra::ExpressionHandler n_d() {
    return boson_algebra::BosonNumberOperator::make(d);
}

#endif