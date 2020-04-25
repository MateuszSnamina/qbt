#include <boson_algebra/boson_algebra.hpp>
#include <boson_algebra/util_make.hpp>
#include <iostream>

using namespace boson_algebra;

ExpressionHandler expression_1(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
    ExpressionHandler an_b{std::make_unique<BosonAnihilationOperator>(b)};
    ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
    ExpressionHandler n_d{std::make_unique<BosonNumberOperator>(d)};
    ExpressionHandler double_cr_c{std::make_unique<IntegerFactoredExpression>(2, std::move(cr_c))};
    ExpressionHandler product1{std::make_unique<ProductExpression>(std::move(cr_a), std::move(an_b))};
    ExpressionHandler product2{std::make_unique<ProductExpression>(std::move(double_cr_c), std::move(n_d))};
    ExpressionHandler product3{std::make_unique<ProductExpression>(std::move(product1), std::move(product2))};
    return product3;
}

ExpressionHandler expression_2(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
    ExpressionHandler an_b{std::make_unique<BosonAnihilationOperator>(b)};
    ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
    ExpressionHandler n_d{std::make_unique<BosonNumberOperator>(d)};
    ExpressionHandler double_cr_c{std::make_unique<IntegerFactoredExpression>(3, std::move(cr_c))};
    ExpressionHandler product1{std::make_unique<ProductExpression>(std::move(cr_a), std::move(an_b))};
    ExpressionHandler product2{std::make_unique<ProductExpression>(std::move(double_cr_c), std::move(n_d))};
    ExpressionHandler product3{std::make_unique<ProductExpression>(std::move(product1), std::move(product2))};
    return product3;
}

ExpressionHandler expression_3(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler an_a{std::make_unique<BosonAnihilationOperator>(a)};
    ExpressionHandler an_b{std::make_unique<BosonAnihilationOperator>(b)};
    ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
    ExpressionHandler n_d{std::make_unique<BosonNumberOperator>(d)};
    ExpressionHandler double_cr_c{std::make_unique<IntegerFactoredExpression>(3, std::move(cr_c))};
    ExpressionHandler product1{std::make_unique<ProductExpression>(std::move(an_a), std::move(an_b))};
    ExpressionHandler product2{std::make_unique<ProductExpression>(std::move(double_cr_c), std::move(n_d))};
    ExpressionHandler product3{std::make_unique<ProductExpression>(std::move(product1), std::move(product2))};
    return product3;
}

ExpressionHandler expression_4(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler an_b{std::make_unique<BosonAnihilationOperator>(b)};
    ExpressionHandler an_b_re{std::make_unique<BosonAnihilationOperator>(b)};
    ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
    ExpressionHandler n_d{std::make_unique<BosonNumberOperator>(d)};
    ExpressionHandler double_cr_c{std::make_unique<IntegerFactoredExpression>(2, std::move(cr_c))};
    ExpressionHandler product1{std::make_unique<ProductExpression>(std::move(an_b), std::move(an_b_re))};
    ExpressionHandler product2{std::make_unique<ProductExpression>(std::move(double_cr_c), std::move(n_d))};
    ExpressionHandler product3{std::make_unique<ProductExpression>(std::move(product1), std::move(product2))};
    return product3;
}

ExpressionHandler expression_5(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
    ExpressionHandler an_b{std::make_unique<BosonAnihilationOperator>(b)};
    ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
    ExpressionHandler n_d{std::make_unique<BosonNumberOperator>(d)};
    ExpressionHandler product1{std::make_unique<ProductExpression>(std::move(cr_a), std::move(an_b))};
    ExpressionHandler product2{std::make_unique<ProductExpression>(std::move(cr_c), std::move(n_d))};
    ExpressionHandler product3{std::make_unique<ProductExpression>(std::move(product1), std::move(product2))};
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
        ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
        ExpressionHandler cr_b{std::make_unique<BosonCreationOperator>(b)};
        ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};

        std::cout << "Boson Primitive Operator str:  " << cr_c.target().str() << std::endl;
        std::cout << "Boson Primitive Operator repr: " << cr_c.target().repr() << std::endl;

        // Note: Expressions are not intended to be referenced by smart pointers.
        // The lines below works, but are not intended to be use in client code:
        //const std::unique_ptr<Expression> cr_a = std::make_unique<BosonCreationOperator>(a);
        //const std::unique_ptr<Expression> cr_b = std::make_unique<BosonCreationOperator>(b);
        //const std::unique_ptr<Expression> cr_c = std::make_unique<BosonCreationOperator>(c);
    }

    // **********************************************************
    // ***  Declare some Structured Expressions               ***
    // **********************************************************

    {
        // Product expression may be defined using a veriadic constructor:
        ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
        ExpressionHandler cr_b{std::make_unique<BosonCreationOperator>(b)};
        ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
        ExpressionHandler product{std::make_unique<ProductExpression>(std::move(cr_a), std::move(cr_b), std::move(cr_c))};
        std::cout << "Structured Expressions str:  " << product.target().str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.target().repr() << std::endl;
    }
    {
        //  Product expression may be defined using a constructor with ExpressionHandlerVector:
        ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
        ExpressionHandler cr_b{std::make_unique<BosonCreationOperator>(b)};
        ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
        ExpressionHandlerVector v = util::make<ExpressionHandlerVector>(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        ExpressionHandler product{std::make_unique<ProductExpression>(std::move(v))};
        std::cout << "Structured Expressions str:  " << product.target().str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.target().repr() << std::endl;
    }

    // **********************************************************
    // ***  Clone                                             ***
    // **********************************************************

    {
        // Expressions may be cloned (deep copy):
        ExpressionHandler expr = expression_1(a, b, c, d);
        auto cloned = expr.clone();
        std::cout << "Clone:    " << cloned.target().str() << std::endl;
        std::cout << "Original: " << expr.target().str() << std::endl;
    }

    // **********************************************************
    // ***  Equals                                            ***
    // **********************************************************

    {
        ExpressionHandler expr1 = expression_1(a, b, c, d);
        ExpressionHandler expr1_re = expression_1(a, b, c, d);
        ExpressionHandler expr2 = expression_2(a, b, c, d);
        ExpressionHandler expr3 = expression_3(a, b, c, d);
        ExpressionHandler expr4 = expression_4(a, b, c, d);
        ExpressionHandler expr5 = expression_5(a, b, c, d);
        std::cout << expr1.target().str() << " equals " << expr1_re.target().str() << " ? " << expr1.equals(expr1_re) << std::endl;
        std::cout << expr1.target().str() << " equals " << expr2.target().str() << " ? " << expr1.equals(expr2) << std::endl;
        std::cout << expr1.target().str() << " equals " << expr3.target().str() << " ? " << expr1.equals(expr3) << std::endl;
        std::cout << expr1.target().str() << " equals " << expr4.target().str() << " ? " << expr1.equals(expr4) << std::endl;
        std::cout << expr1.target().str() << " equals " << expr5.target().str() << " ? " << expr1.equals(expr5) << std::endl;
    }

    // **********************************************************
    // ***  Dfs transform                                     ***
    // **********************************************************

    {
        const auto fun = [](const Expression& expr) -> std::unique_ptr<Expression> {
            std::cout << "Dfs: " << expr.str() << std::endl;
            return nullptr;
        };
        ExpressionHandler expr1 = expression_1(a, b, c, d);
        ExpressionHandler expr1_clone = expr1.clone();
        std::cout << "Start Dfs." << std::endl;
        expr1.safe_dfs_transform(fun);
        std::cout << "End Dfs." << std::endl;
        std::cout << "Before transforming DFS: " << expr1_clone.target().str() << std::endl;
        std::cout << "After transforming DFS:  " << expr1.target().str() << std::endl;
    }

    {
        const auto fun = [](const Expression& expr) -> std::unique_ptr<Expression> {
            std::cout << "Dfs: " << expr.str() << std::endl;
            const auto casted_other_ptr = dynamic_cast<const BosonNumberOperator*>(&expr);
            if (!casted_other_ptr) {
                return nullptr;
            }
            const auto& casted_other = *casted_other_ptr;
            const auto boson = casted_other.boson();
            ExpressionHandler cr{std::make_unique<BosonCreationOperator>(boson)};
            ExpressionHandler an{std::make_unique<BosonAnihilationOperator>(boson)};
            std::unique_ptr<Expression> product{std::make_unique<ProductExpression>(std::move(cr), std::move(an))};
            return product;
        };
        ExpressionHandler expr1 = expression_1(a, b, c, d);
        ExpressionHandler expr1_clone = expr1.clone();
        std::cout << "Start Dfs." << std::endl;
        expr1.safe_dfs_transform(fun);
        std::cout << "End Dfs." << std::endl;
        std::cout << "Before transforming DFS: " << expr1_clone.target().str() << std::endl;
        std::cout << "After transforming DFS:  " << expr1.target().str() << std::endl;
    }
}