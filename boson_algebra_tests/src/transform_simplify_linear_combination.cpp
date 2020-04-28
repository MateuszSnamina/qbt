// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_simplify_linear_combination.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformSimplifyLinearCombination, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyLinearCombination, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyLinearCombination, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyLinearCombination, OnFactorExpression) {
    const auto expression = (4 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4♭b❫");
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyLinearCombination, MinimalWorkingExample1) {
    const auto expression = (4 * 'b'_an) + (7 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪4♭b❫+❪7♭b❫❫");
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪11♭b❫❫");
}

TEST(TransformSimplifyLinearCombination, MinimalWorkingExample2) {
    const auto expression = ba::SumExpression::make((4 * 'b'_an), (12 * 'a'_an), (-7 * 'b'_an), (31 * 'b'_cr), (5 * 'a'_an));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪4♭b❫+❪12♭a❫+❪-7♭b❫+❪31♯b❫+❪5♭a❫❫");
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪-3♭b❫+❪17♭a❫+❪31♯b❫❫");
}

TEST(TransformSimplifyLinearCombination, MinimalNotWorkingExample1) {
    const auto expression = (4 * 'b'_an) * (4 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪4♭b❫◦❪4♭b❫❫");
    const auto transformed_expression_optional = transform_simplify_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}