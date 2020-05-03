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

inline unsigned safe_dfs_transform(
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
                replacement_counter++;
                replacement_counter += safe_dfs_transform(expression, fun, greediness);
            }
            break;
        default:
            assert(false);
    }
    return replacement_counter;
}

//*************************************************************************

class ModificationResult {
   public:
    // copy semmantic:
    ModificationResult(const ModificationResult&) = delete;
    ModificationResult& operator=(const ModificationResult&) = delete;
    // move semantic:
    static ModificationResult make_passed_through_result(ExpressionHandler&&);
    static ModificationResult make_generated_result(ExpressionHandler&&);
    bool is_passed_through_result() const {
        return _is_passed_through;
    }
    bool is_generated_result() const {
        return !_is_passed_through;
    }
    operator bool() const {
        return is_generated_result();
    }
    ExpressionHandler result() {
        return std::move(_result);
    }
    ExpressionHandler operator*() {
        return result();
    }

   private:
    ModificationResult(bool is_passed_through, ExpressionHandler&&);
    bool _is_passed_through;
    ExpressionHandler _result;
};

inline ModificationResult::ModificationResult(bool is_passed_through, ExpressionHandler&& result)
    : _is_passed_through(is_passed_through),
      _result(std::move(result)) {
}

inline ModificationResult ModificationResult::make_passed_through_result(ExpressionHandler&& result) {
    return ModificationResult(true, std::move(result));
}

inline ModificationResult ModificationResult::make_generated_result(ExpressionHandler&& result) {
    return ModificationResult(false, std::move(result));
}

}  // namespace boson_algebra

#endif
