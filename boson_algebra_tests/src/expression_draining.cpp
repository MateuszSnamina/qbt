// SELF:
#include <boson_algebra_tests/abcd.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;

TEST(Draining, Test0) {
    auto expression = ba::ProductExpression::make(cr_b(), cr_a(), an_d());
    ASSERT_EQ(expression.str(), "❪♯b◦♯a◦♭d❫");

    ASSERT_FALSE(expression.subexpression(0).is_drained());
    ASSERT_FALSE(expression.subexpression(1).is_drained());
    ASSERT_FALSE(expression.subexpression(2).is_drained());

    auto& expression_ref = expression.subexpression(1);

    ASSERT_FALSE(expression.subexpression(0).is_drained());
    ASSERT_FALSE(expression.subexpression(1).is_drained());
    ASSERT_FALSE(expression.subexpression(2).is_drained());

    ba::ExpressionHandler expression1{std::move(expression_ref)};

    ASSERT_FALSE(expression.subexpression(0).is_drained());
    ASSERT_TRUE(expression.subexpression(1).is_drained());
    ASSERT_FALSE(expression.subexpression(2).is_drained());

    expression1 = std::move(expression.subexpression(0));

    ASSERT_TRUE(expression.subexpression(0).is_drained());
    ASSERT_TRUE(expression.subexpression(1).is_drained());
    ASSERT_FALSE(expression.subexpression(2).is_drained());

    swap(expression.subexpression(1), expression.subexpression(2));

    ASSERT_TRUE(expression.subexpression(0).is_drained());
    ASSERT_FALSE(expression.subexpression(1).is_drained());
    ASSERT_TRUE(expression.subexpression(2).is_drained());
}

TEST(Draining, Test1) {
    auto expression = ba::SumExpression::make(cr_b(), cr_a(), an_d());
    ASSERT_EQ(expression.str(), "❪♯b+♯a+♭d❫");

    ASSERT_FALSE(expression.subexpression(0).is_drained());
    ASSERT_FALSE(expression.subexpression(1).is_drained());
    ASSERT_FALSE(expression.subexpression(2).is_drained());

    bool blinking_flag = true;
    for (auto& _ : expression.range()) {
        if (blinking_flag) {
            ba::ExpressionHandler new_expr{std::move(_)};
        }
    blinking_flag = !blinking_flag;
    }

    ASSERT_TRUE(expression.subexpression(0).is_drained());
    ASSERT_FALSE(expression.subexpression(1).is_drained());
    ASSERT_TRUE(expression.subexpression(2).is_drained());
}
