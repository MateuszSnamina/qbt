#ifndef BOSON_ALGEBRA_ALGORITHM_HPP
#define BOSON_ALGEBRA_ALGORITHM_HPP

// SELF:
#include <boson_algebra/expression_abstract.hpp>

//*************************************************************************
//*** ModificationMode, ModificationResult                              ***
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

}  // namespace boson_algebra

//*************************************************************************
//*** ModyficationFunctionT, modify_in_place                            ***
//*************************************************************************

namespace boson_algebra {

using UnsafeTransformFunctionT = std::function<ModificationResult(ExpressionHandler&&)>;
bool modify_in_place(ExpressionHandler& expression, UnsafeTransformFunctionT fun);

}  // namespace boson_algebra

//*************************************************************************
//*** GreedinessLevel, dfs_transform                                    ***
//*************************************************************************

namespace boson_algebra {

enum class GreedinessLevel {
    DoNotTouchReplacedExpressions,
    RepeatForReplacedExpressions,
    DoDfsForReplacedExpressions,
};

unsigned safe_dfs_transform_new_api(
    ExpressionHandler& expression,
    const UnsafeTransformFunctionT& fun,
    GreedinessLevel greediness = GreedinessLevel::DoNotTouchReplacedExpressions);

}  // namespace boson_algebra

#endif
