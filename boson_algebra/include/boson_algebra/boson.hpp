#ifndef BOSON_ALGEBRA_BOSON_HPP
#define BOSON_ALGEBRA_BOSON_HPP

// SELF:
#include <boson_algebra/util_id.hpp>
#include <boson_algebra/util_str_repr.hpp>
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
    Boson(const Boson&) = delete;
    Boson(Boson&&) = delete;

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
    CharBoson(const CharBoson&) = delete;
    CharBoson(CharBoson&&) = delete;
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