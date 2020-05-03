// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_rebuild_prod_sum_into_sum_prod.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;
using namespace ba::operators;

TEST(ModifyRebuildProdSumIntoSumProd, OnBosonPrimitiveOperator) {
    const auto expression = 'd'_cr;
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildProdSumIntoSumProd, OnEmptyProduct) {
    const auto expression = ba::ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildProdSumIntoSumProd, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ('a'_cr * 'b'_an);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample1) {
    const auto expression = ba::ProductExpression::make('a'_cr, ('b'_an + 'c'_cr), 'd'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦❴♭b+♯c❵◦♯d❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯a◦♭b◦♯d❫+❪♯a◦♯c◦♯d❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample2) {
    const auto expression = ('a'_cr * ('b'_an + 'c'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦❴♭b+♯c❵❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♯a◦♭b❫+❪♯a◦♯c❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample3) {
    const auto expression = (('b'_an + 'c'_cr) * 'd'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴♭b+♯c❵◦♯d❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♭b◦♯d❫+❪♯c◦♯d❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample4) {
    const auto expression = ba::ProductExpression::make(('b'_an + 'c'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴♭b+♯c❵❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
    // const auto& transformed_expression = *transformed_expression_optional;
    // //std::cout << transformed_expression.str() << std::endl;
    // ASSERT_EQ(transformed_expression.str(), "❴❪♭b❫+❪♯c❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample5) {
    const auto expression = (('b'_an + 'c'_cr) * (2 * 'd'_cr));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❴♭b+♯c❵◦❪2♯d❫❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❴❪♭b◦❪2♯d❫❫+❪♯c◦❪2♯d❫❫❵");
}

TEST(ModifyRebuildProdSumIntoSumProd, MinimalExample6) {
    const auto expression = ba::ProductExpression::make('a'_cr, ('b'_an * 'c'_cr), 'd'_cr);
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦❪♭b◦♯c❫◦♯d❫");
    const auto transformed_expression_optional = modify_rebuild_prod_sum_into_sum_prod(expression);
    ASSERT_FALSE(transformed_expression_optional);
}