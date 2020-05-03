// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_sort_product_of_boson_primitive_operators_2.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnBosonPrimitiveOperator) {
    auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "♯d");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnEmptySum) {
    auto expression = ba::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝟘");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnEmptyProduct) {
    auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "𝕀");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators1) {
    auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯a◦♭b❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators2) {
    auto expression = ('b'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯b◦♭b❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators3) {
    auto expression = ('b'_an * 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♯b❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪♯b◦♭b❫+❪𝕀❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators4) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_cr, 'b'_an, 'b'_cr, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♯b◦♭b◦♯b◦♭b❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯b◦♯b◦♭b◦♯b◦♭b❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators5) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_cr, 'b'_an, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♯b◦♭b◦♭b❫");
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_FALSE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❪♯b◦♭b◦♯b◦♭b◦♭b❫");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators6) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'b'_cr, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♯b◦♭b❫");
    // desierd state: "❪♯b◦♭b◦♯b◦♭b◦♭b❫", first difference on posiotion idx2, transposition idx2<=>idx3.
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪♯b◦♭b◦♯b◦♭b◦♭b❫+❪♯b◦♭b◦𝕀◦♭b❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators7) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'b'_an, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♭b◦♯b❫");
    // desierd state: "❪♯b◦♭b◦♯b◦♭b◦♭b❫", first difference on posiotion idx2, transposition idx3<=>idx4.
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪♯b◦♭b◦♭b◦♯b◦♭b❫+❪♯b◦♭b◦♭b◦𝕀❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators8) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_cr, 'b'_an, 'b'_an, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♯b◦♭b◦♭b◦♭b❫");
    // desierd state: "❪♯b◦♭b◦♯b◦♭b◦♭b❫", first difference on posiotion idx1, transposition idx1<=>idx2.
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪♯b◦♭b◦♯b◦♭b◦♭b❫+❪-❪♯b◦𝕀◦♭b◦♭b❫❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators9) {
    auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'b'_cr, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♯b◦♯b❫");
    // desierd state: "❪♯b◦♯b◦♭b◦♯b◦♭b❫", first difference on posiotion idx1, transposition idx2<=>idx3.
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪♯b◦♭b◦♯b◦♭b◦♯b❫+❪♯b◦♭b◦𝕀◦♯b❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2, OnProductOfBosonPrimitiveOperators10) {
    auto expression = ba::ProductExpression::make('b'_an, 'b'_an, 'b'_cr, 'b'_cr, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♭b◦♯b◦♯b◦♯b❫");
    // desierd state: "❪♯b◦♯b◦♭b◦♯b◦♭b❫", first difference on posiotion idx0, transposition idx1<=>idx2.
    const auto modification_result = modify_sort_product_of_boson_primitive_operators_2_new_api(std::move(expression));
    ASSERT_TRUE(modification_result);
    const auto& modified_expression = *modification_result;
    //std::cout << modified_expression.str() << std::endl;
    ASSERT_EQ(modified_expression.str(), "❴❪♭b◦♯b◦♭b◦♯b◦♯b❫+❪♭b◦𝕀◦♯b◦♯b❫❵");
}