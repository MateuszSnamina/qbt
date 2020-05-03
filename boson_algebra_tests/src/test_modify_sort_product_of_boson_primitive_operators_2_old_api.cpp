// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_sort_product_of_boson_primitive_operators_2.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnEmptySum) {
    const auto expression = ba::SumExpression::make();
    ASSERT_EQ(expression.str(), "𝟘");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators1) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators2) {
    const auto expression = ('b'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b❫");
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators3) {
    const auto expression = ('b'_an * 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♯b❫");
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯b◦♭b❫+❪𝕀❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators4) {
    const auto expression = ba::ProductExpression::make('b'_cr, 'b'_cr, 'b'_an, 'b'_cr, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♯b◦♭b◦♯b◦♭b❫");
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators5) {
    const auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_cr, 'b'_an, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♯b◦♭b◦♭b❫");
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators6) {
    const auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'b'_cr , 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♯b◦♭b❫");
    // desierd state: "❪♯b◦♭b◦♯b◦♭b◦♭b❫", first difference on posiotion idx2, transposition idx2<=>idx3.
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯b◦♭b◦♯b◦♭b◦♭b❫+❪♯b◦♭b◦𝕀◦♭b❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators7) {
    const auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an , 'b'_an, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♭b◦♯b❫");
    // desierd state: "❪♯b◦♭b◦♯b◦♭b◦♭b❫", first difference on posiotion idx2, transposition idx3<=>idx4.
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯b◦♭b◦♭b◦♯b◦♭b❫+❪♯b◦♭b◦♭b◦𝕀❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators8) {
    const auto expression = ba::ProductExpression::make('b'_cr, 'b'_cr, 'b'_an, 'b'_an, 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♯b◦♭b◦♭b◦♭b❫");
    // desierd state: "❪♯b◦♭b◦♯b◦♭b◦♭b❫", first difference on posiotion idx1, transposition idx1<=>idx2.
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯b◦♭b◦♯b◦♭b◦♭b❫+❪-❪♯b◦𝕀◦♭b◦♭b❫❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators9) {
    const auto expression = ba::ProductExpression::make('b'_cr, 'b'_an, 'b'_an, 'b'_cr, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯b◦♭b◦♭b◦♯b◦♯b❫");
    // desierd state: "❪♯b◦♯b◦♭b◦♯b◦♭b❫", first difference on posiotion idx1, transposition idx2<=>idx3.
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯b◦♭b◦♯b◦♭b◦♯b❫+❪♯b◦♭b◦𝕀◦♯b❫❵");
}

TEST(ModifySortProductOfBosonPrimitiveOperators2OldApi, OnProductOfBosonPrimitiveOperators10) {
    const auto expression = ba::ProductExpression::make('b'_an, 'b'_an, 'b'_cr, 'b'_cr, 'b'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭b◦♭b◦♯b◦♯b◦♯b❫");
    // desierd state: "❪♯b◦♯b◦♭b◦♯b◦♭b❫", first difference on posiotion idx0, transposition idx1<=>idx2.
    const auto transformed_expression_optional = modify_sort_product_of_boson_primitive_operators_2(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♭b◦♯b◦♭b◦♯b◦♯b❫+❪♭b◦𝕀◦♯b◦♯b❫❵");
}