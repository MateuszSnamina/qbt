// SELF:
#include <boson_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_rebuild_factor_sum_into_sum_factors.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, OnFactoredExpression1) {
    const auto expression = (4 * 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4♯b❫");
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, OnFactoredExpression2) {
    const auto expression = (4 * ('d'_an * 'a'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❪♭d◦♯a❫❫");
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, MinimalExample1) {
    const auto expression = (4 * ('d'_an + 'a'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❴♭d+♯a❵❫");
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪4♭d❫+❪4♯a❫❵");
}

TEST(ModifyRebuildFactorSumIntoSumFactorsOldApi, MinimalExample2) {
    const auto expression = (4 * ba::SumExpression::make('d'_an, 'a'_cr, (2 * 'c'_cr)));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪4❴♭d+♯a+❪2♯c❫❵❫");
    const auto transformed_expression_optional = modify_rebuild_factor_sum_into_sum_factors(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪4♭d❫+❪4♯a❫+❪4❪2♯c❫❫❵");
}