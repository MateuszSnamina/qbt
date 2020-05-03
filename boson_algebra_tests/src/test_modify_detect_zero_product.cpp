// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_detect_zero_product.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifyDetectZeroProduct, OnBosonPrimitiveOperator) {
    auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnProductOfBosonPrimitiveOperators) {
    auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnFactorExpression) {
    auto expression = (4 * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4♭b❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnNestedFactorExpression) {
    auto expression = (4 * (-6 * 'b'_an));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❪-6♭b❫❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}

TEST(ModifyDetectZeroProduct, OnZeroProduct1) {
    auto expression = (ba::SumExpression::make_zero() * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪𝟘◦♭b❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroProduct, OnZeroProduct2) {
    auto expression = ba::ProductExpression::make('b'_an, ba::SumExpression::make_zero(), 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦𝟘◦♭b❫");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyDetectZeroProduct, OnSumWithZero) {
    auto expression = (ba::SumExpression::make_zero() + 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴𝟘+♭b❵");
    const auto modification_result = modify_detect_zero_product(std::move(expression));
    ASSERT_FALSE(modification_result);
}