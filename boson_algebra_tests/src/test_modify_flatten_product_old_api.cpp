// SELF:
#include <boson_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_flatten_product.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformFlattenProductOldApi, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformFlattenProductOldApi, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformFlattenProductOldApi, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformFlattenProductOldApi, MinimalExample1) {
    const auto expression = ('c'_an * ('a'_cr * 'b'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫❫");
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭c◦♯a◦♯b❫");
}

TEST(TransformFlattenProductOldApi, MinimalExample2) {
    const auto expression = ba::ProductExpression::make('c'_an, ('a'_cr * 'b'_cr), ('d'_an * 'a'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫◦❪♭d◦♯a❫❫");
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭c◦♯a◦♯b◦♭d◦♯a❫");
}

TEST(TransformFlattenProductOldApi, BigTest1) {
    const auto expression = make_expression_1();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪♯a◦♭b◦❪2♯c❫❫◦❴♯c+♯c❵◦❪♭d◦ℕd❫◦❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❫");
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♯a◦♭b◦❪2♯c❫◦❴♯c+♯c❵◦♭d◦ℕd◦❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❫");
}

TEST(TransformFlattenProductOldApi, BigTest2) {
    const auto expression = make_expression_2();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪♯a◦♭b◦❪2♯c❫❫+❴♯c+♯c❵+❪♭d◦ℕd❫+❴❴♭a+ℕb❵+❴♭c+ℕd❵❵❵");
    const auto transformed_expression_optional = modify_flatten_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}