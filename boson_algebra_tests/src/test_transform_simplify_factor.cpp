// SELF:
#include<boson_algebra_tests/abcd.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/transform_simplify_factor.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;

TEST(TransformSimplifyFactor, OnBosonPrimitiveOperator) {
    const auto expression = cr_d();
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyFactor, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyFactor, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ba::ProductExpression::make(cr_a(), an_b());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyFactor, MinimalExample1) {
    const auto expression = ba::ProductExpression::make(an_c(), ba::ProductExpression::make(cr_a(), cr_b()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫❫");
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭c◦♯a◦♯b❫");
}

TEST(TransformSimplifyFactor, MinimalExample2) {
    const auto expression = ba::ProductExpression::make(an_c(), ba::ProductExpression::make(cr_a(), cr_b()), ba::ProductExpression::make(an_d(), cr_a()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫◦❪♭d◦♯a❫❫");
    const auto transformed_expression_optional = transform_simplify_factor(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭c◦♯a◦♯b◦♭d◦♯a❫");
}

// TEST(TransformSimplifyFactor, BigTest1) {
//     const auto expression = make_expression_1();
//     //std::cout << expression.str() << std::endl;
//     ASSERT_EQ(expression.str(), "❪❪♯a◦♭b◦❪2♯c❫❫◦❪♯c+♯c❫◦❪♭d◦ℕd❫◦❪❪♭a+ℕb❫+❪♭c+ℕd❫❫❫");
//     const auto transformed_expression_optional = transform_simplify_product(expression);
//     ASSERT_TRUE(transformed_expression_optional);
//     const auto& transformed_expression = *transformed_expression_optional;
//     //std::cout << transformed_expression.str() << std::endl;
//     ASSERT_EQ(transformed_expression.str(), "❪♯a◦♭b◦❪2♯c❫◦❪♯c+♯c❫◦♭d◦ℕd◦❪❪♭a+ℕb❫+❪♭c+ℕd❫❫❫");
// }

// TEST(TransformSimplifyFactor, BigTest2) {
//     const auto expression = make_expression_2();
//     //std::cout << expression.str() << std::endl;
//     ASSERT_EQ(expression.str(), "❪❪♯a◦♭b◦❪2♯c❫❫+❪♯c+♯c❫+❪♭d◦ℕd❫+❪❪♭a+ℕb❫+❪♭c+ℕd❫❫❫");
//     const auto transformed_expression_optional = transform_simplify_product(expression);
//     ASSERT_FALSE(transformed_expression_optional);
// }
