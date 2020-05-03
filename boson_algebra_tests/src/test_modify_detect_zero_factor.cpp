// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_detect_zero_factor.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifyDetectZeroFactor, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyDetectZeroFactor, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyDetectZeroFactor, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyDetectZeroFactor, OnNoZeroFactorExpression) {
    const auto expression = (4 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4♭b❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression1) {
    const auto expression = (0 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪0♭b❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression2) {
    const auto expression = (4 * ba::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4𝟘❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression3) {
    const auto expression = (0 * ba::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪0𝟘❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnNestedFactorExpression) {
    const auto expression = (4 * (0 * 'b'_an));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❪0♭b❫❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyDetectZeroFactor, NotWorking) {
    const auto expression = (4 * (ba::SumExpression::make_zero() + ba::SumExpression::make_zero()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❴𝟘+𝟘❵❫");
    const auto transformed_expression_optional = modify_detect_zero_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}