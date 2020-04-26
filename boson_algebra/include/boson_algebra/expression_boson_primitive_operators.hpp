#ifndef BOSON_ALGEBRA_EXPRESSION_BOSON_PRIMITIVE_OPERATORS_HPP
#define BOSON_ALGEBRA_EXPRESSION_BOSON_PRIMITIVE_OPERATORS_HPP

#include <boson_algebra/boson.hpp>
#include <boson_algebra/expression_common.hpp>

#define UNUSED(x) (void)x;

// ##########################################################
// ###########  BosonPrimitiveOperators #####################
// ##########################################################

// References:
// (1) list-of-all-unicodes-open-close-brackets:
// https://stackoverflow.com/questions/13535172/list-of-all-unicodes-open-close-brackets

// **********************************************************
// ***  BosonPrimitiveOperators                           ***
// **********************************************************

namespace boson_algebra {

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

}  // namespace boson_algebra

// **********************************************************
// ***  BosonCreationOperator                             ***
// **********************************************************

namespace boson_algebra {

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

}  // namespace boson_algebra

// **********************************************************
// ***  BosonAnihilationOperator                          ***
// **********************************************************

namespace boson_algebra {

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

}  // namespace boson_algebra

#endif