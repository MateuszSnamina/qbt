// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_0.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformSortProductOfBosonPrimitiveOperators, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSortProductOfBosonPrimitiveOperators, OnEmptySum) {
    const auto expression = ba::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSortProductOfBosonPrimitiveOperators, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "𝕀");
}

TEST(TransformSortProductOfBosonPrimitiveOperators, OnProductOfBosonPrimitiveOperators1) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♯a◦♭b❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators, OnProductOfBosonPrimitiveOperators2) {
    const auto expression = ('b'_an * 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♯a❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♯a◦♭b❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators, OnProductOfBosonPrimitiveOperators3) {
    const auto expression = ba::ProductExpression::make('d'_cr, 'b'_cr, 'a'_an, 'c'_an, 'a'_cr, 'b'_an, 'b'_cr, 'c'_cr, 'a'_cr, 'b'_an, 'a'_no, 'a'_an, 'b'_an, 'c'_an, 'd'_no, 'b'_cr, 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦♯b◦♭a◦♭c◦♯a◦♭b◦♯b◦♯c◦♯a◦♭b◦ℕa◦♭a◦♭b◦♭c◦ℕd◦♯b◦♯a❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭a◦♯a◦♯a◦ℕa◦♭a◦♯a◦♯b◦♭b◦♯b◦♭b◦♭b◦♯b◦♭c◦♯c◦♭c◦♯d◦ℕd❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators, OnHeterogeneousProductOfBosonPrimitiveOperators3) {
    const auto expression = 'd'_cr * ('d'_cr * 'd'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦❪♯d◦♯d❫❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_0(expression);
    ASSERT_FALSE(transformed_expression_optional);
}