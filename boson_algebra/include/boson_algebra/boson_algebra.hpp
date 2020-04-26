#ifndef BOSON_ALGEBRA_BOSON_ALGEBRA_HPP
#define BOSON_ALGEBRA_BOSON_ALGEBRA_HPP

#include <array>
#include <boson_algebra/util_make.hpp>
#include <cassert>
#include <functional>
#include <iostream>  //DEBUG
#include <list>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
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

class ExpressionHandler final : public StrRepr {
    using ExpressionHandlerOptional = std::optional<ExpressionHandler>;
    using SafeTransformFunctionT = std::function<ExpressionHandlerOptional(const Expression&)>;

   public:
    // move semantic:
    ExpressionHandler(ExpressionHandler&&) = default;
    ExpressionHandler& operator=(ExpressionHandler&&) = default;
    // copy semantic:
    ExpressionHandler(const ExpressionHandler&) = delete;
    ExpressionHandler& operator=(const ExpressionHandler&) = delete;
    // creation model:
    template <class ExpressionClass, class... Args>
    static ExpressionHandler make(Args&&... expression_class_ctor_args);
    // accessors:
    Expression& target();
    const Expression& target() const;
    // string representation:
    std::string str() const override;
    std::string repr() const override;
    // other methods:
    ExpressionHandler clone() const;
    bool equals(const ExpressionHandler&) const;
    void safe_dfs_transform(const SafeTransformFunctionT&);
    //void unsafe_dfs_transform(const UnsafeTransformFunctionT&);

   private:
    ExpressionHandler(std::unique_ptr<Expression>);
    std::unique_ptr<Expression> substitute(std::unique_ptr<Expression>);
    friend void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2);

   private:
    std::unique_ptr<Expression> _expr;
};

using ExpressionHandlerVector = std::vector<ExpressionHandler>;
using ExpressionHandlerList = std::list<ExpressionHandler>;
template <std::size_t N>
using ExpressionHandlerArray = std::array<ExpressionHandler, N>;
template <class KeyT>
using ExpressionHandlerMap = std::map<KeyT, ExpressionHandler>;
using ExpressionHandlerOptional = std::optional<ExpressionHandler>;
using SafeTransformFunctionT = std::function<ExpressionHandlerOptional(const Expression&)>;
//using UnsafeTransformFunctionT = std::function<std::unique_ptr<Expression>(Expression&&)>;

class Expression : public StrRepr {
   public:
    // copy semantic:
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
    // move semantic:
    Expression(Expression&&) = default;
    Expression& operator=(Expression&&) = default;
    // tree structure accessos:
    virtual unsigned n_subexpressions() const = 0;
    virtual ExpressionHandler& subexpression(unsigned n_subexpression) = 0;
    virtual const ExpressionHandler& subexpression(unsigned n_subexpression) const = 0;
    // tree structure operations:
    virtual ExpressionHandler clone() const = 0;
    virtual bool equals(const Expression&) const = 0;
    // dctor:
    virtual ~Expression() = default;

   protected:
    Expression() = default;
};

// **********************************************************

inline ExpressionHandler::ExpressionHandler(std::unique_ptr<Expression> expr) : _expr(std::move(expr)) {
    assert(_expr);
}

template <class ExpressionClass, class... Args>
ExpressionHandler ExpressionHandler::make(Args&&... expression_class_ctor_args) {
    static_assert(std::is_base_of_v<Expression, ExpressionClass>);
    return ExpressionHandler(std::unique_ptr<ExpressionClass>(new ExpressionClass(std::forward<Args>(expression_class_ctor_args)...)));
}

inline Expression& ExpressionHandler::target() {
    return *_expr;
}

inline const Expression& ExpressionHandler::target() const {
    return *_expr;
}

inline std::string ExpressionHandler::str() const {
    return target().str();
}

inline std::string ExpressionHandler::repr() const {
    return target().repr();
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
    while (auto transformation_result = fun(target())) {
        swap(*this, *transformation_result);
    }
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
// ***  LeafExpression                                    ***
// **********************************************************

class LeafExpression : public Expression {
   public:
    // copy semantic:
    LeafExpression(const LeafExpression&) = delete;
    LeafExpression& operator=(const LeafExpression&) = delete;
    // tree structure accessos:
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    // dtor:
    ~LeafExpression() = 0;

   protected:
    // ctor:
    LeafExpression() = default;
    // move semantic:
    LeafExpression(LeafExpression&&) = default;
    boson_algebra::LeafExpression& operator=(LeafExpression&&) = default;
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
    // copy semantic:
    BridgeExpression(const BridgeExpression&) = delete;
    BridgeExpression& operator=(const BridgeExpression&) = delete;
    // tree structure accessos:
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    // dctor:
    ~BridgeExpression() = 0;

   protected:
    // ctor:
    BridgeExpression(ExpressionHandler&&);
    // move semantic:
    BridgeExpression(BridgeExpression&&) = default;
    BridgeExpression& operator=(BridgeExpression&&) = default;

   private:
    ExpressionHandler _expr_hdl;
};

inline BridgeExpression::BridgeExpression(ExpressionHandler&& expr_hdl)
    : _expr_hdl(std::move(expr_hdl)) {
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
    // copy semantic:
    VectorNumerousExpression(const VectorNumerousExpression&) = delete;
    VectorNumerousExpression& operator=(const VectorNumerousExpression&) = delete;
    // tree structure accessos:
    unsigned n_subexpressions() const override;
    ExpressionHandler& subexpression(unsigned n_subexpression) override;
    const ExpressionHandler& subexpression(unsigned n_subexpression) const override;
    // dctor:
    ~VectorNumerousExpression();

   protected:
    // ctor:
    VectorNumerousExpression(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    VectorNumerousExpression(Args&&... expr_hdls);
    // move semantic:
    VectorNumerousExpression(VectorNumerousExpression&&) = default;
    VectorNumerousExpression& operator=(VectorNumerousExpression&&) = default;
    // helper function:
    ExpressionHandlerVector clone_expr_hdls_vector() const;

   private:
    ExpressionHandlerVector _expr_hdls;
};

inline VectorNumerousExpression::VectorNumerousExpression(ExpressionHandlerVector&& expr_hdls)
    : _expr_hdls(std::move(expr_hdls)) {
}

template <class... Args>
VectorNumerousExpression::VectorNumerousExpression(Args&&... expr_hdls)
    : _expr_hdls(util::make<ExpressionHandlerVector>(std::move(expr_hdls)...)) {
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
    std::shared_ptr<Boson> boson() const;

   protected:
    // ctor:
    BosonPrimitiveOperators(std::shared_ptr<Boson> boson);
    // move semantic:
    BosonPrimitiveOperators(BosonPrimitiveOperators&&) = default;
    BosonPrimitiveOperators& operator=(BosonPrimitiveOperators&&) = default;

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
    static ExpressionHandler make(std::shared_ptr<Boson> boson);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    BosonCreationOperator(std::shared_ptr<Boson> boson);
    std::unique_ptr<BosonCreationOperator> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline BosonCreationOperator::BosonCreationOperator(std::shared_ptr<Boson> boson)
    : BosonPrimitiveOperators(boson) {
}

inline ExpressionHandler BosonCreationOperator::make(std::shared_ptr<Boson> boson) {
    return ExpressionHandler::make<BosonCreationOperator>(boson);
}

inline std::unique_ptr<BosonCreationOperator> BosonCreationOperator::casted_clone() const {
    return std::unique_ptr<BosonCreationOperator>(new BosonCreationOperator(boson()));
}

inline ExpressionHandler BosonCreationOperator::clone() const {
    return ExpressionHandler::make<BosonCreationOperator>(boson());
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
    static ExpressionHandler make(std::shared_ptr<Boson> boson);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    BosonAnihilationOperator(std::shared_ptr<Boson> boson);
    std::unique_ptr<BosonAnihilationOperator> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline BosonAnihilationOperator::BosonAnihilationOperator(std::shared_ptr<Boson> boson)
    : BosonPrimitiveOperators(boson) {
}

inline ExpressionHandler BosonAnihilationOperator::make(std::shared_ptr<Boson> boson) {
    return ExpressionHandler::make<BosonAnihilationOperator>(boson);
}

inline std::unique_ptr<BosonAnihilationOperator> BosonAnihilationOperator::casted_clone() const {
    return std::unique_ptr<BosonAnihilationOperator>(new BosonAnihilationOperator(boson()));
}

inline ExpressionHandler BosonAnihilationOperator::clone() const {
    return ExpressionHandler::make<BosonAnihilationOperator>(boson());
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
    static ExpressionHandler make(std::shared_ptr<Boson> boson);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    BosonNumberOperator(std::shared_ptr<Boson> boson);
    std::unique_ptr<BosonNumberOperator> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline BosonNumberOperator::BosonNumberOperator(std::shared_ptr<Boson> boson)
    : BosonPrimitiveOperators(boson) {
}

inline ExpressionHandler BosonNumberOperator::make(std::shared_ptr<Boson> boson) {
    return ExpressionHandler::make<BosonNumberOperator>(boson);
}

inline std::unique_ptr<BosonNumberOperator> BosonNumberOperator::casted_clone() const {
    return std::unique_ptr<BosonNumberOperator>(new BosonNumberOperator(boson()));
}

inline ExpressionHandler BosonNumberOperator::clone() const {
    return ExpressionHandler::make<BosonNumberOperator>(boson());
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
    static ExpressionHandler make(long factor, ExpressionHandler&& expr_hdl);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    long factor() const;

   private:
    IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl);
    std::unique_ptr<IntegerFactoredExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);

   private:
    long _factor;
};

inline IntegerFactoredExpression::IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl)
    : BridgeExpression(std::move(expr_hdl)), _factor(factor) {
}

inline ExpressionHandler IntegerFactoredExpression::make(long factor, ExpressionHandler&& expr_hdl) {
    return ExpressionHandler::make<IntegerFactoredExpression>(factor, std::move(expr_hdl));
}

inline std::unique_ptr<IntegerFactoredExpression> IntegerFactoredExpression::casted_clone() const {
    return std::unique_ptr<IntegerFactoredExpression>(new IntegerFactoredExpression(_factor, subexpression(0).clone()));
}

inline ExpressionHandler IntegerFactoredExpression::clone() const {
    return ExpressionHandler::make<IntegerFactoredExpression>(_factor, subexpression(0).clone());
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
    template <class... Args>
    ProductExpression(Args&&... expr_hdls);
    static ExpressionHandler make(std::vector<ExpressionHandler>&& expr_hdls);
    template <class... Args>
    static ExpressionHandler make(Args&&... expr_hdls);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    ProductExpression(std::vector<ExpressionHandler>&& expr_hdls);
    std::unique_ptr<ProductExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline ProductExpression::ProductExpression(std::vector<ExpressionHandler>&& expr_hdls)
    : VectorNumerousExpression(std::move(expr_hdls)) {
}

template <class... Args>
inline ProductExpression::ProductExpression(Args&&... expr_hdls)
    : VectorNumerousExpression(std::move(expr_hdls)...) {
}

inline ExpressionHandler ProductExpression::make(std::vector<ExpressionHandler>&& expr_hdls) {
    return ExpressionHandler::make<ProductExpression>(std::move(expr_hdls));
}

template <class... Args>
ExpressionHandler ProductExpression::make(Args&&... expr_hdls) {
    return ExpressionHandler::make<ProductExpression>(std::move(expr_hdls)...);
}

inline std::unique_ptr<ProductExpression> ProductExpression::casted_clone() const {
    auto v = clone_expr_hdls_vector();
    return std::unique_ptr<ProductExpression>(new ProductExpression(std::move(v)));
}

inline ExpressionHandler ProductExpression::clone() const {
    auto v = clone_expr_hdls_vector();
    return ExpressionHandler::make<ProductExpression>(std::move(v));
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
