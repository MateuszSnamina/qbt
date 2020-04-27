// SELF:
#include<boson_algebra_tests/example_expressions.hpp>//TODO removed
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_simplify_factor.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformSimplifyFactor, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyFactor, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyFactor, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}