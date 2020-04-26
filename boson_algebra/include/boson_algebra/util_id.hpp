#ifndef BOSON_ALGEBRA_UTIL_ID_HPP
#define BOSON_ALGEBRA_UTIL_ID_HPP

namespace boson_algebra {

// **********************************************************
// ***  IdClass                                           ***
// **********************************************************

class IdClass {
   public:
    unsigned long id() const;
    virtual ~IdClass() = default;

   protected:
    IdClass();

   private:
    unsigned long _id;
    static unsigned long _pool_id;
};

inline IdClass::IdClass() : _id(_pool_id++) {
}

inline unsigned long IdClass::id() const {
    return _id;
}

}  // namespace boson_algebra

#endif
