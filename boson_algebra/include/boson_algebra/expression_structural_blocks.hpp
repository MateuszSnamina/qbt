#ifndef BOSON_ALGEBRA_EXPRESSION_STRUCTURAL_BLOCKS_HPP
#define BOSON_ALGEBRA_EXPRESSION_STRUCTURAL_BLOCKS_HPP

#include <boson_algebra/expression_common.hpp>

// References:
// (1) list-of-all-unicodes-open-close-brackets:
// https://stackoverflow.com/questions/13535172/list-of-all-unicodes-open-close-brackets

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
    IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl) noexcept;
    std::unique_ptr<IntegerFactoredExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);

   private:
    long _factor;
};

inline IntegerFactoredExpression::IntegerFactoredExpression(long factor, ExpressionHandler&& expr_hdl) noexcept
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
    auto fancy_to_string = [](auto _) -> std::string {
        if (_ == +1) {
            return "+";
        }
        if (_ == -1) {
            return "-";
        }
        return std::to_string(_);
    };
    return "❪" + fancy_to_string(_factor) + subexpression(0).target().str() + "❫";
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
    static ExpressionHandler make_from_buffer(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    static ExpressionHandler make(Args&&... expr_hdls);
    static ExpressionHandler make_identity();
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    bool is_identity() const;  // it is identity if it is empty.

   private:
    ProductExpression(FromBufferTag, ExpressionHandlerVector&& expr_hdls) noexcept;
    template <class... Args>
    ProductExpression(VariadicTag, Args&&... expr_hdls) noexcept;
    std::unique_ptr<ProductExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline ProductExpression::ProductExpression(FromBufferTag, ExpressionHandlerVector&& expr_hdls) noexcept
    : VectorNumerousExpression(FromBufferTag{}, std::move(expr_hdls)) {
}

template <class... Args>
inline ProductExpression::ProductExpression(VariadicTag, Args&&... expr_hdls) noexcept
    : VectorNumerousExpression(VariadicTag{}, std::forward<Args>(expr_hdls)...) {
}

inline ExpressionHandler ProductExpression::make_from_buffer(ExpressionHandlerVector&& expr_hdls) {
    return ExpressionHandler::make<ProductExpression>(FromBufferTag{}, std::move(expr_hdls));
}

template <class... Args>
ExpressionHandler ProductExpression::make(Args&&... expr_hdls) {
    return ExpressionHandler::make<ProductExpression>(VariadicTag{}, std::forward<Args>(expr_hdls)...);
}

inline ExpressionHandler ProductExpression::make_identity() {
    return make();
}

inline std::unique_ptr<ProductExpression> ProductExpression::casted_clone() const {
    auto v = clone_expr_hdls_vector();
    return std::unique_ptr<ProductExpression>(new ProductExpression(FromBufferTag{}, std::move(v)));
}

inline ExpressionHandler ProductExpression::clone() const {
    auto v = clone_expr_hdls_vector();
    return ExpressionHandler::make<ProductExpression>(FromBufferTag{}, std::move(v));
}

inline bool ProductExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const ProductExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    return equals_helper_function(casted_other);
}

inline std::string ProductExpression::str() const {
    return str_helper_function("𝕀", "◦", {"❪", "❫"});
}

inline std::string ProductExpression::repr() const {
    return repr_helper_function("Product");
}

inline bool ProductExpression::is_identity() const {
    return n_subexpressions() == 0;
}

}  // namespace boson_algebra

// **********************************************************
// ***  SumExpression                                     ***
// **********************************************************

namespace boson_algebra {
class SumExpression final : public VectorNumerousExpression {
   public:
    static ExpressionHandler make_from_buffer(ExpressionHandlerVector&& expr_hdls);
    template <class... Args>
    static ExpressionHandler make(Args&&... expr_hdls);
    static ExpressionHandler make_zero();
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;
    bool is_zero() const;  // it is zero if it is empy.
   private:
    SumExpression(FromBufferTag, ExpressionHandlerVector&& expr_hdls) noexcept;
    template <class... Args>
    SumExpression(VariadicTag, Args&&... expr_hdls) noexcept;
    std::unique_ptr<SumExpression> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline SumExpression::SumExpression(FromBufferTag, std::vector<ExpressionHandler>&& expr_hdls) noexcept
    : VectorNumerousExpression(FromBufferTag{}, std::move(expr_hdls)) {
}

template <class... Args>
inline SumExpression::SumExpression(VariadicTag, Args&&... expr_hdls) noexcept
    : VectorNumerousExpression(VariadicTag{}, std::forward<Args>(expr_hdls)...) {
}

inline ExpressionHandler SumExpression::make_from_buffer(ExpressionHandlerVector&& expr_hdls) {
    return ExpressionHandler::make<SumExpression>(FromBufferTag{}, std::move(expr_hdls));
}

template <class... Args>
ExpressionHandler SumExpression::make(Args&&... expr_hdls) {
    return ExpressionHandler::make<SumExpression>(VariadicTag{}, std::forward<Args>(expr_hdls)...);
}

inline ExpressionHandler SumExpression::make_zero() {
    return make();
}

inline std::unique_ptr<SumExpression> SumExpression::casted_clone() const {
    auto v = clone_expr_hdls_vector();
    return std::unique_ptr<SumExpression>(new SumExpression(FromBufferTag{}, std::move(v)));
}

inline ExpressionHandler SumExpression::clone() const {
    auto v = clone_expr_hdls_vector();
    return ExpressionHandler::make<SumExpression>(FromBufferTag{}, std::move(v));
}

inline bool SumExpression::equals(const Expression& other) const {
    const auto casted_other_ptr = dynamic_cast<const SumExpression*>(&other);
    if (!casted_other_ptr) {
        return false;
    }
    const auto& casted_other = *casted_other_ptr;
    return equals_helper_function(casted_other);
}

inline std::string SumExpression::str() const {
    return str_helper_function("𝟘", "+", {"❴", "❵"});
}

inline std::string SumExpression::repr() const {
    return repr_helper_function("Sum");
}

inline bool SumExpression::is_zero() const {
    return n_subexpressions() == 0;
}

}  // namespace boson_algebra

#endif
