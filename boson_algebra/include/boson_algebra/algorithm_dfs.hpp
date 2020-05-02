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
    unsigned replacement_counter;
};

unsigned safe_dfs_transform(ExpressionHandler& expression, const SafeTransformFunctionT& fun, Greediness greediness) {
    assert(!expression.is_shallow_drained());
    unsigned replacement_counter = 0;
    for (unsigned n_subexpression = 0; n_subexpression < expression.n_subexpressions(); n_subexpression++) {
        replacement_counter += safe_dfs_transform(expression.subexpression(n_subexpression), fun, greediness);
    }
    switch (greediness) {
        case Greediness::DoNotTouchReplacedExpressions:
            if (auto transformation_result = fun(expression)) {
                swap(expression, *transformation_result);
                replacement_counter++;
            }
            break;
        case Greediness::RepeatForReplacedExpressions:
            while (auto transformation_result = fun(expression)) {
                swap(expression, *transformation_result);
                replacement_counter++;
            }
            break;
        case Greediness::DoDfsForReplacedExpressions:
            //TODO:
            assert(0);
            break;
        default:
            assert(0);
    }
    return replacement_counter;
}

}  // namespace boson_algebra

#endif
