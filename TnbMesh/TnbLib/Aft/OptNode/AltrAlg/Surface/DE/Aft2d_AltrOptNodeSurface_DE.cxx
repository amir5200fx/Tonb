#include <Aft2d_AltrOptNodeSurface_DE.hxx>

#include <Aft2d_MetricPrcsrSurface.hxx>
#include <differential_evolution.hpp>
#include <TnbError.hxx>
#include <Osstream.hxx>

double tnbLib::Aft2d_AltrOptNodeSurface_DE::Iter(const std::vector<double>& xs) const
{
	Pnt2d pt(xs.at(0), xs.at(1));

	Debug_Null_Pointer(Front());
	Debug_Null_Pointer(MetricMap());
	Debug_If_Condition(ElmSize() <= gp::Resolution());

	const auto& node0 = Front()->Node0();
	const auto& node1 = Front()->Node1();
	Debug_Null_Pointer(node0);
	Debug_Null_Pointer(node1);

	const auto& v0 = node0->Coord();
	const auto& v1 = node1->Coord();

	const auto d0 = MetricMap()->CalcUnitDistance(v0, pt);
	const auto d1 = MetricMap()->CalcUnitDistance(v1, pt);

	const auto del0 = std::abs(1.0 - d0);
	const auto del1 = std::abs(1.0 - d1);

	static const Standard_Real Pow = 3.0;
	const auto cost0 = d0 * std::pow(1.0 + del0, Pow);
	const auto cost1 = d1 * std::pow(1.0 + del1, Pow);
	return cost0 * cost1;
}

//void tnbLib::Aft2d_AltrOptNodeSurface_DE::Perform()
//{
//	static const size_t nbVars = 2;
//	amichel::de::constraints myConstraints{ nbVars,-1.0E-16,1.0E16 };
//	myConstraints[0] = std::make_shared<amichel::de::real_constraint>(UV0().first, UV1().first);
//	myConstraints[1] = std::make_shared<amichel::de::real_constraint>(UV0().second, UV1().second);
//
//	/**
//	* Instantiate the collection of processors with the number of
//	* parallel processors (4), the objective function and the
//	* listener
//	*/
//	amichel::de::listener_ptr listener(std::make_shared<amichel::de::null_listener>());
//	amichel::de::processor_listener_ptr processor_listener(
//		std::make_shared<amichel::de::null_processor_listener>());
//
//	/**
//	 * Instantiate the collection of processors with the number of
//	 * parallel processors (1), the objective function and the
//	 * listener
//	 */
//	amichel::de::processors _processors{ 1, std::bind(&Iter, this, std::placeholders::_1), processor_listener };
//
//	/**
//	 * Instantiate a simple termination strategy which will stop the
//	 * optimization process after n generations
//	 */
//	amichel::de::termination_strategy terminationStrategy(amichel::de::max_gen_termination_strategy(DEInfo()->GenSize()));
//
//	/**
//	 * Instantiate the selection strategy - we'll use the best of
//	 * parent/child strategy
//	 */
//	amichel::de::selection_strategy selectionStrategy{ amichel::de::best_parent_child_selection_strategy{} };
//
//	/**
//	 * Instantiate the mutation strategy - we'll use the mutation
//	 * strategy 1 with the weight and crossover factors set to 0.5
//	 * and 0.9 respectively
//	 */
//	amichel::de::mutation_strategy_arguments mutation_arguments(DEInfo()->MutWeight(), DEInfo()->MutCross());
//
//	amichel::de::mutation_strategy_ptr mutationStrategy(
//		std::make_shared<amichel::de::mutation_strategy_1>(nbVars, mutation_arguments));
//
//	/**
//	 * Instantiate the differential evolution using the previously
//	 * defined constraints, processors, listener, and the various
//	 * strategies
//	 */
//
//	size_t populationSize = DEInfo()->PopSize();
//
//	auto alg = std::make_shared<amichel::de::differential_evolution>
//		(
//			nbVars,
//			populationSize,
//			_processors,
//			myConstraints,
//			true,
//			terminationStrategy,
//			selectionStrategy,
//			mutationStrategy,
//			listener
//			);
//
//	/**
//	 * Run the optimization process
//	 */
//
//	alg->run();
//
//	/**
//	 * Get the best individual resulted from the optimization
//	 * process
//	 */
//	amichel::de::individual_ptr best(alg->best());
//
//	Pnt2d pt(best->vars().at(0), best->vars().at(1));
//
//	CorrectedRef() = std::move(pt);
//	Change_IsDone() = Standard_True;
//}