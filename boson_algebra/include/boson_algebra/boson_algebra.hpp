#ifndef BOSON_ALGEBRA_BOSON_ALGEBRA_HPP
#define BOSON_ALGEBRA_BOSON_ALGEBRA_HPP

#include <boson_algebra/util_make.hpp>
#include <cassert>
#include <functional>
#include <iostream>  //DEBUG
#include <map>
#include <memory>
#include <string>
#include <vector>

#define UNUSED(x) (void)(x)

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

using SafeTransformFunctionT = std::function<std::unique_ptr<Expression>(const Expression&)>;
//using UnsafeTransformFunctionT = std::function<std::unique_ptr<Expression>(Expression&&)>;

class ExpressionHandler {
   public:
    ExpressionHandler(std::unique_ptr<Expression>);
    ExpressionHandler(ExpressionHandler&&);
    // void operator=(ExpressionHandler&&); //TODO - implementation.
    ExpressionHandler(const ExpressionHandler&) = delete;
    void operator=(const ExpressionHandler&) = delete;
    Expression& target();
    const Expression& target() const;
    std::unique_ptr<Expression> substitute(std::unique_ptr<Expression>);
    friend void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2);
    ExpressionHandler clone() const;
    bool equals(const ExpressionHandler&) const;
    void safe_dfs_transform(const SafeTransformFunctionT&);
    //void unsafe_dfs_transform(const UnsafeTransformFunctionT&);

   private:
    std::unique_ptr<Expression> _expr;
};

using ExpressionHandlerVector = std::vector<ExpressionHandler>;
template <class KeyT>
using ExpressionHandlerMap = std::map<KeyT, ExpressionHandler>;

class Expression : public StrRepr {
   public:
    virtual unsigned n_subexpressions() const = 0;
    virtual ExpressionHandler& subexpression(unsigned n_subexpression) = 0;
    virtual const ExpressionHandler& subexpression(unsigned n_subexpression) const = 0;
    virtual std::unique_ptr<Expression> clone() const = 0;
    virtual bool equals(const Expression&) const = 0;
    virtual ~Expression() = default;
};

// **********************************************************

//TODO move to bottom:
// inline void post_dfs_transform(const DfsTransformFunctionT&) {
// }

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

inline ExpressionHandler ExpressionHandler::clone() const {
    return ExpressionHandler(target().clone());
}

inline bool ExpressionHandler::equals(const ExpressionHandler& other) const {
    return target().equals(other.target());
}

inline void ExpressionHandler::safe_dfs_transform(const SafeTransformFunctionT& fun) {
    for (unsigned n_subexpression = 0; n_subexpression < target().n_subexpressions(); n_subexpression++) {
        target().subexpression(n_subexpression).safe_dfs_transform(fun);
    }
    // if(auto transformation_result = fun(target())) {
    //     UNUSED(substitute(std::move(transformation_result)));
    // }
    while (auto transformation_result = fun(target())) {
        UNUSED(substitute(std::move(transformation_result)));
    }
}

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
// ***  VectorNumerousExpression                          ***
// **********************************************************

class VectorNumerousExpression : public Expression {
   public:
    VectorNumerousExpression(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    VectorNumerousExpression(Args&&... expr_hdls);
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    ~VectorNumerousExpression();

   protected:
    ExpressionHandlerVector clone_expr_hdls_vector() const;

   private:
    ExpressionHandlerVector _expr_hdls;
};

inline VectorNumerousExpression::VectorNumerousExpression(ExpressionHandlerVector&& expr_hdls)
    : _expr_hdls(std::move(expr_hdls)) {
}

template <class... Args>
VectorNumerousExpression::VectorNumerousExpression(Args&&... expr_hdls) : _expr_hdls(util::make<ExpressionHandlerVector>(std::move(expr_hdls)...)) {
}

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

inline ExpressionHandlerVector VectorNumerousExpression::clone_expr_hdls_vector() const {
    ExpressionHandlerVector v;
    for (unsigned n_subexpression = 0; n_subexpression < n_subexpressions(); n_subexpression++) {
        v.emplace_back(subexpression(n_subexpression).clone());
    }
    return v;
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
    virtual bool equals(const Boson&) const = 0;
    virtual ~Boson() = default;
};

// **********************************************************
// ***  CharBoson                                         ***
// **********************************************************

class CharBoson final : public Boson {
   public:
    CharBoson(char);
    bool equals(const Boson&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    char _c;
};

inline CharBoson::CharBoson(char c) : _c(c) {
}

inline bool CharBoson::equals(const Boson& other) const {
    return get_id() == other.get_id();
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

class BosonPrimitiveOperators : public LeafExpression {
   public:
    BosonPrimitiveOperators(std::shared_ptr<Boson> boson);
    std::shared_ptr<Boson> boson() const;

   private:
    std::shared_ptr<Boson> _boson;
};

inline BosonPrimitiveOperators::BosonPrimitiveOperators(std::shared_ptr<Boson> boson) : _boson(boson) {
    assert(boson);
}

inline std::shared_ptr<Boson> BosonPrimitiveOperators::boson() const {
    return _boson;
}

// **********************************************************
// ***  BosonCreationOperator                             ***
// **********************************************************

class BosonCreationOperator final : public BosonPrimitiveOperators {
   public:
    BosonCreationOperator(std::shared_ptr<Boson> boson);
    std::unique_ptr<BosonCreationOperator> casted_clone() const;
    std::unique_ptr<Expression> clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
};

inline BosonCreationOperator::BosonCreationOperator(std::shared_ptr<Boson> boson)
    : BosonPrimitiveOperators(boson) {
}

inline std::unique_ptr<BosonCreationOperator> BosonCreationOperator::casted_clone() const {
    return std::make_unique<BosonCreationOperator>(boson());
}

inline std::unique_ptr<Expression> BosonCreationOperator::clone() const {
    return casted_clone();
}

inline bool BosonCreationOperator::equals(const Expression& other) const {
    const auto casted_other = dynamic_cast<const BosonCreationOperator*>(&other);
    return (casted_other ? boson()->equals(*casted_other->boson()) : false);
}

inline std::string BosonCreationOperator::str() const {
    return "♯" + boson()->str();
}

inline std::string BosonCreationOperator::repr() const {
    return "BosonCreationOperator(" + boson()->repr() + ")";
}

// **********************************************************
// ***  BosonAnihilationOperator                          ***
// **********************************************************

class BosonAnihilationOperator final : public BosonPrimitiveOperators {
   public:
    BosonAnihilationOperator(std::shared_ptr<Boson> boson);
    std::unique_ptr<BosonAnihilationOperator> casted_clone() const;
    std::unique_ptr<Expression> clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
};

inline BosonAnihilationOperator::BosonAnihilationOperator(std::shared_ptr<Boson> boson)
    : BosonPrimitiveOperators(boson) {
}

inline std::unique_ptr<BosonAnihilationOperator> BosonAnihilationOperator::casted_clone() const {
    return std::make_unique<BosonAnihilationOperator>(boson());
}

inline std::unique_ptr<Expression> BosonAnihilationOperator::clone() const {
    return casted_clone();
}

inline bool BosonAnihilationOperator::equals(const Expression& other) const {
    const auto casted_other = dynamic_cast<const BosonAnihilationOperator*>(&other);
    return (casted_other ? boson()->equals(*casted_other->boson()) : false);
}

inline std::string BosonAnihilationOperator::str() const {
    return "♭" + boson()->str();
}

inline std::string BosonAnihilationOperator::repr() const {
    return "BosonAnihilationOperator(" + boson()->repr() + ")";
}

// **********************************************************
// ***  BosonNumberOperator                               ***
// **********************************************************

class BosonNumberOperator final : public BosonPrimitiveOperators {
   public:
    BosonNumberOperator(std::shared_ptr<Boson> boson);
    std::unique_ptr<BosonNumberOperator> casted_clone() const;
    std::unique_ptr<Expression> clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
};

inline BosonNumberOperator::BosonNumberOperator(std::shared_ptr<Boson> boson)
    : BosonPrimitiveOperators(boson) {
}

inline std::unique_ptr<BosonNumberOperator> BosonNumberOperator::casted_clone() const {
    return std::make_unique<BosonNumberOperator>(boson());
}

inline std::unique_ptr<Expression> BosonNumberOperator::clone() const {
    return casted_clone();
}

inline bool BosonNumberOperator::equals(const Expression& other) const {
    const auto casted_other = dynamic_cast<const BosonNumberOperator*>(&other);
    return (casted_other ? boson()->equals(*casted_other->boson()) : false);
}

inline std::string BosonNumberOperator::str() const {
    return "ℕ" + boson()->str();
}

inline std::string BosonNumberOperator::repr() const {
    return "BosonNumberOperator(" + boson()->repr() + ")";
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
    std::unique_ptr<IntegerFactoredExpression> casted_clone() const;
    std::unique_ptr<Expression> clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    long factor() const;

   private:
    long _factor;
};

inline IntegerFactoredExpression::IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl)
    : BridgeExpression(std::move(expr_hdl)), _factor(factor) {
}

inline std::unique_ptr<IntegerFactoredExpression> IntegerFactoredExpression::casted_clone() const {
    return std::make_unique<IntegerFactoredExpression>(_factor, subexpression(0).clone());
}

inline std::unique_ptr<Expression> IntegerFactoredExpression::clone() const {
    return casted_clone();
}

inline bool IntegerFactoredExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const IntegerFactoredExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    if (_factor != casted_other._factor) {
        return false;
    }
    if (!subexpression(0).equals(other.subexpression(0))) {
        return false;
    }
    return true;
}

inline std::string IntegerFactoredExpression::str() const {
    return "❪" + std::to_string(_factor) + subexpression(0).target().str() + "❫";
}

inline std::string IntegerFactoredExpression::repr() const {
    return "IntegerFactor(" + std::to_string(_factor) + "," + subexpression(0).target().repr() + ")";
}

inline long IntegerFactoredExpression::factor() const {
    return _factor;
}
// **********************************************************
// ***  ProductExpression                                 ***
// **********************************************************

class ProductExpression final : public VectorNumerousExpression {
   public:
    ProductExpression(std::vector<ExpressionHandler>&& expr_hdls);
    template <class... Args>
    ProductExpression(Args&&... expr_hdls);
    std::unique_ptr<ProductExpression> casted_clone() const;
    std::unique_ptr<Expression> clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
};

inline ProductExpression::ProductExpression(std::vector<ExpressionHandler>&& expr_hdls)
    : VectorNumerousExpression(std::move(expr_hdls)) {
}

template <class... Args>
inline ProductExpression::ProductExpression(Args&&... expr_hdls)
    : VectorNumerousExpression(std::move(expr_hdls)...) {
}

inline std::unique_ptr<ProductExpression> ProductExpression::casted_clone() const {
    auto v = clone_expr_hdls_vector();
    return std::make_unique<ProductExpression>(v);
}

inline std::unique_ptr<Expression> ProductExpression::clone() const {
    return casted_clone();
}

inline bool ProductExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const ProductExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    if (n_subexpressions() != casted_other.n_subexpressions()) {
        return false;
    }
    for (unsigned n_subexpression = 0; n_subexpression < n_subexpressions(); n_subexpression++) {
        if (!subexpression(n_subexpression).equals(other.subexpression(n_subexpression))) {
            return false;
        }
    }
    return true;
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
