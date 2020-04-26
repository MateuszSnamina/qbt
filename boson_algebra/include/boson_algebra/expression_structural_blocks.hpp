#ifndef BOSON_ALGEBRA_EXPRESSION_STRUCTURAL_BLOCKS_HPP
#define BOSON_ALGEBRA_EXPRESSION_STRUCTURAL_BLOCKS_HPP

#include <boson_algebra/expression_common.hpp>

// ##########################################################
// ###########  StructuralBlockExpressions   ################
// ##########################################################

// **********************************************************
// ***  IntegerFactoredExpression                         ***
// **********************************************************

namespace boson_algebra {

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

}  // namespace boson_algebra

// **********************************************************
// ***  ProductExpression                                 ***
// **********************************************************

namespace boson_algebra {

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

}  // namespace boson_algebra

// **********************************************************
// ***  IntegerLinearCombinationExpression                ***
// **********************************************************

namespace boson_algebra {

// TODO

}  // namespace boson_algebra

#endif
