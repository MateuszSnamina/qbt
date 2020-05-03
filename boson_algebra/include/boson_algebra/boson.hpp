#ifndef BOSON_ALGEBRA_BOSON_HPP
#define BOSON_ALGEBRA_BOSON_HPP

// SELF:
#include <boson_algebra/util_str_repr.hpp>
#include <boson_algebra/util_id.hpp>
// STD:
#include <memory>
#include <string>

// ##########################################################
// ###########  Boson                   #####################
// ##########################################################

// **********************************************************
// ***  Boson                                             ***
// **********************************************************

namespace boson_algebra {

class Boson : public IdClass, public util::StrRepr {
   public:
    virtual bool equals(const Boson&) const = 0;
    virtual ~Boson() = default;

   protected:
    Boson() = default;
};

}  // namespace boson_algebra

// **********************************************************
// ***  CharBoson                                         ***
// **********************************************************

namespace boson_algebra {

class CharBoson final : public Boson {
   public:
    static std::unique_ptr<CharBoson> make(char);
    bool equals(const Boson&) const override;
    std::string str() const override;
    std::string repr() const override;

   private:
    CharBoson(char);
    char _c;
};

}  // namespace boson_algebra

#endif
