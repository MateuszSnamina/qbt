#ifndef BOSON_ALGEBRA_UTIL_STR_REPR_HPP
#define BOSON_ALGEBRA_UTIL_STR_REPR_HPP

#include <string>

// **********************************************************
// ***  StrRepr                                           ***
// **********************************************************

namespace boson_algebra {
namespace util {

class StrRepr {
   public:
    virtual std::string str() const = 0;
    virtual std::string repr() const = 0;
    virtual ~StrRepr() = default;
};

}  // namespace util
}  // namespace boson_algebra

#endif