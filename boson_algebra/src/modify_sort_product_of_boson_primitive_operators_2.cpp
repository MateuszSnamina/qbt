// MY HEADER:
#include <boson_algebra/modify_sort_product_of_boson_primitive_operators_2.hpp>
// SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/adjacent_find.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/irange.hpp>
#include <boost/range/sub_range.hpp>
// STD:
//#include <iterator>

namespace {

enum class CrAn {
    Cr,
    An
};

// std::ostream& operator<<(std::ostream& s, const CrAn& _) {
//     switch (_) {
//         case CrAn::Cr:
//             s << "Cr";
//             break;
//         case CrAn::An:
//             s << "An";
//             break;
//         default:
//             s << "??";
//             break;
//     }
//     return s;
// }

CrAn expression_to_cr_an(const boson_algebra::ExpressionHandler& expression) {
    if (expression.is_of_type<boson_algebra::BosonCreationOperator>()) {
        return CrAn::Cr;
    }
    if (expression.is_of_type<boson_algebra::BosonAnnihilationOperator>()) {
        return CrAn::An;
    }
    assert(0);
}

class DesiredStateCalculator {
   public:
    DesiredStateCalculator(std::size_t n_cr, std::size_t n_an);
    CrAn operator()(std::size_t idx) const;
    std::size_t n_cr() const {
        return _n_cr;
    }
    std::size_t n_an() const {
        return _n_an;
    }
    std::size_t n_all() const {
        return _n_an + _n_cr;
    }

   private:
    std::size_t _n_cr;
    std::size_t _n_an;
    std::size_t _n_min;
    std::size_t _n_chink_1;
    std::size_t _n_chink_2;
    std::size_t _n_chink_3;
};

DesiredStateCalculator::DesiredStateCalculator(std::size_t n_cr, std::size_t n_an)
    : _n_cr(n_cr),
      _n_an(n_an),
      _n_min(std::min(n_cr, n_an)),
      _n_chink_1(n_cr - _n_min),
      _n_chink_2(2 * _n_min),
      _n_chink_3(n_an - _n_min) {
}

CrAn DesiredStateCalculator::operator()(std::size_t idx) const {
    assert(idx < _n_cr + _n_an);
    // std::cout << "CALCULATOR idx: " << idx << std::endl;
    if (idx < _n_chink_1) {
        // std::cout << "CALCULATOR inside CHUNK1" << std::endl;
        return CrAn::Cr;
    } else if (_n_chink_1 + _n_chink_2 <= idx) {
        // std::cout << "CALCULATOR inside CHUNK3" << std::endl;
        return CrAn::An;
    } else {
        // std::cout << "CALCULATOR inside CHUNK2" << std::endl;
        unsigned subchunk_ind = idx - _n_chink_1;
        return (subchunk_ind % 2 == 0 ? CrAn::Cr : CrAn::An);
    }
}

}  // namespace

namespace boson_algebra {

ModificationResult modify_sort_product_of_boson_primitive_operators_2(ExpressionHandler&& expression) {
    const auto& range = expression.crange();
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // ***************************************************************
    if (!expression.is_of_type<ProductExpression>()) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** the transformation does apply to product expressions     **
    // *** with zero factors or only one factor                     **
    // ***************************************************************
    if (expression.n_subexpressions() < 2) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    };
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** with factors being of BosonCreationAnnihilationBase type **
    // ***************************************************************
    const auto is_creation_operator_or_anihillation_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonCreationAnnihilationBase>();
    };
    if (!boost::algorithm::all_of(range, is_creation_operator_or_anihillation_operator)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** the transformation applies only to product expressions   **
    // *** of operators associated with the only one boson          **
    // ***************************************************************
    const auto have_different_bosons = [](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
        const auto boson1 = expression1.casted_target<BosonCreationAnnihilationBase>().unwrap().get().boson();
        const auto boson2 = expression2.casted_target<BosonCreationAnnihilationBase>().unwrap().get().boson();
        return boson1->id() != boson2->id();
    };
    if (boost::adjacent_find(range, have_different_bosons) != boost::end(range)) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    // ***************************************************************
    // *** count number of creation operator factors and            **
    // *** count number of annihilation operator factors            **
    // ***************************************************************
    const auto is_anihillation_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonAnnihilationOperator>();
    };
    const auto is_creation_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonCreationOperator>();
    };
    const unsigned n_cr = boost::count_if(range, is_creation_operator);
    const unsigned n_an = boost::count_if(range, is_anihillation_operator);
    assert(n_cr + n_an == expression.n_subexpressions());
    // ***************************************************************
    // *** construct a helper calculator instance                   **
    // *** defining the operators order in the desired product      **
    // ***************************************************************
    const DesiredStateCalculator desired_state_calculator{n_cr, n_an};
    // ***************************************************************
    // *** find the first not-matching operator                     **
    // *** (not matching to the desired operators order)            **
    // ***************************************************************
    const auto find_index_of_first_not_matching_subexpression =
        [&range, &desired_state_calculator]() -> std::optional<std::size_t> {
        const auto n_all = desired_state_calculator.n_all();
        const auto cobined_range = boost::combine(
            boost::irange(static_cast<std::size_t>(0u), n_all - 1),
            boost::irange(static_cast<std::size_t>(0u), n_all - 1) | boost::adaptors::transformed(desired_state_calculator),
            range | boost::adaptors::sliced(0, n_all - 1));
        for (const auto& _ : cobined_range) {
            const auto index = _.get<0>();
            const auto desired_cr_an = _.get<1>();
            const auto& expression = _.get<2>();
            const auto found_cr_an = expression_to_cr_an(expression);
            if (found_cr_an != desired_cr_an) {
                return index;
            }
        }
        return std::nullopt;
    };
    const auto index_of_first_not_matching_subexpression_optional = find_index_of_first_not_matching_subexpression();
    // ***************************************************************
    // *** the transformation applies only to product               **
    // *** different than the desired product                       **
    // ***************************************************************
    if (!index_of_first_not_matching_subexpression_optional) {
        return ModificationResult::make_passed_through_result(std::move(expression));
    }
    const auto index_of_first_not_matching_subexpression = *index_of_first_not_matching_subexpression_optional;
    assert(index_of_first_not_matching_subexpression < expression.n_subexpressions());
    assert(index_of_first_not_matching_subexpression != expression.n_subexpressions() - 1);
    // ***************************************************************
    // **** find the first adjecent operator pair                   **
    // **** (the operators pair from the transformed product)       **
    // **** to transpose                                            **
    // **** (so to make the procuct more like the desired one)      **
    // ***************************************************************
    const auto find_index_of_first_operator_pair_to_transpose =
        [index_of_first_not_matching_subexpression, &range, &desired_state_calculator]() -> std::size_t {
        const auto n_all = desired_state_calculator.n_all();
        const auto sought_cr_an = desired_state_calculator(index_of_first_not_matching_subexpression);
        const auto cobined_range = boost::combine(
            boost::irange(index_of_first_not_matching_subexpression, n_all - 1),
            range | boost::adaptors::sliced(index_of_first_not_matching_subexpression, n_all - 1),
            range | boost::adaptors::sliced(index_of_first_not_matching_subexpression + 1, n_all));
        for (const auto& _ : cobined_range) {
            const auto index = _.get<0>();
            const auto& expression_l = _.get<1>();
            const auto& expression_r = _.get<2>();
            const auto found_cr_an_l = expression_to_cr_an(expression_l);
            const auto found_cr_an_r = expression_to_cr_an(expression_r);
            if (found_cr_an_r == sought_cr_an) {
                assert(found_cr_an_l != sought_cr_an);
                return index;
            }
        }
        assert(false);
    };
    const auto index_of_first_operator_pair_to_transpose = find_index_of_first_operator_pair_to_transpose();
    assert(index_of_first_operator_pair_to_transpose < expression.n_subexpressions());
    assert(index_of_first_operator_pair_to_transpose != expression.n_subexpressions() - 1);
    // ***************************************************************
    // ***** make the two new subexpressions                        **
    // ***************************************************************
    const auto make_new_subexpression_1 = [&expression, &index_of_first_operator_pair_to_transpose]() -> ExpressionHandler {
        using ConstExpressionHandlerSinglePassSubRange = boost::sub_range<ConstExpressionHandlerSinglePassRange>;
        const auto& range = expression.crange();
        const auto& range_begin = boost::begin(range);
        const auto& range_end = boost::end(range);
        const ConstExpressionHandlerSinglePassSubRange sub_range_1(range_begin, range_begin + index_of_first_operator_pair_to_transpose);
        const ConstExpressionHandlerSinglePassSubRange sub_range_2(range_begin + index_of_first_operator_pair_to_transpose + 2, range_end);
        ExpressionHandlerVector new_subsubexpressions;
        for (const auto& subexpression : sub_range_1) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subsubexpressions.push_back(expression.subexpression(index_of_first_operator_pair_to_transpose + 1).clone());
        new_subsubexpressions.push_back(expression.subexpression(index_of_first_operator_pair_to_transpose).clone());
        for (const auto& subexpression : sub_range_2) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        return ProductExpression::make_from_buffer(std::move(new_subsubexpressions));
    };
    const auto make_new_subexpression_2 = [&expression, &index_of_first_operator_pair_to_transpose]() -> ExpressionHandler {
        using ConstExpressionHandlerSinglePassSubRange = boost::sub_range<ConstExpressionHandlerSinglePassRange>;
        const auto& range = expression.crange();
        const auto& range_begin = boost::begin(range);
        const auto& range_end = boost::end(range);
        const ConstExpressionHandlerSinglePassSubRange sub_range_1(range_begin, range_begin + index_of_first_operator_pair_to_transpose);
        const ConstExpressionHandlerSinglePassSubRange sub_range_2(range_begin + index_of_first_operator_pair_to_transpose + 2, range_end);
        ExpressionHandlerVector new_subsubexpressions;
        for (const auto& subexpression : sub_range_1) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subsubexpressions.push_back(ProductExpression::make_identity());
        for (const auto& subexpression : sub_range_2) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        return ProductExpression::make_from_buffer(std::move(new_subsubexpressions));
    };
    ExpressionHandler new_subexpression_1 = make_new_subexpression_1();
    ExpressionHandler new_subexpression_2 = make_new_subexpression_2();
    // ***************************************************************
    // *** if needed add minus sign in front of                     **
    // *** the new subexpression with unity operator                **
    // ***************************************************************
    const auto is_modify_an_cr_to_cr_an = [index_of_first_not_matching_subexpression, &desired_state_calculator]() -> bool {
        const auto sought_cr_an = desired_state_calculator(index_of_first_not_matching_subexpression);
        // There are two possoible mathematical cases:
        // Case1: ♯◦♭ => ♭◦♯ - 𝕀
        // Case2: ♭◦♯ => ♯◦♭ + 𝕀
        // The cases may be identified by sought_cr_an:
        // Case1: is if and only if sought_cr_an == CrAn::An
        // Case2: is if and only if sought_cr_an == CrAn::Cr
        return (sought_cr_an == CrAn::An);
    };
    if (is_modify_an_cr_to_cr_an()) {  //TODO logic
        new_subexpression_2 = IntegerFactoredExpression::make(-1, std::move(new_subexpression_2));
    }
    // ***************************************************************
    // *** return the composed expression                           **
    // ***************************************************************
    auto new_sum = SumExpression::make(std::move(new_subexpression_1), std::move(new_subexpression_2));
    return ModificationResult::make_generated_result(std::move(new_sum));
}

}  // namespace boson_algebra
