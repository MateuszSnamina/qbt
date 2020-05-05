// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_substitute_cr_an_with_no.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifySubstituteCrAnWithNo, OnBosonPrimitiveOperator) {
    auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "♯d");
}

TEST(ModifySubstituteCrAnWithNo, OnEmptySum) {
    auto expression = ba::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifySubstituteCrAnWithNo, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators1) {
    auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators2) {
    auto expression = ('b'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪ℕb❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators3) {
    auto expression = ('b'_an * 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♯b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♭b◦♯b❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators4) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_cr, 'b'_an, 'b'_cr, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♯b◦♭b◦♯b◦♭b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯b◦ℕb◦ℕb❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators5) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_cr, 'b'_an, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♯b◦♭b◦♭b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪ℕb◦ℕb◦♭b❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators6) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'b'_cr, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♯b◦♭b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪ℕb◦♭b◦ℕb❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators7) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'a'_an, 'a'_an, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭a◦♭a◦♯b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪ℕb◦♭a◦♭a◦♯b❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators8) {
    auto expression = ba::ProductExpression::make('d'_cr, 'b'_cr, 'b'_an, 'c'_an, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯d◦♯b◦♭b◦♭c◦♭b❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯d◦ℕb◦♭c◦♭b❫");
}

TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators9) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'c'_cr, 'c'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♯c◦♭c❫");
    const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪ℕb◦♭b◦ℕc❫");
}

// TEST(ModifySubstituteCrAnWithNo, OnProductOfBosonPrimitiveOperators10) {
//     auto expression = ba::ProductExpression::make('b'_an, 'b'_an, 'b'_cr, 'b'_cr, 'b'_cr);
//     //std::cout << expression.str() << std::endl;
//     ASSERT_EQ(expression.str(), "❪♭b◦♭b◦♯b◦♯b◦♯b❫");
//     const auto modification_result = modify_substitute_cr_an_with_no(std::move(expression));
//     ASSERT_TRUE(modification_result);
//     const auto& modified_expression = *modification_result;
//     //std::cout << modified_expression.str() << std::endl;
//     ASSERT_EQ(modified_expression.str(), "❴❪♭b◦♯b◦♭b◦♯b◦♯b❫+❪♭b◦𝕀◦♯b◦♯b❫❵");
// }