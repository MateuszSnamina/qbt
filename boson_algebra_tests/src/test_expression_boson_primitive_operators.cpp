// SELF:
#include <boson_algebra_tests/abcd.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
// GTEST:
#include <gtest/gtest.h>
// BOOST:
#include <boost/range/algorithm/count.hpp>

namespace ba = boson_algebra;

TEST(ExpressionBosonPrimitiveOperator, BosonCreationOperator) {
    const auto expression = cr_d();
    ASSERT_EQ(expression.str(), "♯d");
    ASSERT_EQ(expression.is_of_type<ba::BosonCreationOperator>(), true);
    ASSERT_EQ(expression.is_of_type<ba::BosonAnnihilationOperator>(), false);
    ASSERT_EQ(expression.is_of_type<ba::BosonNumberOperator>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    const auto boson = expression.casted_target<ba::BosonPrimitiveOperators>().unwrap().get().boson();
    ASSERT_TRUE(boson);
    ASSERT_EQ(boson->str(), "d");
    ASSERT_EQ(std::addressof(*boson), std::addressof(*d));
    {
        const auto expression1 = cr_d();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = cr_a();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = an_a();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "♯d");
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(ExpressionBosonPrimitiveOperator, BosonAnnihilationOperator) {
    const auto expression = an_d();
    ASSERT_EQ(expression.str(), "♭d");
    ASSERT_EQ(expression.is_of_type<ba::BosonCreationOperator>(), false);
    ASSERT_EQ(expression.is_of_type<ba::BosonAnnihilationOperator>(), true);
    ASSERT_EQ(expression.is_of_type<ba::BosonNumberOperator>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    const auto boson = expression.casted_target<ba::BosonPrimitiveOperators>().unwrap().get().boson();
    ASSERT_TRUE(boson);
    ASSERT_EQ(boson->str(), "d");
    ASSERT_EQ(std::addressof(*boson), std::addressof(*d));
    {
        const auto expression1 = an_d();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = an_a();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = cr_a();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "♭d");
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}

TEST(ExpressionBosonPrimitiveOperator, BosonNumberOperator) {
    const auto expression = n_d();
    ASSERT_EQ(expression.str(), "ℕd");
    ASSERT_EQ(expression.is_of_type<ba::BosonCreationOperator>(), false);
    ASSERT_EQ(expression.is_of_type<ba::BosonAnnihilationOperator>(), false);
    ASSERT_EQ(expression.is_of_type<ba::BosonNumberOperator>(), true);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);
    const auto boson = expression.casted_target<ba::BosonPrimitiveOperators>().unwrap().get().boson();
    ASSERT_TRUE(boson);
    ASSERT_EQ(boson->str(), "d");
    ASSERT_EQ(std::addressof(*boson), std::addressof(*d));
    {
        const auto expression1 = n_d();
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = n_a();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = cr_a();
        ASSERT_FALSE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
    {
        const auto expression1 = expression.clone();
        ASSERT_EQ(expression1.str(), "ℕd");
        ASSERT_TRUE(expression.equals(expression1));
        ASSERT_FALSE(std::addressof(expression.target()) == std::addressof(expression1.target()));
    }
}