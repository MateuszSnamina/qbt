// TESTED LIBRARY:
#include <boson_algebra/expression_pragma.hpp>
// GTEST:
#include <gtest/gtest.h>

namespace ba = boson_algebra;
using namespace ba::literals;

TEST(Draining, Test0) {
    auto expression = ba::ProductExpression::make('b'_cr, 'a'_cr, 'd'_an);
    ASSERT_EQ(expression.str(), "❪♯b◦♯a◦♭d❫");

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    auto& expression_ref = expression.subexpression(1);

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    ba::ExpressionHandler expression1{std::move(expression_ref)};

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    expression1 = std::move(expression.subexpression(0));

    ASSERT_TRUE(expression.subexpression(0).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    swap(expression.subexpression(1), expression.subexpression(2));

    ASSERT_TRUE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(2).is_shallow_drained());
}

TEST(Draining, Test1) {
    auto expression = ba::SumExpression::make('b'_cr, 'a'_cr, 'd'_an);
    ASSERT_EQ(expression.str(), "❪♯b+♯a+♭d❫");

    ASSERT_FALSE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(2).is_shallow_drained());

    bool blinking_flag = true;
    for (auto& _ : expression.range()) {
        if (blinking_flag) {
            ba::ExpressionHandler new_expr{std::move(_)};
        }
    blinking_flag = !blinking_flag;
    }

    ASSERT_TRUE(expression.subexpression(0).is_shallow_drained());
    ASSERT_FALSE(expression.subexpression(1).is_shallow_drained());
    ASSERT_TRUE(expression.subexpression(2).is_shallow_drained());
}