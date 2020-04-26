#ifndef BOSON_ALGEBRA_BOSON_HPP
#define BOSON_ALGEBRA_BOSON_HPP

#include <boson_algebra/util_id.hpp>

// ##########################################################
// ###########  Boson                   #####################
// ##########################################################

// **********************************************************
// ***  Boson                                             ***
// **********************************************************

namespace boson_algebra {

class Boson : public IdClass, public StrRepr {
   public:
    virtual bool equals(const Boson&) const = 0;
    virtual ~Boson() = default;
};

}  // namespace boson_algebra

// **********************************************************
// ***  CharBoson                                         ***
// **********************************************************

namespace boson_algebra {

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
    return id() == other.id();
}

inline std::string CharBoson::str() const {
    return std::string(1, _c);
}

inline std::string CharBoson::repr() const {
    return std::string("B[") + _c + std::string("]");
}

}  // namespace boson_algebra


#endif
