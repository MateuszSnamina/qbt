#ifndef BOSON_ALGEBRA_EXPRESSION_ABSTRACT_HPP
#define BOSON_ALGEBRA_EXPRESSION_ABSTRACT_HPP

// SELF:
#include <boson_algebra/str_repr.hpp>
// BOOST:
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/range/any_range.hpp>
// STD STL:
#include <array>
#include <list>
#include <map>
#include <string>
#include <vector>
// STD NOT-STL:
//#include <iostream>//DEBUG
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
    // copy semantic:
    ExpressionHandler(const ExpressionHandler&) = delete;
    ExpressionHandler& operator=(const ExpressionHandler&) = delete;
    // move semantic:
    ExpressionHandler(ExpressionHandler&&);
    ExpressionHandler& operator=(ExpressionHandler&&);
    // drained checker (drained = after move => invalid):
    bool is_shallow_drained() const;
    bool is_deep_drained() const;
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
    // modifier algorithms:
    void safe_dfs_transform(const SafeTransformFunctionT&, bool greedy = true);
    //void unsafe_dfs_transform(const UnsafeTransformFunctionT&);

   private:
    ExpressionHandler(std::unique_ptr<Expression>);
    std::unique_ptr<Expression> substitute(std::unique_ptr<Expression>);
    friend void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2);

   private:
    std::unique_ptr<Expression> _expr;
    bool _is_drained;
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

inline ExpressionHandler::ExpressionHandler(std::unique_ptr<Expression> expr)
    : _expr(nullptr),
      _is_drained(true) {
    assert(expr);
    _expr = std::move(expr);
    _is_drained = false;
}

inline ExpressionHandler::ExpressionHandler(ExpressionHandler&& other)
    : _expr(nullptr),
      _is_drained(true) {
    assert(!other.is_shallow_drained());
    assert(other._expr);
    other._is_drained = true;
    _expr = std::move(other._expr);
    _is_drained = false;
}

inline ExpressionHandler& ExpressionHandler::operator=(ExpressionHandler&& other) {
    assert(!other.is_shallow_drained());
    assert(other._expr);
    other._is_drained = true;
    _expr = std::move(other._expr);
    _is_drained = false;
    return *this;
}

inline bool ExpressionHandler::is_shallow_drained() const {
    return _is_drained;
}

inline bool ExpressionHandler::is_deep_drained() const {
    if (_is_drained) {
        return true;
    }
    return boost::algorithm::any_of(crange(), [](const auto& _) { return _.is_deep_drained(); });
}

template <class ExpressionDerrivedClass, class... Args>
ExpressionHandler ExpressionHandler::make(Args&&... expression_class_ctor_args) {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    return ExpressionHandler(std::unique_ptr<ExpressionDerrivedClass>(new ExpressionDerrivedClass(std::forward<Args>(expression_class_ctor_args)...)));
}

inline Expression& ExpressionHandler::target() {
    assert(!is_shallow_drained());
    assert(_expr);
    return *_expr;
}

inline const Expression& ExpressionHandler::target() const {
    return *_expr;
}

inline std::string ExpressionHandler::str() const {
    assert(!is_shallow_drained());
    return target().str();
}

inline std::string ExpressionHandler::repr() const {
    assert(!is_shallow_drained());
    return target().repr();
}

inline unsigned ExpressionHandler::n_subexpressions() const {
    assert(!is_shallow_drained());
    return target().n_subexpressions();
}

inline ExpressionHandler& ExpressionHandler::subexpression(unsigned n_subexpression) {
    assert(!is_shallow_drained());
    return target().subexpression(n_subexpression);
}

inline const ExpressionHandler& ExpressionHandler::subexpression(unsigned n_subexpression) const {
    assert(!is_shallow_drained());
    return target().subexpression(n_subexpression);
}

inline ExpressionHandlerRandomAccessRange ExpressionHandler::range() {
    assert(!is_shallow_drained());
    return target().range();
}

inline ConstExpressionHandlerRandomAccessRange ExpressionHandler::range() const {
    assert(!is_shallow_drained());
    return target().range();
}

inline ConstExpressionHandlerRandomAccessRange ExpressionHandler::crange() const {
    assert(!is_shallow_drained());
    return target().crange();
}

inline ExpressionHandler ExpressionHandler::clone() const {
    assert(!is_shallow_drained());
    return ExpressionHandler(target().clone());
}

inline bool ExpressionHandler::equals(const ExpressionHandler& other) const {
    assert(!other.is_shallow_drained());
    assert(!is_shallow_drained());
    return target().equals(other.target());
}

template <class ExpressionDerrivedClass>
ExpressionDerrivedClass& ExpressionHandler::casted_target() {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(!is_shallow_drained());
    assert(is_of_type<ExpressionDerrivedClass>());
    return dynamic_cast<ExpressionDerrivedClass&>(target());
}

template <class ExpressionDerrivedClass>
const ExpressionDerrivedClass& ExpressionHandler::casted_target() const {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(!is_shallow_drained());
    assert(is_of_type<ExpressionDerrivedClass>());
    return dynamic_cast<const ExpressionDerrivedClass&>(target());
}

template <class ExpressionDerrivedClass>
const bool ExpressionHandler::is_of_type() const {
    static_assert(std::is_base_of_v<Expression, ExpressionDerrivedClass>);
    assert(!is_shallow_drained());
    return bool(dynamic_cast<const ExpressionDerrivedClass*>(&target()));
}

inline void ExpressionHandler::safe_dfs_transform(const SafeTransformFunctionT& fun, bool greedy) {
    assert(!is_shallow_drained());
    for (unsigned n_subexpression = 0; n_subexpression < target().n_subexpressions(); n_subexpression++) {
        target().subexpression(n_subexpression).safe_dfs_transform(fun, greedy);
    }
    if (greedy) {
        while (auto transformation_result = fun(*this)) {
            swap(*this, *transformation_result);
        }
    } else {
        if (auto transformation_result = fun(*this)) {
            swap(*this, *transformation_result);
        }
    }
}

inline std::unique_ptr<Expression>
ExpressionHandler::substitute(std::unique_ptr<Expression> expr) {
    assert(expr);
    std::swap(_expr, expr);
    _is_drained = false;
    return expr;
}

inline void swap(ExpressionHandler& expr_1, ExpressionHandler& expr_2) {
    std::swap(expr_1._expr, expr_2._expr);
    std::swap(expr_1._is_drained, expr_2._is_drained);
}

}  // namespace boson_algebra

#endif