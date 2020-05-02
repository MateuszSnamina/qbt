#ifndef BOSON_ALGEBRA_ALGORITHM_HPP
#define BOSON_ALGEBRA_ALGORITHM_HPP

// SELF:
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

enum class Greediness {
    DoNotTouchReplacedExpressions,
    RepeatForReplacedExpressions,
    DoDfsForReplacedExpressions,
};

struct DfsResult {
    ExpressionHandler expression;
    int replacement_counter;
};

DfsResult dfs(ExpressionHandler& expression, const SafeTransformFunctionT&, Greediness greediness) {
    // assert(!is_shallow_drained());
    // for (unsigned n_subexpression = 0; n_subexpression < target().n_subexpressions(); n_subexpression++) {
    //     target().subexpression(n_subexpression).safe_dfs_transform(fun, greedy);
    // }
    // if (greedy) {
    //     while (auto transformation_result = fun(*this)) {
    //         swap(*this, *transformation_result);
    //     }
    // } else {
    //     if (auto transformation_result = fun(*this)) {
    //         swap(*this, *transformation_result);
    //     }
    // }
}

}  // namespace boson_algebra

#endif
