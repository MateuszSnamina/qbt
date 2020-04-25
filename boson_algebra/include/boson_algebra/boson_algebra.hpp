#ifndef BOSON_ALGEBRA_BOSON_ALGEBRA_HPP
#define BOSON_ALGEBRA_BOSON_ALGEBRA_HPP

#include <boson_algebra/util_make.hpp>
#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace boson_algebra {

// **********************************************************
// ***  StrRepr                                           ***
// **********************************************************

class StrRepr {
   public:
    virtual std::string str() const = 0;
    virtual std::string repr() const = 0;
    virtual ~StrRepr() = default;
};

// **********************************************************
// ***  ExpressionHandler                                 ***
// **********************************************************

class Expression;

class ExpressionHandler {
   public:
    ExpressionHandler(std::unique_ptr<Expression>);
    ExpressionHandler(ExpressionHandler&& expr_hdl);
    Expression& target();
    const Expression& target() const;
    std::unique_ptr<Expression> substitute(std::unique_ptr<Expression>);
    friend void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2);
    friend class Expression;

   private:
    std::unique_ptr<Expression> _expr;
};

inline ExpressionHandler::ExpressionHandler(std::unique_ptr<Expression> expr) : _expr(std::move(expr)) {
    assert(_expr);
}

inline ExpressionHandler::ExpressionHandler(ExpressionHandler&& expr_hdl) : _expr(std::move(expr_hdl._expr)) {
}

inline Expression& ExpressionHandler::target() {
    return *_expr;
}

inline const Expression& ExpressionHandler::target() const {
    return *_expr;
}

inline std::unique_ptr<Expression>
ExpressionHandler::substitute(std::unique_ptr<Expression> expr) {
    assert(expr);
    std::swap(_expr, expr);
    return expr;
}

inline void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2) {
    std::swap(expr_1._expr, expr_2._expr);
}

// **********************************************************
// ***  ExpressionHandler typedefs                        ***
// **********************************************************

using ExpressionHandlerVector = std::vector<ExpressionHandler>;
template <class KeyT>
using ExpressionHandlerMap = std::map<KeyT, ExpressionHandler>;

// **********************************************************
// ***  Expression                                        ***
// **********************************************************

class Expression : public StrRepr {
   public:
    virtual unsigned n_subexpressions() const = 0;
    virtual ExpressionHandler& subexpression(unsigned n_subexpression) = 0;
    virtual const ExpressionHandler& subexpression(unsigned n_subexpression) const = 0;
    virtual ~Expression() = default;
};

// **********************************************************
// ***  LeafExpression                                    ***
// **********************************************************

class LeafExpression : public Expression {
   public:
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    ~LeafExpression() = 0;
};

inline unsigned LeafExpression::n_subexpressions() const {
    return 0u;
}

inline ExpressionHandler& LeafExpression::subexpression(unsigned n_subexpression) {
    assert(false);
}

inline const ExpressionHandler& LeafExpression::subexpression(unsigned n_subexpression) const {
    assert(false);
}

inline LeafExpression::~LeafExpression() {
}

// **********************************************************
// ***  BridgeExpression                                  ***
// **********************************************************

class BridgeExpression : public Expression {
   public:
    BridgeExpression(ExpressionHandler&&);
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    ~BridgeExpression() = 0;

   private:
    ExpressionHandler _expr_hdl;
};

inline BridgeExpression::BridgeExpression(ExpressionHandler&& expr_hdl) : _expr_hdl(std::move(expr_hdl)) {
}

inline unsigned BridgeExpression::n_subexpressions() const {
    return 1u;
}

inline ExpressionHandler& BridgeExpression::subexpression(unsigned n_subexpression) {
    assert(n_subexpression == 0);
    return _expr_hdl;
}

inline const ExpressionHandler& BridgeExpression::subexpression(unsigned n_subexpression) const {
    assert(n_subexpression == 0);
    return _expr_hdl;
}

inline BridgeExpression::~BridgeExpression() {
}

// **********************************************************
// ***  VectorNumerous                                    ***
// **********************************************************

class VectorNumerousExpression : public Expression {
   public:
    VectorNumerousExpression(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    VectorNumerousExpression(Args&&... expr_hdls);
    // VectorNumerousExpression(ExpressionHandler&& e1, ExpressionHandler&& e2);
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    ~VectorNumerousExpression();

   private:
    ExpressionHandlerVector _expr_hdls;
};

inline VectorNumerousExpression::VectorNumerousExpression(ExpressionHandlerVector&& expr_hdls)
    : _expr_hdls(std::move(expr_hdls)) {
}

template <class... Args>
VectorNumerousExpression::VectorNumerousExpression(Args&&... expr_hdls) : _expr_hdls(util::make<ExpressionHandlerVector>(std::move(expr_hdls)...)) {
}

// VectorNumerousExpression::VectorNumerousExpression(ExpressionHandler&& e1, ExpressionHandler&& e2)
//     : _expr_hdls(util::make<ExpressionHandlerVector>(std::move(e1), std::move(e2))) {
// }

inline unsigned VectorNumerousExpression::n_subexpressions() const {
    return _expr_hdls.size();
}

inline ExpressionHandler& VectorNumerousExpression::subexpression(unsigned n_subexpression) {
    assert(n_subexpression < _expr_hdls.size());
    return _expr_hdls[n_subexpression];
}

inline const ExpressionHandler& VectorNumerousExpression::subexpression(unsigned n_subexpression) const {
    assert(n_subexpression < _expr_hdls.size());
    return _expr_hdls[n_subexpression];
}

inline VectorNumerousExpression::~VectorNumerousExpression() {
}

// ****************************************************************************************************************

// ##########################################################
// ###########  Boson                   #####################
// ##########################################################

// **********************************************************
// ***  IdClass                                           ***
// **********************************************************

class IdClass {
   public:
    unsigned long get_id() const;
    virtual ~IdClass() = default;

   protected:
    IdClass();

   private:
    unsigned long _id;
    static unsigned long _pool_id;
};

inline IdClass::IdClass() : _id(_pool_id++) {
}

inline unsigned long IdClass::get_id() const {
    return _id;
}

// ****************************************************************************************************************

// ##########################################################
// ###########  Boson                   #####################
// ##########################################################

// **********************************************************
// ***  Boson                                             ***
// **********************************************************

class Boson : public IdClass, public StrRepr {
   public:
    virtual ~Boson() = 0;
};

inline Boson::~Boson() {
}

// **********************************************************
// ***  CharBoson                                         ***
// **********************************************************

class CharBoson final : public Boson {
   public:
    CharBoson(char);
    std::string str() const override;
    std::string repr() const override;

   private:
    char _c;
};

inline CharBoson::CharBoson(char c) : _c(c) {
}

inline std::string CharBoson::str() const {
    return std::string(1, _c);
}

inline std::string CharBoson::repr() const {
    return std::string("B[") + _c + std::string("]");
}

// ****************************************************************************************************************

// References:
// (1) list-of-all-unicodes-open-close-brackets:
// https://stackoverflow.com/questions/13535172/list-of-all-unicodes-open-close-brackets

// ##########################################################
// ###########  BosonPrimitiveOperators #####################
// ##########################################################

// **********************************************************
// ***  BosonCreationOperator                             ***
// **********************************************************

class BosonCreationOperator final : public LeafExpression {
   public:
    BosonCreationOperator(std::shared_ptr<Boson> boson);
    std::string str() const override;
    std::string repr() const override;

   private:
    std::shared_ptr<Boson> _boson;
};

inline BosonCreationOperator::BosonCreationOperator(std::shared_ptr<Boson> boson) : _boson(boson) {
    assert(boson);
}

inline std::string BosonCreationOperator::str() const {
    return "♯" + _boson->str();
}

inline std::string BosonCreationOperator::repr() const {
    return "BosonCreationOperator(" + _boson->repr() + ")";
}

// **********************************************************
// ***  BosonAnihilationOperator                          ***
// **********************************************************

class BosonAnihilationOperator final : public LeafExpression {
   public:
    BosonAnihilationOperator(std::shared_ptr<Boson> boson);
    std::string str() const override;
    std::string repr() const override;

   private:
    std::shared_ptr<Boson> _boson;
};

inline BosonAnihilationOperator::BosonAnihilationOperator(std::shared_ptr<Boson> boson) : _boson(boson) {
    assert(boson);
}

inline std::string BosonAnihilationOperator::str() const {
    return "♭" + _boson->str();
}

inline std::string BosonAnihilationOperator::repr() const {
    return "BosonAnihilationOperator(" + _boson->repr() + ")";
}

// **********************************************************
// ***  BosonNumberOperator                               ***
// **********************************************************

class BosonNumberOperator final : public LeafExpression {
   public:
    BosonNumberOperator(std::shared_ptr<Boson> boson);
    std::string str() const override;
    std::string repr() const override;

   private:
    std::shared_ptr<Boson> _boson;
};

inline BosonNumberOperator::BosonNumberOperator(std::shared_ptr<Boson> boson) : _boson(boson) {
    assert(boson);
}

inline std::string BosonNumberOperator::str() const {
    return "ℕ" + _boson->str();
}

inline std::string BosonNumberOperator::repr() const {
    return "BosonNumberOperator(" + _boson->repr() + ")";
}

// ****************************************************************************************************************

// ##########################################################
// ###########  StructuredExpressions        ################
// ##########################################################

// **********************************************************
// ***  IntegerFactoredExpression                         ***
// **********************************************************

class IntegerFactoredExpression final : public BridgeExpression {
   public:
    IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl);
    std::string str() const override;
    std::string repr() const override;

   private:
    long _factor;
};

inline IntegerFactoredExpression::IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl)
    : BridgeExpression(std::move(expr_hdl)), _factor(factor) {
}

inline std::string IntegerFactoredExpression::str() const {
    return "❪" + std::to_string(_factor) + subexpression(0).target().str() + "❫";
}

inline std::string IntegerFactoredExpression::repr() const {
    return "IntegerFactor(" + std::to_string(_factor) + "," + subexpression(0).target().repr() + ")";
}

// **********************************************************
// ***  ProductExpression                                 ***
// **********************************************************

class ProductExpression final : public VectorNumerousExpression {
   public:
    ProductExpression(std::vector<ExpressionHandler>&& expr_hdls);
    template<class... Args>
    ProductExpression(Args&&... expr_hdls);

    std::string str() const override;
    std::string repr() const override;
};

inline ProductExpression::ProductExpression(std::vector<ExpressionHandler>&& expr_hdls)
    : VectorNumerousExpression(std::move(expr_hdls)) {
}

template<class... Args>
inline ProductExpression::ProductExpression(Args&&... expr_hdls)
    : VectorNumerousExpression(std::move(expr_hdls)...) {
}

inline std::string ProductExpression::str() const {
    if (n_subexpressions() == 0) {
        return "𝕀";
    }
    std::string result;
    result += "❪";
    result += subexpression(0).target().str();
    for (unsigned n_subexpression = 1; n_subexpression < n_subexpressions(); n_subexpression++) {
        result += "◦";
        result += subexpression(n_subexpression).target().str();
    }
    result += "❫";
    return result;
}

inline std::string ProductExpression::repr() const {
    std::string result;
    result += "Product(";
    if (n_subexpressions() > 0) {
        result += subexpression(0).target().repr();
    }
    for (unsigned n_subexpression = 1; n_subexpression < n_subexpressions(); n_subexpression++) {
        result += ",";
        result += subexpression(n_subexpression).target().repr();
    }
    result += ")";
    return result;
}

// **********************************************************
// ***  IntegerLinearCombinationExpression                ***
// **********************************************************

//TODO

}  // namespace boson_algebra

#endif
