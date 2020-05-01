// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_1.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnEmptySum) {
    const auto expression = ba::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_FALSE(transformed_expression_optional);
    // const auto& transformed_expression = *transformed_expression_optional;
    // //std::cout << transformed_expression.str() << std::endl;
    // ASSERT_EQ(transformed_expression.str(), "𝕀");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators1) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪♯a❫◦❪♭b❫❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators2) {
    const auto expression = ('b'_an * 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♯a❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪♭b❫◦❪♯a❫❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators3) {
    const auto expression = ('a'_an * 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭a◦♯a❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪♭a◦♯a❫❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators4) {
    const auto expression = ba::ProductExpression::make('d'_cr, 'a'_cr, 'a'_an, 'c'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦♯a◦♭a◦♭c❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪♯d❫◦❪♯a◦♭a❫◦❪♭c❫❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators5) {
    const auto expression = ba::ProductExpression::make('d'_cr, 'd'_cr, 'd'_an, 'c'_an, 'a'_cr, 'b'_an, 'b'_cr, 'c'_cr, 'a'_cr, 'b'_an, 'a'_no, 'a'_an, 'b'_an, 'c'_an, 'c'_no, 'c'_cr, 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦♯d◦♭d◦♭c◦♯a◦♭b◦♯b◦♯c◦♯a◦♭b◦ℕa◦♭a◦♭b◦♭c◦ℕc◦♯c◦♯a❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    // //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪♯d◦♯d◦♭d❫◦❪♭c❫◦❪♯a❫◦❪♭b◦♯b❫◦❪♯c❫◦❪♯a❫◦❪♭b❫◦❪ℕa◦♭a❫◦❪♭b❫◦❪♭c◦ℕc◦♯c❫◦❪♯a❫❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnProductOfBosonPrimitiveOperators6) {
    const auto expression = ba::ProductExpression::make('a'_cr, 'd'_cr, 'd'_an, 'c'_an, 'a'_cr, 'b'_an, 'b'_cr, 'c'_cr, 'a'_cr, 'b'_an, 'a'_no, 'a'_an, 'b'_an, 'c'_an, 'c'_no, 'a'_cr, 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♯d◦♭d◦♭c◦♯a◦♭b◦♯b◦♯c◦♯a◦♭b◦ℕa◦♭a◦♭b◦♭c◦ℕc◦♯a◦♯a❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    // //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪❪♯a❫◦❪♯d◦♭d❫◦❪♭c❫◦❪♯a❫◦❪♭b◦♯b❫◦❪♯c❫◦❪♯a❫◦❪♭b❫◦❪ℕa◦♭a❫◦❪♭b❫◦❪♭c◦ℕc❫◦❪♯a◦♯a❫❫");
}

TEST(TransformSortProductOfBosonPrimitiveOperators1, OnHeterogeneousProductOfBosonPrimitiveOperators) {
    const auto expression = 'd'_cr * ('d'_cr * 'd'_cr);
    // std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦❪♯d◦♯d❫❫");
    const auto transformed_expression_optional = transform_sort_product_of_boson_primitive_operators_1(expression);
    ASSERT_FALSE(transformed_expression_optional);
}