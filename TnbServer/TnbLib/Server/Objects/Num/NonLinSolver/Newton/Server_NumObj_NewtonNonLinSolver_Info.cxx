#include <Server_NumObj_NewtonNonLinSolver_Info.hxx>

#include <NumAlg_NewtonSolver_Info.hxx>
#include <json.hpp>

const std::string tnbLib::Server_NumObj_NewtonNonLinSolver_Info::Params::tol = "tol";
const std::string tnbLib::Server_NumObj_NewtonNonLinSolver_Info::Params::small = "small";
const std::string tnbLib::Server_NumObj_NewtonNonLinSolver_Info::Params::zero = "zero";
const std::string tnbLib::Server_NumObj_NewtonNonLinSolver_Info::Params::ur = "ur";
const std::string tnbLib::Server_NumObj_NewtonNonLinSolver_Info::Params::max_nb_iters = "max_nb_iters";

void tnbLib::Server_NumObj_NewtonNonLinSolver_Info::Construct(const std::string& theValue)
{
	double tol = 0;
	double small = 0;
	double zero = 0;
	double ur = 0;
	int max_nb_iters = 0;
	{
		defineTnbServerParser(theValue);
		// loading the value of tol.
		{
			loadTnbServerObject(tol);
		}
		// loading the value of small.
		{
			loadTnbServerObject(small);
		}
		// loading the value of zero.
		{
			loadTnbServerObject(zero);
		}
		// loading the value of ur.
		{
			loadTnbServerObject(ur);
		}
		// loading the value of max_nb_iters.
		{
			loadTnbServerObject(max_nb_iters);
		}
	}
	// streaming the value
	auto value = std::make_shared<NumAlg_NewtonSolver_Info>();
	value->SetTolerance(tol);
	value->SetMaxIterations(max_nb_iters);
	value->SetSmall(small);
	value->SetUnderRelaxation(ur);
	value->SetZero(zero);
	streamGoodTnbServerObject(value);
}
