// MY_HEADER:
#include <boson_algebra/boson.hpp>

namespace boson_algebra {

CharBoson::CharBoson(char c) : _c(c) {
}

std::unique_ptr<CharBoson> CharBoson::make(char c) {
    return std::unique_ptr<CharBoson>(new CharBoson(c));
}

bool CharBoson::equals(const Boson& other) const {
    return id() == other.id();
}

std::string CharBoson::str() const {
    return std::string(1, _c);
}

std::string CharBoson::repr() const {
    return std::string("B[") + _c + std::string("]");
}

}