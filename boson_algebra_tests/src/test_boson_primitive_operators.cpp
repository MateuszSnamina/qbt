// SELF:
#include <boson_algebra_tests/abcd.hpp>
// TESTED LIBRARY:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/transform_simplify_product.hpp>
// GTEST:
#include <gtest/gtest.h>
// BOOST
#include <boost/range/algorithm/count.hpp>

namespace ba = boson_algebra;

TEST(BosonPrimitiveOperator, BosonCreationOperator) {
    const auto expression = cr_d();
    ASSERT_EQ(expression.str(), "♯d");
    ASSERT_EQ(expression.is_of_type<ba::BosonCreationOperator>(), true);
    ASSERT_EQ(expression.is_of_type<ba::BosonAnnihilationOperator>(), false);
    ASSERT_EQ(expression.is_of_type<ba::BosonNumberOperator>(), false);
    ASSERT_EQ(expression.n_subexpressions(), 0);
    ASSERT_EQ(boost::size(expression.range()), 0);
    ASSERT_EQ(boost::size(expression.crange()), 0);

    const auto expression1 = cr_d();
    ASSERT_TRUE(expression.equals(expression1));
    ASSERT_FALSE(std::addressof(cr_d().target()) == std::addressof(expression1.target()));

    const auto expression2 = cr_a();
    ASSERT_FALSE(expression.equals(expression2));
    ASSERT_FALSE(std::addressof(cr_d().target()) == std::addressof(expression2.target()));

    const auto expression3 = an_a();
    ASSERT_FALSE(expression.equals(expression3));
    ASSERT_FALSE(std::addressof(cr_d().target()) == std::addressof(expression3.target()));
}

//BosonAnnihilationOperator
