
//SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>

namespace boson_algebra {

extern const std::vector<std::shared_ptr<boson_algebra::CharBoson>> char_bosons;

namespace literals {

std::shared_ptr<CharBoson> operator"" _b(char ch);
ExpressionHandler operator"" _cr(char ch);
ExpressionHandler operator"" _an(char ch);
ExpressionHandler operator"" _no(char ch);

}  // namespace literals

namespace operators {

ExpressionHandler operator*(long long, ExpressionHandler&&);
ExpressionHandler operator*(ExpressionHandler&&, ExpressionHandler&&);
ExpressionHandler operator+(ExpressionHandler&&, ExpressionHandler&&);

}  // namespace operators

}  // namespace boson_algebra
