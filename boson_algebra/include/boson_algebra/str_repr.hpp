#ifndef BOSON_ALGEBRA_STR_REPR_HPP
#define BOSON_ALGEBRA_STR_REPR_HPP

#include<string>

// **********************************************************
// ***  StrRepr                                           ***
// **********************************************************

namespace boson_algebra {

class StrRepr {
   public:
    virtual std::string str() const = 0;
    virtual std::string repr() const = 0;
    virtual ~StrRepr() = default;
};

}  // namespace boson_algebra

#endif