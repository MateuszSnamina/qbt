// SELF:
#include <boson_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/transform_prod_factors_to_factor_prod.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(TransformProdFactorsToFactorProd, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_prod_factors_to_factor_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformProdFactorsToFactorProd, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_prod_factors_to_factor_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformProdFactorsToFactorProd, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_prod_factors_to_factor_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformProdFactorsToFactorProd, MinimalExample1) {
    const auto expression = ba::ProductExpression::make(4 * 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪4♯b❫❫");
    const auto transformed_expression_optional = transform_prod_factors_to_factor_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪4❪♯b❫❫");
}

TEST(TransformProdFactorsToFactorProd, MinimalExample2) {
    const auto expression = ba::ProductExpression::make(('a'_cr * 'b'_cr), 5 * 'c'_an, ('d'_an * 'a'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪♯a◦♯b❫◦❪5♭c❫◦❪♭d◦♯a❫❫");
    const auto transformed_expression_optional = transform_prod_factors_to_factor_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪5❪❪♯a◦♯b❫◦♭c◦❪♭d◦♯a❫❫❫");
}

TEST(TransformProdFactorsToFactorProd, MinimalExample3) {
    const auto expression = ba::ProductExpression::make(('a'_cr * 'b'_cr), 5 * 'c'_an, ('d'_an * 'a'_cr), -1 * 'd'_cr, 7 * 'a'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪♯a◦♯b❫◦❪5♭c❫◦❪♭d◦♯a❫◦❪-♯d❫◦❪7♯a❫❫");
    const auto transformed_expression_optional = transform_prod_factors_to_factor_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪-35❪❪♯a◦♯b❫◦♭c◦❪♭d◦♯a❫◦♯d◦♯a❫❫");
}