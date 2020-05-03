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
    auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "♯d");
}

TEST(ModifyDetectZeroFactor, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyDetectZeroFactor, OnProductOfBosonPrimitiveOperators) {
    auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
}

TEST(ModifyDetectZeroFactor, OnNoZeroFactorExpression) {
    auto expression = (4 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4♭b❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪4♭b❫");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression1) {
    auto expression = (0 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪0♭b❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression2) {
    auto expression = (4 * ba::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4𝟘❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnZeroFactorExpression3) {
    auto expression = (0 * ba::SumExpression::make_zero());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪0𝟘❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroFactor, OnNestedFactorExpression) {
    auto expression = (4 * (0 * 'b'_an));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❪0♭b❫❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroFactor, NotWorking) {
    auto expression = (4 * (ba::SumExpression::make_zero() + ba::SumExpression::make_zero()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❴𝟘+𝟘❵❫");
    const auto modification_result = modify_detect_zero_factor(std::move(expression));
    ASSERT_FALSE(modification_result);
}