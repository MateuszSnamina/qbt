// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_detect_zero_product.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformDetectZeroProduct, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformDetectZeroProduct, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformDetectZeroProduct, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformDetectZeroProduct, OnFactorExpression) {
    const auto expression = (4 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4♭b❫");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformDetectZeroProduct, OnNestedFactorExpression) {
    const auto expression = (4 * (-6 * 'b'_an));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❪-6♭b❫❫");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformDetectZeroProduct, OnZeroProduct1) {
    const auto expression = (ba::SumExpression::make_zero() * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘◦♭b❫");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "𝟘");
}

TEST(TransformDetectZeroProduct, OnZeroProduct2) {
    const auto expression = ba::ProductExpression::make('b'_an, ba::SumExpression::make_zero(), 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦𝟘◦♭b❫");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "𝟘");
}

TEST(TransformDetectZeroProduct, OnSumWithZero) {
    const auto expression = (ba::SumExpression::make_zero() + 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘+♭b❫");
    const auto transformed_expression_optional = transform_detect_zero_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}