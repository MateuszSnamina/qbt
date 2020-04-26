#include <gtest/gtest.h>

#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/transform_simplify_product.hpp>

using namespace boson_algebra;

const std::shared_ptr<Boson> a = std::make_shared<CharBoson>('a');
const std::shared_ptr<Boson> b = std::make_shared<CharBoson>('b');
const std::shared_ptr<Boson> c = std::make_shared<CharBoson>('c');
const std::shared_ptr<Boson> d = std::make_shared<CharBoson>('d');

ExpressionHandler cr_a() {
    return BosonCreationOperator::make(a);
}

ExpressionHandler an_a() {
    return BosonAnihilationOperator::make(a);
}

ExpressionHandler n_a() {
    return BosonNumberOperator::make(a);
}

ExpressionHandler cr_b() {
    return BosonCreationOperator::make(b);
}

ExpressionHandler an_b() {
    return BosonAnihilationOperator::make(b);
}

ExpressionHandler n_b() {
    return BosonNumberOperator::make(b);
}

ExpressionHandler cr_c() {
    return BosonCreationOperator::make(c);
}

ExpressionHandler an_c() {
    return BosonAnihilationOperator::make(c);
}

ExpressionHandler n_c() {
    return BosonNumberOperator::make(c);
}

ExpressionHandler cr_d() {
    return BosonCreationOperator::make(d);
}

ExpressionHandler an_d() {
    return BosonAnihilationOperator::make(d);
}

ExpressionHandler n_d() {
    return BosonNumberOperator::make(d);
}

ExpressionHandler make_expression_1() {
    ExpressionHandler double_cr_c = IntegerFactoredExpression::make(2, cr_c());
    ExpressionHandler expr01 = ProductExpression::make(cr_a(), an_b(), std::move(double_cr_c));
    ExpressionHandler expr02 = SumExpression::make(cr_c(), cr_c());
    ExpressionHandler expr03 = ProductExpression::make(an_d(), n_d());
    ExpressionHandler expr040 = SumExpression::make(an_a(), n_b());
    ExpressionHandler expr041 = SumExpression::make(an_c(), n_d());
    ExpressionHandler expr04 = SumExpression::make(std::move(expr040), std::move(expr041));
    ExpressionHandler expr0 = ProductExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

ExpressionHandler make_expression_2() {
    ExpressionHandler double_cr_c = IntegerFactoredExpression::make(2, cr_c());
    ExpressionHandler expr01 = ProductExpression::make(cr_a(), an_b(), std::move(double_cr_c));
    ExpressionHandler expr02 = SumExpression::make(cr_c(), cr_c());
    ExpressionHandler expr03 = ProductExpression::make(an_d(), n_d());
    ExpressionHandler expr040 = SumExpression::make(an_a(), n_b());
    ExpressionHandler expr041 = SumExpression::make(an_c(), n_d());
    ExpressionHandler expr04 = SumExpression::make(std::move(expr040), std::move(expr041));
    ExpressionHandler expr0 = SumExpression::make(std::move(expr01), std::move(expr02), std::move(expr03), std::move(expr04));
    return expr0;
}

TEST(TransformSimplifyProduct, OnBosonPrimitiveOperator) {
    const auto expression = cr_d();
    ASSERT_EQ(expression.str(), "♯d");
    //std::cout << expression.str() << std::endl;
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyProduct, OnEmptyProduct) {
    const auto expression = ProductExpression::make();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "𝕀");
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyProduct, OnProductOfBosonPrimitiveOperators) {
    const auto expression = ProductExpression::make(cr_a(), an_b());
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♯a◦♭b❫");
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}

TEST(TransformSimplifyProduct, MinimalExample1) {
    const auto expression = ProductExpression::make(an_c(), ProductExpression::make(cr_a(), cr_b()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫❫");
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭c◦♯a◦♯b❫");
}

TEST(TransformSimplifyProduct, MinimalExample2) {
    const auto expression = ProductExpression::make(an_c(), ProductExpression::make(cr_a(), cr_b()), ProductExpression::make(an_d(), cr_a()));
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪♭c◦❪♯a◦♯b❫◦❪♭d◦♯a❫❫");
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♭c◦♯a◦♯b◦❪♭d◦♯a❫❫");
}

TEST(TransformSimplifyProduct, BigTest1) {
    const auto expression = make_expression_1();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪♯a◦♭b◦❪2♯c❫❫◦❪♯c+♯c❫◦❪♭d◦ℕd❫◦❪❪♭a+ℕb❫+❪♭c+ℕd❫❫❫");
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_TRUE(transformed_expression_optional);
    const auto& transformed_expression = *transformed_expression_optional;
    //std::cout << transformed_expression.str() << std::endl;
    ASSERT_EQ(transformed_expression.str(), "❪♯a◦♭b◦❪2♯c❫◦❪♯c+♯c❫◦❪♭d◦ℕd❫◦❪❪♭a+ℕb❫+❪♭c+ℕd❫❫❫");
}

TEST(TransformSimplifyProduct, BigTest2) {
    const auto expression = make_expression_2();
    //std::cout << expression.str() << std::endl;
    ASSERT_EQ(expression.str(), "❪❪♯a◦♭b◦❪2♯c❫❫+❪♯c+♯c❫+❪♭d◦ℕd❫+❪❪♭a+ℕb❫+❪♭c+ℕd❫❫❫");
    const auto transformed_expression_optional = transform_simplify_product(expression);
    ASSERT_FALSE(transformed_expression_optional);
}
