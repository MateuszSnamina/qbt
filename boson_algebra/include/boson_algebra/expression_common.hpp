#ifndef BOSON_ALGEBRA_EXPRESSION_COMMON_HPP
#define BOSON_ALGEBRA_EXPRESSION_COMMON_HPP

#include <boson_algebra/expression_abstract.hpp>
#include <boson_algebra/util_make.hpp>

namespace boson_algebra {

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
    ExpressionHandlerRandomAccessRange range() override;
    ConstExpressionHandlerRandomAccessRange range() const override;
    ConstExpressionHandlerRandomAccessRange crange() const override;
    // dtor:
    ~LeafExpression() = 0;

   protected:
    // ctor:
    LeafExpression() = default;
    // move semantic:
    LeafExpression(LeafExpression&&) = default;
    boson_algebra::LeafExpression& operator=(LeafExpression&&) = default;

   private:
    std::array<ExpressionHandler, 0> _expr_hdls;
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

inline ExpressionHandlerRandomAccessRange LeafExpression::range() {
    return _expr_hdls;
}

inline ConstExpressionHandlerRandomAccessRange LeafExpression::range() const {
    return _expr_hdls;
}

inline ConstExpressionHandlerRandomAccessRange LeafExpression::crange() const {
    return _expr_hdls;
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
    ExpressionHandlerRandomAccessRange range() override;
    ConstExpressionHandlerRandomAccessRange range() const override;
    ConstExpressionHandlerRandomAccessRange crange() const override;
    // dctor:
    ~BridgeExpression() = 0;

   protected:
    // ctor:
    BridgeExpression(ExpressionHandler&&);
    // move semantic:
    BridgeExpression(BridgeExpression&&) = default;
    BridgeExpression& operator=(BridgeExpression&&) = default;

   private:
    std::array<ExpressionHandler, 1> _expr_hdls;
    ExpressionHandler& _expr_hdl;
};

inline BridgeExpression::BridgeExpression(ExpressionHandler&& expr_hdl)
    : _expr_hdls{std::move(expr_hdl)},
      _expr_hdl(_expr_hdls[0]) {
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

inline ExpressionHandlerRandomAccessRange BridgeExpression::range() {
    return _expr_hdls;
}

inline ConstExpressionHandlerRandomAccessRange BridgeExpression::range() const {
    return _expr_hdls;
}

inline ConstExpressionHandlerRandomAccessRange BridgeExpression::crange() const {
    return _expr_hdls;
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
    ExpressionHandlerRandomAccessRange range() override;
    ConstExpressionHandlerRandomAccessRange range() const override;
    ConstExpressionHandlerRandomAccessRange crange() const override;
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

inline ExpressionHandlerRandomAccessRange VectorNumerousExpression::range() {
    return _expr_hdls;
}

inline ConstExpressionHandlerRandomAccessRange VectorNumerousExpression::range() const {
    return _expr_hdls;
}

inline ConstExpressionHandlerRandomAccessRange VectorNumerousExpression::crange() const {
    return _expr_hdls;
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

}  // namespace boson_algebra

#endif
