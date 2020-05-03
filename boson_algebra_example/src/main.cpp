//SELF:
#include <boson_algebra/expression_all.hpp>
#include <boson_algebra/expression_pragma.hpp>
#include <boson_algebra/modify_flatten_product.hpp>
#include <boson_algebra/util_make.hpp>
#include <boson_algebra/algorithm_dfs.hpp>
// STD:
#include <iostream>

using namespace boson_algebra;
using namespace boson_algebra::literals;
using namespace boson_algebra::operators;

ExpressionHandler expression_1(const std::shared_ptr<Boson>& a,
                               const std::shared_ptr<Boson>& b,
                               const std::shared_ptr<Boson>& c,
                               const std::shared_ptr<Boson>& d) {
    ExpressionHandler cr_a = BosonCreationOperator::make(a);
    ExpressionHandler an_b = BosonAnnihilationOperator::make(b);
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
    ExpressionHandler an_b = BosonAnnihilationOperator::make(b);
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
    ExpressionHandler an_a = BosonAnnihilationOperator::make(a);
    ExpressionHandler an_b = BosonAnnihilationOperator::make(b);
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
    ExpressionHandler an_b = BosonAnnihilationOperator::make(b);
    ExpressionHandler an_b_re = BosonAnnihilationOperator::make(b);
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
    ExpressionHandler an_b = BosonAnnihilationOperator::make(b);
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

    const std::shared_ptr<Boson> a = CharBoson::make('a');
    const std::shared_ptr<Boson> b = CharBoson::make('b');
    const std::shared_ptr<Boson> c = CharBoson::make('c');
    const std::shared_ptr<Boson> d = CharBoson::make('d');
    std::cout << "boson str:  " << c->str() << std::endl;
    std::cout << "boson repr: " << c->repr() << std::endl;
    std::cout << "boson id:   " << c->id() << std::endl;

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
        ExpressionHandler product = ProductExpression::make(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        std::cout << "Structured Expressions str:  " << product.str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.repr() << std::endl;
    }
    {
        //  Product expression may be defined using a constructor with ExpressionHandlerVector:
        ExpressionHandler cr_a = BosonCreationOperator::make(a);
        ExpressionHandler cr_b = BosonCreationOperator::make(b);
        ExpressionHandler cr_c = BosonCreationOperator::make(c);
        ExpressionHandlerVector v = util::make<ExpressionHandlerVector>(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        const ExpressionHandler product = ProductExpression::make_from_buffer(std::move(v));
        std::cout << "Structured Expressions str:  " << product.str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.repr() << std::endl;
    }
    {
        // Product may be traversed using range (not const variant)
        ExpressionHandler cr_a = BosonCreationOperator::make(a);
        ExpressionHandler cr_b = BosonCreationOperator::make(b);
        ExpressionHandler cr_c = BosonCreationOperator::make(c);
        ExpressionHandler mut_product = ProductExpression::make(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        for (const auto& xxx : mut_product.range()) {
            std::cout << "===>: " << xxx.repr() << std::endl;
        }
        for (auto&& xxx : mut_product.target().range()) {
            ExpressionHandler stealed{std::move(xxx)};
        }
    }
    {
        // Product may be traversed using range (const variant):
        ExpressionHandler cr_a = BosonCreationOperator::make(a);
        ExpressionHandler cr_b = BosonCreationOperator::make(b);
        ExpressionHandler cr_c = BosonCreationOperator::make(c);
        const ExpressionHandler const_product = ProductExpression::make(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        for (const auto& xxx : const_product.range()) {
            std::cout << "===>: " << xxx.repr() << std::endl;
        }
        for (auto&& xxx : const_product.range()) {
            (void)xxx;
            // ExpressionHandler stealed{std::move(xxx)}; // compile error.
        }
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
    // {
    //     const auto fun = [](const ExpressionHandler& expression) -> ExpressionHandlerOptional {
    //         std::cout << "Dfs: " << expression.str() << std::endl;
    //         return std::nullopt;
    //     };
    //     ExpressionHandler expr1 = expression_1(a, b, c, d);
    //     ExpressionHandler expr1_clone = expr1.clone();
    //     std::cout << "Start Dfs." << std::endl;
    //     safe_dfs_transform(expr1, fun);
    //     std::cout << "End Dfs." << std::endl;
    //     std::cout << "Before transforming DFS: " << expr1_clone.str() << std::endl;
    //     std::cout << "After transforming DFS:  " << expr1.str() << std::endl;
    // }
    // {
    //     Transfomration goal: Rebuild_prod_sum_into_sum_prod boson number operator when possible.
    //     Transfomration example: 2*n(boson)=>2*(cr(boson)*an(boson))
    //     const auto fun = [](const ExpressionHandler& expression) -> ExpressionHandlerOptional {
    //         if (!expression.is_of_type<BosonNumberOperator>()) {
    //             return std::nullopt;
    //         }
    //         const auto& casted_other = expression.casted_target<BosonNumberOperator>().unwrap().get();
    //         const auto boson = casted_other.boson();
    //         ExpressionHandler cr = BosonCreationOperator::make(boson);
    //         ExpressionHandler an = BosonAnnihilationOperator::make(boson);
    //         return ProductExpression::make(std::move(cr), std::move(an));
    //     };
    //     ExpressionHandler expr1 = expression_1(a, b, c, d);
    //     ExpressionHandler expr1_clone = expr1.clone();
    //     std::cout << "Start Dfs." << std::endl;
    //     safe_dfs_transform(expr1, fun);
    //     std::cout << "End Dfs." << std::endl;
    //     std::cout << "Before transforming DFS: " << expr1_clone.str() << std::endl;
    //     std::cout << "After transforming DFS:  " << expr1.str() << std::endl;
    // }
    // {
    //     Transfomration goal: Perform simplification due to product associativity.
    //     Transfomration example: a*b*(c*d)*e => a*b*c*d*e
    //     ExpressionHandler expr1 = expression_1(a, b, c, d);
    //     ExpressionHandler expr1_clone = expr1.clone();
    //     std::cout << "Start Dfs." << std::endl;
    //     safe_dfs_transform(expr1, modify_flatten_product);
    //     std::cout << "End Dfs." << std::endl;
    //     std::cout << "Before transforming DFS: " << expr1_clone.str() << std::endl;
    //     std::cout << "After transforming DFS:  " << expr1.str() << std::endl;
    // }
    // {
    //     When writing code you may utilize expression pragma.
    //     Expression pragma literals:
    //     std::cout << ('u'_b)->repr() << std::endl;
    //     std::cout << ('u'_cr).str() << std::endl;
    //     std::cout << ('u'_an).str() << std::endl;
    //     std::cout << ('u'_no).str() << std::endl;
    //     Expression pragma operators:
    //     std::cout << ((3 * 'a'_cr) + 'u'_no).str() << std::endl;
    //     std::cout << ('a'_cr * 'b'_cr * 'c'_cr).str() << std::endl;
    // }
}