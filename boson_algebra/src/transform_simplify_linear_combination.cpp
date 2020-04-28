//MY HEADER:
#include <boson_algebra/transform_simplify_linear_combination.hpp>
//SELF:
#include <boson_algebra/expression_structural_blocks.hpp>
//BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
//STD:
#include <numeric>

namespace boson_algebra {

ExpressionHandlerOptional transform_simplify_linear_combination(const ExpressionHandler& expression_hdl) {
    if (!expression_hdl.is_of_type<SumExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression_hdl.crange();
    const bool are_all_subexpression_factors =
        boost::algorithm::all_of(range, [](const ExpressionHandler& expression_hdl) {
            return expression_hdl.is_of_type<IntegerFactoredExpression>();
        });
    if (!are_all_subexpression_factors) {
        return std::nullopt;
    }
    std::list<std::size_t> indices(expression_hdl.n_subexpressions());
    std::iota(indices.begin(), indices.end(), 0);
    ExpressionHandlerVector new_subexpressions;
    while (!indices.empty()) {
        const auto processed_idx = indices.front();
        const auto& processed_subexpression_hdl = expression_hdl.subexpression(processed_idx);
        const auto& processed_subsubexpression_hdl = processed_subexpression_hdl.subexpression(0);
        long accumulated_factor = 0l;
        auto it = indices.begin();
        while (it != indices.end()) {
            const auto& subexpression_hdl = expression_hdl.subexpression(*it);
            const auto& subsubexpression_hdl = subexpression_hdl.subexpression(0);
            if (processed_subsubexpression_hdl.equals(subsubexpression_hdl)) {
                accumulated_factor += subexpression_hdl.casted_target<IntegerFactoredExpression>().factor();
                it = indices.erase(it);
            } else {
                it++;
            }
        }
        auto new_subsubexpression = expression_hdl.subexpression(processed_idx).subexpression(0).clone();
        auto new_subexpression = IntegerFactoredExpression::make(accumulated_factor, std::move(new_subsubexpression));
        new_subexpressions.push_back(std::move(new_subexpression));
    }
    return SumExpression::make(std::move(new_subexpressions));
}

}  // namespace boson_algebra