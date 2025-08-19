#include "Server_NewtonSolverInfoObj.hxx"

#include "../../../Server.hxx"

#include <NumAlg_NewtonSolver_Info.hxx>
#include <json.hpp>

const std::string tnbLib::Server_NewtonSolverInfoObj::Params::tol = "newton_solver_tol";
const std::string tnbLib::Server_NewtonSolverInfoObj::Params::small = "newton_solver_delta";
const std::string tnbLib::Server_NewtonSolverInfoObj::Params::zero = "newton_solver_zero";
const std::string tnbLib::Server_NewtonSolverInfoObj::Params::under_relax = "newton_ur_relax";
const std::string tnbLib::Server_NewtonSolverInfoObj::Params::max_nb_iters = "newton_solver_max_nb_iters";


void tnbLib::Server_NewtonSolverInfoObj::Construct(const std::string& theValue)
{
	double tol = 0;
	double small = 0;
	double zero = 0;
	double ur = 0;
	int max_nb_iters = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of tol.
		{
			std::stringstream stream;
			stream << loader.at(Params::tol).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> tol;
		}
		// loading the value of small.
		{
			std::stringstream stream;
			stream << loader.at(Params::small).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> small;
		}
		// loading the value of zero.
		{
			std::stringstream stream;
			stream << loader.at(Params::zero).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> zero;
		}
		// loading the value of ur.
		{
			std::stringstream stream;
			stream << loader.at(Params::under_relax).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> ur;
		}
		// loading the value of max_nb_iters.
		{
			std::stringstream stream;
			stream << loader.at(Params::max_nb_iters).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> max_nb_iters;
		}
	}
	// streaming the value
	std::stringstream stream;
	nlohmann::json jData;
	auto value = std::make_shared<NumAlg_NewtonSolver_Info>();
	value->SetTolerance(tol);
	value->SetMaxIterations(max_nb_iters);
	value->SetSmall(small);
	value->SetUnderRelaxation(ur);
	value->SetZero(zero);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
