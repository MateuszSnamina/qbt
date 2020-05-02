// SELF:
#include <boson_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_sum_to_linear_combination.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformSumToLinearCombination, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_sum_to_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSumToLinearCombination, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_sum_to_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSumToLinearCombination, OnEmptySum) {
    const auto expression = ba::SumExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝟘");
    const auto transformed_expression_optional = transform_sum_to_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSumToLinearCombination, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_sum_to_linear_combination(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSumToLinearCombination, OnSumOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr + 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴♯a+♭b❵");
    const auto transformed_expression_optional = transform_sum_to_linear_combination(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪+♯a❫+❪+♭b❫❵");
}

TEST(TransformSumToLinearCombination, BigExample1) {
    const auto expression = ba::SumExpression::make((4*'c'_an), ('a'_cr * 'b'_cr), (5*'a'_an), 'd'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4♭c❫+❪♯a◦♯b❫+❪5♭a❫+♭d❵");
    const auto transformed_expression_optional = transform_sum_to_linear_combination(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪4♭c❫+❪+❪♯a◦♯b❫❫+❪5♭a❫+❪+♭d❫❵");
}