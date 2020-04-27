#ifndef BOSON_ALGEBRA_EXPRESSION_ABSTRACT_HPP
#define BOSON_ALGEBRA_EXPRESSION_ABSTRACT_HPP

// SELF:
#include <boson_algebra/str_repr.hpp>
// BOOST:
#include <boost/range/any_range.hpp>
// STD STL:
#include <array>
#include <list>
#include <map>
#include <string>
#include <vector>
// STD NOT-STL:
//#include <iostream>
#include <functional>
#include <memory>
#include <type_traits>
// STC C:
#include <cassert>

#define UNUSED(x) (void)x;

// **********************************************************
// ***  Expression + ExpressionHandler                    ***
// **********************************************************

namespace boson_algebra {

class Expression;
class ExpressionHandler;


using ExpressionHandlerVector = std::vector<ExpressionHandler>;
using ExpressionHandlerList = std::list<ExpressionHandler>;
template <std::size_t N>
using ExpressionHandlerArray = std::array<ExpressionHandler, N>;
template <class KeyT>
using ExpressionHandlerMap = std::map<KeyT, ExpressionHandler>;
using ExpressionHandlerOptional = std::optional<ExpressionHandler>;
using SafeTransformFunctionT = std::function<ExpressionHandlerOptional(const ExpressionHandler&)>;
//using UnsafeTransformFunctionT = std::function<std::unique_ptr<Expression>(Expression&&)>;
using ExpressionHandlerSinglePassRange = boost::any_range<ExpressionHandler, boost::single_pass_traversal_tag>;
using ExpressionHandlerForwardRange = boost::any_range<ExpressionHandler, boost::forward_traversal_tag>;
using ExpressionHandlerBidirectionalRange = boost::any_range<ExpressionHandler, boost::bidirectional_traversal_tag>;
using ExpressionHandlerRandomAccessRange = boost::any_range<ExpressionHandler, boost::random_access_traversal_tag>;
using ConstExpressionHandlerSinglePassRange = boost::any_range<const ExpressionHandler, boost::single_pass_traversal_tag>;
using ConstExpressionHandlerForwardRange = boost::any_range<const ExpressionHandler, boost::forward_traversal_tag>;
using ConstExpressionHandlerBidirectionalRange = boost::any_range<const ExpressionHandler, boost::bidirectional_traversal_tag>;
using ConstExpressionHandlerRandomAccessRange = boost::any_range<const ExpressionHandler, boost::random_access_traversal_tag>;

class ExpressionHandler final : public StrRepr {
   public:
    // move semantic:
    ExpressionHandler(ExpressionHandler&&) = default;
    ExpressionHandler& operator=(ExpressionHandler&&) = default;
    // copy semantic:
    ExpressionHandler(const ExpressionHandler&) = delete;
    ExpressionHandler& operator=(const ExpressionHandler&) = delete;
    // creation model:
    template <class ExpressionDerrivedClass, class... Args>
    static ExpressionHandler make(Args&&... expression_class_ctor_args);
    // accessors:
    Expression& target();
    const Expression& target() const;
    template <class ExpressionDerrivedClass>
    ExpressionDerrivedClass& casted_target();
    template <class ExpressionDerrivedClass>
    const ExpressionDerrivedClass& casted_target() const;
    template <class ExpressionDerrivedClass>
    const bool is_of_type() const;
    // quick access for the underying expression -- tree structure accessos:
    unsigned n_subexpressions() const;
    ExpressionHandler& subexpression(unsigned n_subexpression);
    const ExpressionHandler& subexpression(unsigned n_subexpression) const;
    ExpressionHandlerRandomAccessRange range();
    ConstExpressionHandlerRandomAccessRange range() const;
    ConstExpressionHandlerRandomAccessRange crange() const;
    // quick access for the underying expression -- string representation:
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
    virtual ExpressionHandlerRandomAccessRange range() = 0;
    virtual ConstExpressionHandlerRandomAccessRange range() const = 0;
    virtual ConstExpressionHandlerRandomAccessRange crange() const = 0;
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

template <class ExpressionDerrivedClass, class... Args>
ExpressionHandler ExpressionHandler::make(Args&&... expression_class_ctor_args) {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    return ExpressionHandler(std::unique_ptr<ExpressionDerrivedClass>(new ExpressionDerrivedClass(std::forward<Args>(expression_class_ctor_args)...)));
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

inline unsigned ExpressionHandler::n_subexpressions() const {
    return target().n_subexpressions();
}

inline ExpressionHandler& ExpressionHandler::subexpression(unsigned n_subexpression) {
    return target().subexpression(n_subexpression);
}

inline const ExpressionHandler& ExpressionHandler::subexpression(unsigned n_subexpression) const {
    return target().subexpression(n_subexpression);
}

inline ExpressionHandlerRandomAccessRange ExpressionHandler::range() {
    return target().range();
}

inline ConstExpressionHandlerRandomAccessRange ExpressionHandler::range() const {
    return target().range();
}

inline ConstExpressionHandlerRandomAccessRange ExpressionHandler::crange() const {
    return target().crange();
}

inline ExpressionHandler ExpressionHandler::clone() const {
    return ExpressionHandler(target().clone());
}

inline bool ExpressionHandler::equals(const ExpressionHandler& other) const {
    return target().equals(other.target());
}

template <class ExpressionDerrivedClass>
ExpressionDerrivedClass& ExpressionHandler::casted_target() {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(is_of_type<ExpressionDerrivedClass>());
    return dynamic_cast<ExpressionDerrivedClass&>(target());
}

template <class ExpressionDerrivedClass>
const ExpressionDerrivedClass& ExpressionHandler::casted_target() const {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(is_of_type<ExpressionDerrivedClass>());
    return dynamic_cast<const ExpressionDerrivedClass&>(target());
}

template <class ExpressionDerrivedClass>
const bool ExpressionHandler::is_of_type() const {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    return bool(dynamic_cast<const ExpressionDerrivedClass*>(&target()));
}

inline void ExpressionHandler::safe_dfs_transform(const SafeTransformFunctionT& fun) {
    for (unsigned n_subexpression = 0; n_subexpression < target().n_subexpressions(); n_subexpression++) {
        target().subexpression(n_subexpression).safe_dfs_transform(fun);
    }
    while (auto transformation_result = fun(*this)) {
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

}  // namespace boson_algebra

#endif
