#ifndef BOSON_ALGEBRA_EXPRESSION_BOSON_PRIMITIVE_OPERATORS_HPP
#define BOSON_ALGEBRA_EXPRESSION_BOSON_PRIMITIVE_OPERATORS_HPP

#include <boson_algebra/boson.hpp>
#include <boson_algebra/expression_common.hpp>

#define UNUSED(x) (void)x;

// ##########################################################
// ###########  BosonPrimitiveOperators #####################
// ##########################################################

// **********************************************************
// ***  BosonPrimitiveOperators                           ***
// **********************************************************

namespace boson_algebra {

class BosonPrimitiveOperators : public LeafExpression {
   public:
    std::shared_ptr<Boson> boson() const;

   protected:
    // ctor:
    BosonPrimitiveOperators(std::shared_ptr<Boson>) noexcept;
    // move semantic:
    BosonPrimitiveOperators(BosonPrimitiveOperators&&) = default;
    BosonPrimitiveOperators& operator=(BosonPrimitiveOperators&&) = default;

   private:
    std::shared_ptr<Boson> _boson;
};

inline BosonPrimitiveOperators::BosonPrimitiveOperators(std::shared_ptr<Boson> boson) noexcept
    : _boson(boson) {
    assert(boson);
}

inline std::shared_ptr<Boson> BosonPrimitiveOperators::boson() const {
    return _boson;
}

}  // namespace boson_algebra

// **********************************************************
// ***  BosonCreationAnnihilationBase                     ***
// **********************************************************

namespace boson_algebra {

class BosonCreationAnnihilationBase : public BosonPrimitiveOperators {
   protected:
    // ctor:
    BosonCreationAnnihilationBase(std::shared_ptr<Boson>) noexcept;
    // move semantic:
    BosonCreationAnnihilationBase(BosonCreationAnnihilationBase&&) = default;
    BosonCreationAnnihilationBase& operator=(BosonCreationAnnihilationBase&&) = default;
};

inline BosonCreationAnnihilationBase::BosonCreationAnnihilationBase(std::shared_ptr<Boson> boson) noexcept
    : BosonPrimitiveOperators(boson) {
}

}  // namespace boson_algebra

// **********************************************************
// ***  BosonCreationOperator                             ***
// **********************************************************

namespace boson_algebra {

class BosonCreationOperator final : public BosonCreationAnnihilationBase {
   public:
    static ExpressionHandler make(std::shared_ptr<Boson> boson);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    BosonCreationOperator(std::shared_ptr<Boson> boson) noexcept;
    std::unique_ptr<BosonCreationOperator> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline BosonCreationOperator::BosonCreationOperator(std::shared_ptr<Boson> boson) noexcept
    : BosonCreationAnnihilationBase(boson) {
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

}  // namespace boson_algebra

// **********************************************************
// ***  BosonAnnihilationOperator                         ***
// **********************************************************

namespace boson_algebra {

class BosonAnnihilationOperator final : public BosonCreationAnnihilationBase {
   public:
    static ExpressionHandler make(std::shared_ptr<Boson> boson);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    BosonAnnihilationOperator(std::shared_ptr<Boson> boson) noexcept;
    std::unique_ptr<BosonAnnihilationOperator> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline BosonAnnihilationOperator::BosonAnnihilationOperator(std::shared_ptr<Boson> boson) noexcept
    : BosonCreationAnnihilationBase(boson) {
}

inline ExpressionHandler BosonAnnihilationOperator::make(std::shared_ptr<Boson> boson) {
    return ExpressionHandler::make<BosonAnnihilationOperator>(boson);
}

inline std::unique_ptr<BosonAnnihilationOperator> BosonAnnihilationOperator::casted_clone() const {
    return std::unique_ptr<BosonAnnihilationOperator>(new BosonAnnihilationOperator(boson()));
}

inline ExpressionHandler BosonAnnihilationOperator::clone() const {
    return ExpressionHandler::make<BosonAnnihilationOperator>(boson());
}

inline bool BosonAnnihilationOperator::equals(const Expression& other) const {
    const auto casted_other = dynamic_cast<const BosonAnnihilationOperator*>(&other);
    return (casted_other ? boson()->equals(*casted_other->boson()) : false);
}

inline std::string BosonAnnihilationOperator::str() const {
    return "♭" + boson()->str();
}

inline std::string BosonAnnihilationOperator::repr() const {
    return "BosonAnnihilationOperator(" + boson()->repr() + ")";
}

}  // namespace boson_algebra

// **********************************************************
// ***  BosonNumberOperator                               ***
// **********************************************************

namespace boson_algebra {

class BosonNumberOperator final : public BosonPrimitiveOperators {
   public:
    static ExpressionHandler make(std::shared_ptr<Boson> boson);
    ExpressionHandler clone() const override;
    bool equals(const Expression&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    BosonNumberOperator(std::shared_ptr<Boson> boson) noexcept;
    std::unique_ptr<BosonNumberOperator> casted_clone() const;
    template <class ExpressionClass, class... Args>
    friend boson_algebra::ExpressionHandler boson_algebra::ExpressionHandler::make(Args&&...);
};

inline BosonNumberOperator::BosonNumberOperator(std::shared_ptr<Boson> boson) noexcept
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

}  // namespace boson_algebra

#endif
