//MY HEADER:
#include <boson_algebra/transform_sort_product_of_boson_primitive_operators_2.hpp>
//SELF:
#include <boson_algebra/expression_boson_primitive_operators.hpp>
#include <boson_algebra/expression_structural_blocks.hpp>
// BOOST:
#include <boost/algorithm/cxx11/all_of.hpp>
// #include <boost/range/adaptors.hpp>
#include <boost/range/adaptor/indexed.hpp>
// #include <boost/range/algorithm/transform.hpp>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/count_if.hpp>
#include <boost/range/combine.hpp>
#include <boost/range/irange.hpp>
//#include<boost/compute/algorithm/adjacent_find.hpp> //TODO??
#include <boost/range/algorithm/adjacent_find.hpp>  //TODO??
// #include <boost/range/algorithm/equal_range.hpp>
// #include <boost/range/algorithm/equal.hpp>
#include <boost/range/sub_range.hpp>

//STD
#include <iostream>  // TODO remove
#include <iterator>

namespace {

enum class CrAn {
    Cr,
    An
};

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
    DesiredStateCalculator(unsigned n_cr, unsigned n_an);
    CrAn operator()(unsigned idx) const;
    unsigned n_cr() const {
        return _n_cr;
    }
    unsigned n_an() const {
        return _n_an;
    }
    unsigned n_all() const {
        return _n_an + _n_cr;
    }

   private:
    unsigned _n_cr;
    unsigned _n_an;
    unsigned _n_min;
    unsigned _n_chink_1;
    unsigned _n_chink_2;
    unsigned _n_chink_3;
};

DesiredStateCalculator::DesiredStateCalculator(unsigned n_cr, unsigned n_an)
    : _n_cr(n_cr),
      _n_an(n_an),
      _n_min(std::min(n_cr, n_an)),
      _n_chink_1(n_cr - _n_min),
      _n_chink_2(2 * _n_min),
      _n_chink_3(n_an - _n_min) {
}

CrAn DesiredStateCalculator::operator()(unsigned idx) const {
    assert(idx < _n_cr + _n_an);
    if (idx < _n_chink_1) {
        return CrAn::Cr;
    } else if (_n_chink_1 + _n_chink_2 <= idx) {
        return CrAn::An;
    } else {
        unsigned subchunk_ind = idx - _n_chink_1;
        return (subchunk_ind % 2 == 0 ? CrAn::Cr : CrAn::An);
    }
}

}  // namespace

namespace boson_algebra {

ExpressionHandlerOptional transform_sort_product_of_boson_primitive_operators_2(const ExpressionHandler& expression) {
    if (!expression.is_of_type<ProductExpression>()) {
        return std::nullopt;
    }
    const auto& range = expression.crange();
    if (!boost::algorithm::all_of(range, [](const ExpressionHandler& _) { return _.is_of_type<BosonCreationAnnihilationBase>(); })) {
        return std::nullopt;
    }
    const auto have_different_bosons = [](const ExpressionHandler& expression1, const ExpressionHandler& expression2) {
        const auto boson1 = expression1.casted_target<BosonCreationAnnihilationBase>().boson();
        const auto boson2 = expression2.casted_target<BosonCreationAnnihilationBase>().boson();
        return boson1->id() != boson2->id();
    };
    if (boost::adjacent_find(range, have_different_bosons) != boost::end(range)) {
        //std::cout << "FOUND DIFFERENT" << std::endl;
        //std::cout << boost::adjacent_find(range, have_different_bosons) - boost::begin(range) << std::endl;
        return std::nullopt;
    }
    const auto is_anihillation_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonAnnihilationOperator>();
    };
    const auto is_creation_operator = [](const ExpressionHandler& expression) {
        return expression.is_of_type<BosonCreationOperator>();
    };
    const unsigned n_cr = boost::count_if(range, is_anihillation_operator);
    const unsigned n_an = boost::count_if(range, is_creation_operator);
    assert(n_cr + n_an == expression.n_subexpressions());

    const DesiredStateCalculator desired_state_calculator{n_cr, n_an};
    // std::cout << "n_cr , n_an = " << n_cr << " " << n_an << std::endl;

    // ***************************************************************
    // ****** handle cases with zero one one subexpressions **********
    // ***************************************************************

    // TODO handle desired_state_calculator.n_all()<2 case!!

    // ***************************************************************
    // ******* find the first adjecent operator pair to transpose ****
    // ***************************************************************

    const auto find_index_of_first_not_matching_subexpression =
        [](const ConstExpressionHandlerRandomAccessRange& range, const DesiredStateCalculator& desired_state_calculator) -> std::optional<std::size_t> {
        const auto n_all = desired_state_calculator.n_all();
        const auto cobined_range = boost::combine(
            boost::irange(0u, n_all - 1),
            boost::irange(0u, n_all) | boost::adaptors::transformed(desired_state_calculator),
            range | boost::adaptors::sliced(0, n_all - 1),
            range | boost::adaptors::sliced(1, n_all));
        for (const auto& _ : cobined_range) {
            //const auto& [index, desired_cr_an, expression] = _;
            const auto index = _.get<0>();
            const auto desired_cr_an = _.get<1>();
            const auto& expression_l = _.get<2>();
            const auto& expression_r = _.get<3>();
            const auto found_cr_an_l = expression_to_cr_an(expression_l);
            const auto found_cr_an_r = expression_to_cr_an(expression_r);
            //std::cout << "index=" << index << std::endl;
            // if (desired_cr_an == CrAn::An) {
            //     std::cout << "desired AN" << std::endl;
            // }
            // if (desired_cr_an == CrAn::Cr) {
            //     std::cout << "desired CR" << std::endl;
            // }
            // if (found_cr_an == CrAn::An) {
            //     std::cout << "found AN" << std::endl;
            // }
            // if (found_cr_an == CrAn::Cr) {
            //     std::cout << "found CR" << std::endl;
            // }
            if (found_cr_an_l != desired_cr_an) {
                return index;
            }
        }
        return std::nullopt;
    };
    const auto index_of_first_not_matching_subexpression =
        find_index_of_first_not_matching_subexpression(range, desired_state_calculator);
    if (!index_of_first_not_matching_subexpression) {
        return std::nullopt;
    }
    // ***************************************************************
    // ******** make the two new subexpressions **********************
    // ***************************************************************
    const auto make_new_subexpression_1 = [&expression, &index_of_first_not_matching_subexpression]() -> ExpressionHandler {
        using ConstExpressionHandlerSinglePassSubRange = boost::sub_range<ConstExpressionHandlerSinglePassRange>;
        const auto& range = expression.crange();
        const auto& range_begin = boost::begin(range);
        const auto& range_end = boost::end(range);
        const ConstExpressionHandlerSinglePassSubRange sub_range_1(range_begin, range_begin + *index_of_first_not_matching_subexpression);
        const ConstExpressionHandlerSinglePassSubRange sub_range_2(range_begin + *index_of_first_not_matching_subexpression + 2, range_end);
        ExpressionHandlerVector new_subsubexpressions;
        for (const auto& subexpression : sub_range_1) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subsubexpressions.push_back(expression.subexpression(*index_of_first_not_matching_subexpression + 1).clone());
        new_subsubexpressions.push_back(expression.subexpression(*index_of_first_not_matching_subexpression).clone());
        for (const auto& subexpression : sub_range_2) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        return SumExpression::make(std::move(new_subsubexpressions));
    };
    const auto make_new_subexpression_2 = [&expression, &index_of_first_not_matching_subexpression]() -> ExpressionHandler {
        using ConstExpressionHandlerSinglePassSubRange = boost::sub_range<ConstExpressionHandlerSinglePassRange>;
        const auto& range = expression.crange();
        const auto& range_begin = boost::begin(range);
        const auto& range_end = boost::end(range);
        const ConstExpressionHandlerSinglePassSubRange sub_range_1(range_begin, range_begin + *index_of_first_not_matching_subexpression);
        const ConstExpressionHandlerSinglePassSubRange sub_range_2(range_begin + *index_of_first_not_matching_subexpression + 2, range_end);
        ExpressionHandlerVector new_subsubexpressions;
        for (const auto& subexpression : sub_range_1) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        new_subsubexpressions.push_back(ProductExpression::make_identity());
        for (const auto& subexpression : sub_range_2) {
            new_subsubexpressions.push_back(subexpression.clone());
        }
        return SumExpression::make(std::move(new_subsubexpressions));
    };
    ExpressionHandler new_subexpression_1 = make_new_subexpression_1();
    ExpressionHandler new_subexpression_2 = make_new_subexpression_2();
    // ***************************************************************
    // ************* add minus sign **********************************
    // ***************************************************************
    if (true) {  //TODO logic
        new_subexpression_2 = IntegerFactoredExpression::make(-1, std::move(new_subexpression_2));
    }
    // ***************************************************************
    // ************* retun the composed expression *******************
    // ***************************************************************
    return SumExpression::make(std::move(new_subexpression_1), std::move(new_subexpression_2));
}

}  // namespace boson_algebra
