#include <boson_algebra/boson_algebra.hpp>
#include <boson_algebra/util_make.hpp>
#include <iostream>

using namespace boson_algebra;

int main() {
    // **********************************************************
    // ***  Declare some underlying bosons                    ***
    // **********************************************************
    //
    const std::shared_ptr<Boson> a = std::make_shared<CharBoson>('a');
    const std::shared_ptr<Boson> b = std::make_shared<CharBoson>('b');
    const std::shared_ptr<Boson> c = std::make_shared<CharBoson>('c');
    const std::shared_ptr<Boson> d = std::make_shared<CharBoson>('d');

    std::cout << c->str() << std::endl;
    std::cout << c->repr() << std::endl;
    std::cout << c->get_id() << std::endl;

    // **********************************************************
    // ***  Declare some basic expressions                    ***
    // **********************************************************

    // Expressions should be refferenced by ExpressionHandlers:
    ExpressionHandler cr_a{std::make_unique<BosonCreationOperator>(a)};
    ExpressionHandler cr_b{std::make_unique<BosonCreationOperator>(b)};
    ExpressionHandler cr_c{std::make_unique<BosonCreationOperator>(c)};
    ExpressionHandler cr_d{std::make_unique<BosonCreationOperator>(d)};

    std::cout << cr_c.target().str() << std::endl;
    std::cout << cr_c.target().repr() << std::endl;

    // Note: Expressions are not intended to be referenced by smart pointers.
    // The lines below works, but are not intended to be use in client code:
    //const std::unique_ptr<Expression> cr_a = std::make_unique<BosonCreationOperator>(a);
    //const std::unique_ptr<Expression> cr_b = std::make_unique<BosonCreationOperator>(b);
    //const std::unique_ptr<Expression> cr_c = std::make_unique<BosonCreationOperator>(c);
    //const std::unique_ptr<Expression> cr_d = std::make_unique<BosonCreationOperator>(d);

    // **********************************************************
    // ***  Declare some structured expressions               ***
    // **********************************************************

    using vt = std::vector<ExpressionHandler>;
    std::vector<ExpressionHandler> v = util::make<vt>(std::move(cr_a), std::move(cr_c), std::move(cr_d));
    ExpressionHandler product{std::make_unique<ProductExpression>(std::move(v))};

    std::cout << product.target().str() << std::endl;
    std::cout << product.target().repr() << std::endl;

}