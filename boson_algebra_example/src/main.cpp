#include <boost/range/adaptor/indexed.hpp>
//#include <boost/range/adaptor/transformed.hpp>
#include <boost/iterator/distance.hpp>  //TODO remove
#include <boost/range/algorithm.hpp>
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
        const ExpressionHandler product = ProductExpression::make(std::move(v));
        std::cout << "Structured Expressions str:  " << product.str() << std::endl;
        std::cout << "Structured Expressions repr: " << product.repr() << std::endl;
    }
    {
        // Product may be traversed using range (not const variant)
        ExpressionHandler cr_a = BosonCreationOperator::make(a);
        ExpressionHandler cr_b = BosonCreationOperator::make(b);
        ExpressionHandler cr_c = BosonCreationOperator::make(c);
        ExpressionHandler mut_product = ProductExpression::make(std::move(cr_a), std::move(cr_b), std::move(cr_c));
        for (const auto& xxx : mut_product.target().range()) {
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
        for (const auto& xxx : const_product.target().range()) {
            std::cout << "===>: " << xxx.repr() << std::endl;
        }
        for (auto&& xxx : const_product.target().range()) {
            (void)xxx;
            // ExpressionHandler stealed{std::move(xxx)}; // compile error.
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
        const auto fun = [](const ExpressionHandler& expr_hdl) -> ExpressionHandlerOptional {
            std::cout << "Dfs: " << expr_hdl.str() << std::endl;
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
        const auto fun = [](const ExpressionHandler& expr_hdl) -> ExpressionHandlerOptional {
            if (!expr_hdl.is_of_type<BosonNumberOperator>()) {
                return std::nullopt;
            }
            const auto& casted_other = expr_hdl.casted_target<BosonNumberOperator>();
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
        const auto fun = [](const ExpressionHandler& expression_hdl) -> ExpressionHandlerOptional {
            if (!expression_hdl.is_of_type<ProductExpression>()) {
                return std::nullopt;
            }
            const auto& range = expression_hdl.target().crange();
            const auto& range_begin = boost::begin(range);
            const auto& range_end = boost::end(range);
            const auto subproduct_hdl_iter = boost::find_if(range, [](const ExpressionHandler& expression_hdl) {
                return expression_hdl.is_of_type<ProductExpression>();
            });
            if (subproduct_hdl_iter == range_end) {
                return std::nullopt;
            }
            const auto& subproduct_expr_hdl = *subproduct_hdl_iter;
            ConstExpressionHandlerRandomAccessRange range1{range_begin, subproduct_hdl_iter};
            ConstExpressionHandlerRandomAccessRange range2 = subproduct_expr_hdl.target().crange();
            ConstExpressionHandlerRandomAccessRange range3{subproduct_hdl_iter + 1, range_end};
            ExpressionHandlerVector v;
            for (const auto& subexpression_hdl : range1) {
                v.emplace_back(std::move(subexpression_hdl.clone()));
            }
            for (const auto& subexpression_hdl : range2) {
                v.emplace_back(std::move(subexpression_hdl.clone()));
            }
            for (const auto& subexpression_hdl : range3) {
                v.emplace_back(std::move(subexpression_hdl.clone()));
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

void range_over_vector_of_nocopyable() {
    class Mov {
       public:
        Mov(int i)
            : p(std::make_unique<int>(i)),
              invalid(false) {
            std::cout << "NormalCtr" << std::endl;
        }
        Mov(const Mov&) = delete;
        Mov& operator=(const Mov&) = delete;

        Mov(Mov&& x)
            : p(std::move(x.p)),
              invalid(false) {
            std::cout << "MovCtr" << *p << std::endl;
            x.invalid = true;
        }

        Mov& operator=(Mov&& x) {
            std::cout << "MovAss" << *x.p << std::endl;
            p = std::move(x.p);
            x.invalid = true;
            return *this;
        }

        std::string str() const {
            if (invalid) {
                return "invalid";
            }
            return std::to_string(*p);
        }
        std::unique_ptr<int> p;
        bool invalid;
    };

    using MovRandomAccessRange = boost::any_range<Mov, boost::random_access_traversal_tag>;
    using ConstMovRandomAccessRange = boost::any_range<const Mov, boost::random_access_traversal_tag>;

    class WithV {
       public:
        std::vector<Mov> v;
        MovRandomAccessRange range() {
            return v;
        }
        ConstMovRandomAccessRange crange() {
            return v;
        }
    };

    std::cout << "----" << std::endl;

    WithV with_v;
    with_v.v.push_back(Mov(0));
    with_v.v.push_back(Mov(1));
    with_v.v.push_back(Mov(2));
    with_v.v.push_back(Mov(3));
    with_v.v.push_back(Mov(4));
    with_v.v.push_back(Mov(5));
    with_v.v.push_back(Mov(6));
    with_v.v.push_back(Mov(7));

    std::cout << "----" << std::endl;

    for (const auto& x : with_v.crange() | boost::adaptors::indexed()) {
        std::cout << "with_v.crange[" << x.index() << "]: " << x.value().str() << std::endl;
    }

    std::cout << "contentv[2]:" << with_v.v[2].str() << std::endl;
    Mov{std::move(with_v.v[2])};
    std::cout << "contentv[2]:" << with_v.v[2].str() << std::endl;

    for (const auto& x : with_v.crange() | boost::adaptors::indexed()) {
        std::cout << "with_v.crange[" << x.index() << "]: " << x.value().str() << std::endl;
    }

    for (const auto& x : with_v.range() | boost::adaptors::indexed()) {
        std::cout << "with_v.range[" << x.index() << "]: " << x.value().str() << std::endl;
    }
    std::cout << "Drain the vector!" << std::endl;
    for (auto&& x : with_v.range()) {
        if (!x.invalid) {
            Mov{std::move(x)};
        }
    }

    for (const auto& x : with_v.crange() | boost::adaptors::indexed()) {
        std::cout << "with_v.crange[" << x.index() << "]: " << x.value().str() << std::endl;
    }

    for (const auto& x : with_v.range() | boost::adaptors::indexed()) {
        std::cout << "with_v.range[" << x.index() << "]: " << x.value().str() << std::endl;
    }
}