// SELF:
#include <boson_algebra_tests/example_expressions.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_rebuild_sum_into_linear_combination.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifyRebuildSumIntoLinearCombination, OnBosonPrimitiveOperator) {
    auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_rebuild_sum_into_linear_combination_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "♯d");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_rebuild_sum_into_linear_combination_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnEmptySum) {
    auto expression = ba::SumExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝟘");
    const auto modification_result = modify_rebuild_sum_into_linear_combination_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnProductOfBosonPrimitiveOperators) {
    auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto modification_result = modify_rebuild_sum_into_linear_combination_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
}

TEST(ModifyRebuildSumIntoLinearCombination, OnSumOfBosonPrimitiveOperators) {
    auto expression = ('a'_cr + 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴♯a+♭b❵");
    const auto modification_result = modify_rebuild_sum_into_linear_combination_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪+♯a❫+❪+♭b❫❵");
}

TEST(ModifyRebuildSumIntoLinearCombination, BigExample1) {
    auto expression = ba::SumExpression::make((4 * 'c'_an), ('a'_cr * 'b'_cr), (5 * 'a'_an), 'd'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❴❪4♭c❫+❪♯a◦♯b❫+❪5♭a❫+♭d❵");
    const auto modification_result = modify_rebuild_sum_into_linear_combination_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪4♭c❫+❪+❪♯a◦♯b❫❫+❪5♭a❫+❪+♭d❫❵");
}