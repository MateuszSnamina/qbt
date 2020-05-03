#ifndef BOSON_ALGEBRA_ALGORITHM_HPP
#define BOSON_ALGEBRA_ALGORITHM_HPP

// SELF:
#include <boson_algebra/expression_abstract.hpp>

//*************************************************************************
//*** GreedinessLevel                                                   ***
//*************************************************************************

namespace boson_algebra {

enum class GreedinessLevel {
    DoNotTouchReplacedExpressions,
    RepeatForReplacedExpressions,
    DoDfsForReplacedExpressions,
};

}

//*************************************************************************
//*** safe_dfs_transform                                                ***
//*************************************************************************

namespace boson_algebra {

using SafeTransformFunctionT = std::function<ExpressionHandlerOptional(const ExpressionHandler&)>;

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

}  // namespace boson_algebra

//*************************************************************************
//*** MODIFICATION -- NEW API                                           ***
//*************************************************************************

namespace boson_algebra {

enum class ModificationMode {
    PassedThroughResult,
    GeneratedResult
};

class ModificationResult {
   public:
    // copy semantic:
    ModificationResult(const ModificationResult&) = delete;
    ModificationResult& operator=(const ModificationResult&) = delete;
    // move semantic:
    ModificationResult(ModificationResult&&) = delete;
    ModificationResult& operator=(ModificationResult&&) = delete;
    // creational model:
    static ModificationResult make_passed_through_result(ExpressionHandler&&);
    static ModificationResult make_generated_result(ExpressionHandler&&);
    // accessors is_passed_through/is_generated_result:
    ModificationMode mode() const;
    bool is_passed_through_result() const;
    bool is_generated_result() const;
    operator bool() const;  // returns true is is_generated_result.
    // move the result:
    const ExpressionHandler& result() const;
    ExpressionHandler result();
    const ExpressionHandler& operator*() const;
    ExpressionHandler operator*();

   private:
    ModificationResult(ModificationMode mode, ExpressionHandler&&) noexcept;
    bool _is_passed_through;
    ModificationMode _mode;
    ExpressionHandler _result;
};

inline ModificationResult::ModificationResult(ModificationMode mode, ExpressionHandler&& result) noexcept
    : _mode(mode),
      _result(std::move(result)) {
}

inline ModificationResult ModificationResult::make_passed_through_result(ExpressionHandler&& result) {
    return ModificationResult(ModificationMode::PassedThroughResult, std::move(result));
}

inline ModificationResult ModificationResult::make_generated_result(ExpressionHandler&& result) {
    return ModificationResult(ModificationMode::GeneratedResult, std::move(result));
}

inline ModificationMode ModificationResult::mode() const {
    return _mode;
}

inline bool ModificationResult::is_passed_through_result() const {
    return _mode == ModificationMode::PassedThroughResult;
}

inline bool ModificationResult::is_generated_result() const {
    return _mode == ModificationMode::GeneratedResult;
}

inline ModificationResult::operator bool() const {
    return is_generated_result();
}

inline const ExpressionHandler& ModificationResult::result() const {
    return _result;
}

inline ExpressionHandler ModificationResult::result() {
    return std::move(_result);
}

inline const ExpressionHandler& ModificationResult::operator*() const {
    return result();
}

inline ExpressionHandler ModificationResult::operator*() {
    return result();
}

}  // namespace boson_algebra

//*************************************************************************
//*** safe_dfs_transform -- new api                                     ***
//*************************************************************************

namespace boson_algebra {

// typedefs for algorithms:
using UnsafeTransformFunctionT = std::function<ModificationResult(ExpressionHandler&&)>;

inline bool modify_in_place(ExpressionHandler& expression, UnsafeTransformFunctionT fun) {
    auto result = fun(std::move(expression));
    expression = std::move(*result);
    return result.is_generated_result();
}

inline unsigned safe_dfs_transform_new_api(
    ExpressionHandler& expression,
    const UnsafeTransformFunctionT& fun,
    GreedinessLevel greediness = GreedinessLevel::DoNotTouchReplacedExpressions) {
    assert(!expression.is_shallow_drained());
    unsigned replacement_counter = 0;
    for (auto& subexpression : expression.range()) {
        replacement_counter += safe_dfs_transform_new_api(subexpression, fun, greediness);
    }
    switch (greediness) {
        case GreedinessLevel::DoNotTouchReplacedExpressions:
            if (modify_in_place(expression, fun)) {
                replacement_counter++;
            }
            break;
        case GreedinessLevel::RepeatForReplacedExpressions:
            while (modify_in_place(expression, fun)) {
                replacement_counter++;
            }
            break;
        case GreedinessLevel::DoDfsForReplacedExpressions:
            if (modify_in_place(expression, fun)) {
                replacement_counter++;
                replacement_counter += safe_dfs_transform_new_api(expression, fun, greediness);
            }
            break;
        default:
            assert(false);
    }
    return replacement_counter;
}

}  // namespace boson_algebra

#endif
