//MY HEADER:
#include <boson_algebra/expression_pragma.hpp>
//STD:
#include <vector>

namespace {

using BosonVector = std::vector<std::shared_ptr<boson_algebra::CharBoson>>;
BosonVector prepare_char_bosons_vector() {
    BosonVector result;
    result.reserve('z' - 'a' + 1);
    for (char c = 'a'; c <= 'z'; c++) {
        boson_algebra::CharBoson::make(c);
        result.push_back(boson_algebra::CharBoson::make(c));
    }
    return result;
}

}  // namespace

namespace boson_algebra {

extern const BosonVector char_bosons = prepare_char_bosons_vector();

namespace literals {

std::shared_ptr<CharBoson> operator"" _b(char ch) {
    assert('a' <= ch);
    assert(ch <= 'z');
    return char_bosons[ch - 'a'];
}

ExpressionHandler operator"" _cr(char ch) {
    const auto& boson = char_bosons[ch - 'a'];
    return BosonCreationOperator::make(boson);
}

ExpressionHandler operator"" _an(char ch) {
    const auto& boson = char_bosons[ch - 'a'];
    return BosonAnnihilationOperator::make(boson);
}

ExpressionHandler operator"" _no(char ch) {
    const auto& boson = char_bosons[ch - 'a'];
    return BosonNumberOperator::make(boson);
}

}  // namespace literals

namespace operators {
ExpressionHandler operator*(long long factor, ExpressionHandler&& expr) {
    return std::move(IntegerFactoredExpression::make(factor, std::move(expr)));
}

ExpressionHandler operator*(ExpressionHandler&& expr1, ExpressionHandler&& expr2) {
    return std::move(ProductExpression::make(expr1, expr2));
}

ExpressionHandler operator+(ExpressionHandler&& expr1, ExpressionHandler&& expr2) {
    return std::move(SumExpression::make(expr1, expr2));
}

}  // namespace operators

}  // namespace boson_algebra