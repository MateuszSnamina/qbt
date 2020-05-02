#ifndef BOSON_ALGEBRA_ALGORITHM_HPP
#define BOSON_ALGEBRA_ALGORITHM_HPP

// SELF:
#include <boson_algebra/expression_abstract.hpp>

namespace boson_algebra {

enum class GreedinessLevel {
    DoNotTouchReplacedExpressions,
    RepeatForReplacedExpressions,
    DoDfsForReplacedExpressions,
};

// struct DfsResult {
//     ExpressionHandler expression;
//     unsigned replacement_counter;
// };

unsigned safe_dfs_transform(
    ExpressionHandler& expression,
    const SafeTransformFunctionT& fun,
    GreedinessLevel greediness = GreedinessLevel::DoNotTouchReplacedExpressions) {
    assert(!expression.is_shallow_drained());
    unsigned replacement_counter = 0;
    for (auto& subexpression : expression.range()) {
        replacement_counter += safe_dfs_transform(subexpression, fun, greediness);
    }
    switch (greediness) {
        case GreedinessLevel::DoNotTouchReplacedExpressions:
            if (auto transformation_result = fun(expression)) {
                swap(expression, *transformation_result);
                replacement_counter++;
            }
            break;
        case GreedinessLevel::RepeatForReplacedExpressions:
            while (auto transformation_result = fun(expression)) {
                swap(expression, *transformation_result);
                replacement_counter++;
            }
            break;
        case GreedinessLevel::DoDfsForReplacedExpressions:
            if (auto transformation_result = fun(expression)) {
                swap(expression, *transformation_result);
                replacement_counter += safe_dfs_transform(expression, fun, greediness);
            }
            break;
        default:
            assert(false);
    }
    return replacement_counter;
}

}  // namespace boson_algebra

#endif
