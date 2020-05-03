// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_sort_product_of_boson_primitive_operators_1.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnBosonPrimitiveOperator) {
    auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "♯d");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnEmptySum) {
    auto expression = ba::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators1) {
    auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪♯a❫◦❪♭b❫❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators2) {
    auto expression = ('b'_an * 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♯a❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪♭b❫◦❪♯a❫❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators3) {
    auto expression = ('a'_an * 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭a◦♯a❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪♭a◦♯a❫❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators4) {
    auto expression = ba::ProductExpression::make('d'_cr, 'a'_cr, 'a'_an, 'c'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦♯a◦♭a◦♭c❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪♯d❫◦❪♯a◦♭a❫◦❪♭c❫❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators5) {
    auto expression = ba::ProductExpression::make('d'_cr, 'd'_cr, 'd'_an, 'c'_an, 'a'_cr, 'b'_an, 'b'_cr, 'c'_cr, 'a'_cr, 'b'_an, 'a'_no, 'a'_an, 'b'_an, 'c'_an, 'c'_no, 'c'_cr, 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦♯d◦♭d◦♭c◦♯a◦♭b◦♯b◦♯c◦♯a◦♭b◦ℕa◦♭a◦♭b◦♭c◦ℕc◦♯c◦♯a❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪♯d◦♯d◦♭d❫◦❪♭c❫◦❪♯a❫◦❪♭b◦♯b❫◦❪♯c❫◦❪♯a❫◦❪♭b❫◦❪ℕa◦♭a❫◦❪♭b❫◦❪♭c◦ℕc◦♯c❫◦❪♯a❫❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators6) {
    auto expression = ba::ProductExpression::make('a'_cr, 'd'_cr, 'd'_an, 'c'_an, 'a'_cr, 'b'_an, 'b'_cr, 'c'_cr, 'a'_cr, 'b'_an, 'a'_no, 'a'_an, 'b'_an, 'c'_an, 'c'_no, 'a'_cr, 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♯d◦♭d◦♭c◦♯a◦♭b◦♯b◦♯c◦♯a◦♭b◦ℕa◦♭a◦♭b◦♭c◦ℕc◦♯a◦♯a❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪❪♯a❫◦❪♯d◦♭d❫◦❪♭c❫◦❪♯a❫◦❪♭b◦♯b❫◦❪♯c❫◦❪♯a❫◦❪♭b❫◦❪ℕa◦♭a❫◦❪♭b❫◦❪♭c◦ℕc❫◦❪♯a◦♯a❫❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators1, OnHeterogeneousProductOfBosonPrimitiveOperators) {
    auto expression = 'd'_cr * ('d'_cr * 'd'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦❪♯d◦♯d❫❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_1(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯d◦❪♯d◦♯d❫❫");
}