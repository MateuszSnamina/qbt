#include <boost/range/adaptor/transformed.hpp>
#include <boson_algebra/boson_algebra.hpp>
#include <boson_algebra/util_make.hpp>
#include <iostream>

using namespace boson_algebra;

ExpressionHandler expression_1(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a = BosonCreationOperator::make(a);
    ExpressionHandler an_b = BosonAnihilationOperator::make(b);
    ExpressionHandler cr_c = BosonCreationOperator::make(c);
    ExpressionHandler n_d = BosonNumberOperator::make(d);
    ExpressionHandler double_cr_c = IntegerFactoredExpression::make(2, std::move(cr_c));
    ExpressionHandler product1 = ProductExpression::make(std::move(cr_a), std::move(an_b));
    ExpressionHandler product2 = ProductExpression::make(std::move(double_cr_c), std::move(n_d));
    ExpressionHandler product3 = ProductExpression::make(std::move(product1), std::move(product2));
    return product3;
}

ExpressionHandler expression_2(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a = BosonCreationOperator::make(a);
    ExpressionHandler an_b = BosonAnihilationOperator::make(b);
    ExpressionHandler cr_c = BosonCreationOperator::make(c);
    ExpressionHandler n_d = BosonNumberOperator::make(d);
    ExpressionHandler double_cr_c = IntegerFactoredExpression::make(3, std::move(cr_c));
    ExpressionHandler product1 = ProductExpression::make(std::move(cr_a), std::move(an_b));
    ExpressionHandler product2 = ProductExpression::make(std::move(double_cr_c), std::move(n_d));
    ExpressionHandler product3 = ProductExpression::make(std::move(product1), std::move(product2));
    return product3;
}

ExpressionHandler expression_3(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler an_a = BosonAnihilationOperator::make(a);
    ExpressionHandler an_b = BosonAnihilationOperator::make(b);
    ExpressionHandler cr_c = BosonCreationOperator::make(c);
    ExpressionHandler n_d = BosonNumberOperator::make(d);
    ExpressionHandler double_cr_c = IntegerFactoredExpression::make(3, std::move(cr_c));
    ExpressionHandler product1 = ProductExpression::make(std::move(an_a), std::move(an_b));
    ExpressionHandler product2 = ProductExpression::make(std::move(double_cr_c), std::move(n_d));
    ExpressionHandler product3 = ProductExpression::make(std::move(product1), std::move(product2));
    return product3;
}

ExpressionHandler expression_4(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler an_b = BosonAnihilationOperator::make(b);
    ExpressionHandler an_b_re = BosonAnihilationOperator::make(b);
    ExpressionHandler cr_c = BosonCreationOperator::make(c);
    ExpressionHandler n_d = BosonNumberOperator::make(d);
    ExpressionHandler double_cr_c = IntegerFactoredExpression::make(2, std::move(cr_c));
    ExpressionHandler product1 = ProductExpression::make(std::move(an_b), std::move(an_b_re));
    ExpressionHandler product2 = ProductExpression::make(std::move(double_cr_c), std::move(n_d));
    ExpressionHandler product3 = ProductExpression::make(std::move(product1), std::move(product2));
    return product3;
}

ExpressionHandler expression_5(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a = BosonCreationOperator::make(a);
    ExpressionHandler an_b = BosonAnihilationOperator::make(b);
    ExpressionHandler cr_c = BosonCreationOperator::make(c);
    ExpressionHandler n_d = BosonNumberOperator::make(d);
    ExpressionHandler product1 = ProductExpression::make(std::move(cr_a), std::move(an_b));
    ExpressionHandler product2 = ProductExpression::make(std::move(cr_c), std::move(n_d));
    ExpressionHandler product3 = ProductExpression::make(std::move(product1), std::move(product2));
    return product3;
}

int main() {
    // **********************************************************
    // ***  Declare some underlying bosons                    ***
    // **********************************************************

    // The instances below will be shared among all the basic
    // Boson Primitive Operators.

    const std::shared_ptr<Boson> a = std::make_shared<CharBoson>('a');
    const std::shared_ptr<Boson> b = std::make_shared<CharBoson>('b');
    const std::shared_ptr<Boson> c = std::make_shared<CharBoson>('c');
    const std::shared_ptr<Boson> d = std::make_shared<CharBoson>('d');
    std::cout << "boson str:  " << c->str() << std::endl;
    std::cout << "boson repr: " << c->repr() << std::endl;
    std::cout << "boson id:   " << c->get_id() << std::endl;

    // **********************************************************
    // ***  Declare some Boson Primitive Operators            ***
    // **********************************************************
    {
        // Expressions should be refferenced by ExpressionHandlers:
        const ExpressionHandler cr_a = BosonCreationOperator::make(a);
        const ExpressionHandler cr_b = BosonCreationOperator::make(b);
        const ExpressionHandler cr_c = BosonCreationOperator::make(c);
        std::cout << "Boson Primitive Operator str:  " << cr_c.str() << std::endl;
        std::cout << "Boson Primitive Operator repr: " << cr_c.repr() << std::endl;
    }

    // **********************************************************
    // ***  Declare some Structured Expressions               ***
    // **********************************************************
    {
        // Product expression may be defined using a veriadic constructor:
        ExpressionHandler cr_a = BosonCreationOperator::make(a);
        ExpressionHandler cr_b = BosonCreationOperator::make(b);
        ExpressionHandler cr_c = BosonCreationOperator::make(c);
        const ExpressionHandler product = ProductExpression::make(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        std::cout << "Structured Expressions str:  " << product.str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.repr() << std::endl;

        // Experimental:
        for (const auto& xxx : dynamic_cast<const ProductExpression&>(product.target()).range()) {
            std::cout << "===>: " << xxx.repr() << std::endl;
        }
    }
    {
        //  Product expression may be defined using a constructor with ExpressionHandlerVector:
        ExpressionHandler cr_a = BosonCreationOperator::make(a);
        ExpressionHandler cr_b = BosonCreationOperator::make(b);
        ExpressionHandler cr_c = BosonCreationOperator::make(c);
        ExpressionHandlerVector v = util::make<ExpressionHandlerVector>(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        const ExpressionHandler product = ProductExpression::make(std::move(v));
        std::cout << "Structured Expressions str:  " << product.str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.repr() << std::endl;
    }

    // **********************************************************
    // ***  Clone                                             ***
    // **********************************************************
    {
        // Expressions may be cloned (deep copy):
        const ExpressionHandler expr = expression_1(a, b, c, d);
        const ExpressionHandler cloned = expr.clone();
        std::cout << "Clone:    " << cloned.str() << std::endl;
        std::cout << "Original: " << expr.str() << std::endl;
    }

    // **********************************************************
    // ***  Equals                                            ***
    // **********************************************************
    {
        const ExpressionHandler expr1 = expression_1(a, b, c, d);
        const ExpressionHandler expr1_re = expression_1(a, b, c, d);
        const ExpressionHandler expr2 = expression_2(a, b, c, d);
        const ExpressionHandler expr3 = expression_3(a, b, c, d);
        const ExpressionHandler expr4 = expression_4(a, b, c, d);
        const ExpressionHandler expr5 = expression_5(a, b, c, d);
        std::cout << expr1.str() << " equals " << expr1_re.str() << " ? " << expr1.equals(expr1_re) << std::endl;
        std::cout << expr1.str() << " equals " << expr2.str() << " ? " << expr1.equals(expr2) << std::endl;
        std::cout << expr1.str() << " equals " << expr3.str() << " ? " << expr1.equals(expr3) << std::endl;
        std::cout << expr1.str() << " equals " << expr4.str() << " ? " << expr1.equals(expr4) << std::endl;
        std::cout << expr1.str() << " equals " << expr5.str() << " ? " << expr1.equals(expr5) << std::endl;
    }

    // **********************************************************
    // ***  Dfs transform                                     ***
    // **********************************************************
    {
        const auto fun = [](const Expression& expr) -> ExpressionHandlerOptional {
            std::cout << "Dfs: " << expr.str() << std::endl;
            return std::nullopt;
        };
        ExpressionHandler expr1 = expression_1(a, b, c, d);
        ExpressionHandler expr1_clone = expr1.clone();
        std::cout << "Start Dfs." << std::endl;
        expr1.safe_dfs_transform(fun);
        std::cout << "End Dfs." << std::endl;
        std::cout << "Before transforming DFS: " << expr1_clone.str() << std::endl;
        std::cout << "After transforming DFS:  " << expr1.str() << std::endl;
    }
    {
        // Transfomration goal: Expand boson number operator when possible.
        // Transfomration example: 2*n(boson)=>2*(cr(boson)*an(boson))
        const auto fun = [](const Expression& expr) -> ExpressionHandlerOptional {
            const auto casted_other_ptr = dynamic_cast<const BosonNumberOperator*>(&expr);
            if (!casted_other_ptr) {
                return std::nullopt;
            }
            const auto& casted_other = *casted_other_ptr;
            const auto boson = casted_other.boson();
            ExpressionHandler cr = BosonCreationOperator::make(boson);
            ExpressionHandler an = BosonAnihilationOperator::make(boson);
            ExpressionHandler product = ProductExpression::make(std::move(cr), std::move(an));
            return std::move(product);
        };
        ExpressionHandler expr1 = expression_1(a, b, c, d);
        ExpressionHandler expr1_clone = expr1.clone();
        std::cout << "Start Dfs." << std::endl;
        expr1.safe_dfs_transform(fun);
        std::cout << "End Dfs." << std::endl;
        std::cout << "Before transforming DFS: " << expr1_clone.str() << std::endl;
        std::cout << "After transforming DFS:  " << expr1.str() << std::endl;
    }
    {
        // Transfomration goal: Perform simplification due to product associativity.
        // Transfomration example: a*b*(c*d)*e => a*b*c*d*e
        const auto fun = [](const Expression& expression) -> ExpressionHandlerOptional {
            const auto casted_expression_ptr = dynamic_cast<const ProductExpression*>(&expression);
            if (!casted_expression_ptr) {
                return std::nullopt;
            }
            const ProductExpression& casted_expression = *casted_expression_ptr;
            std::optional<unsigned> n_subexpression_being_product_optional;
            for (unsigned n_subexpression = 0; n_subexpression < casted_expression.n_subexpressions(); n_subexpression++) {
                const Expression& subexpression = casted_expression.subexpression(n_subexpression).target();
                const auto casted_subexpression_ptr = dynamic_cast<const ProductExpression*>(&subexpression);
                if (casted_subexpression_ptr) {
                    n_subexpression_being_product_optional = n_subexpression;
                    break;
                }
            }
            if (!n_subexpression_being_product_optional) {
                return std::nullopt;
            }
            unsigned n_subexpression_being_product = *n_subexpression_being_product_optional;
            const Expression& subexpression = casted_expression.subexpression(n_subexpression_being_product).target();
            const auto casted_subexpression_ptr = dynamic_cast<const ProductExpression*>(&subexpression);
            const ProductExpression& casted_subexpression = *casted_subexpression_ptr;
            ExpressionHandlerVector v;
            for (unsigned n_subexpression = 0; n_subexpression < n_subexpression_being_product; n_subexpression++) {
                v.emplace_back(std::move(casted_expression.subexpression(n_subexpression).clone()));
            }

            for (unsigned n_subexpression = 0; n_subexpression < casted_subexpression.n_subexpressions(); n_subexpression++) {
                v.emplace_back(std::move(casted_subexpression.subexpression(n_subexpression).clone()));
            }

            for (unsigned n_subexpression = n_subexpression_being_product + 1; n_subexpression < casted_expression.n_subexpressions(); n_subexpression++) {
                v.emplace_back(std::move(casted_expression.subexpression(n_subexpression).clone()));
            }
            ExpressionHandler product = ProductExpression::make(std::move(v));
            return std::move(product);
        };
        ExpressionHandler expr1 = expression_1(a, b, c, d);
        ExpressionHandler expr1_clone = expr1.clone();
        std::cout << "Start Dfs." << std::endl;
        expr1.safe_dfs_transform(fun);
        std::cout << "End Dfs." << std::endl;
        std::cout << "Before transforming DFS: " << expr1_clone.str() << std::endl;
        std::cout << "After transforming DFS:  " << expr1.str() << std::endl;
    }
}