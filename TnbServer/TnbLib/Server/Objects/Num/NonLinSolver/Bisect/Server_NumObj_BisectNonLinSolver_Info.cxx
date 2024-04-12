#include <Server_NumObj_BisectNonLinSolver_Info.hxx>

#include <NumAlg_BisectionSolver_Info.hxx>
#include <json.hpp>

const std::string tnbLib::Server_NumObj_BisectNonLinSolver_Info::Params::tol = "tol";
const std::string tnbLib::Server_NumObj_BisectNonLinSolver_Info::Params::delta = "delta";
const std::string tnbLib::Server_NumObj_BisectNonLinSolver_Info::Params::max_nb_iters = "max_nb_iters";

void tnbLib::Server_NumObj_BisectNonLinSolver_Info::Construct(const std::string& theValue)
{
	double tol = 0;
	double delta = 0;
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
		// loading the value of delta.
		{
			std::stringstream stream;
			stream << loader.at(Params::delta).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> delta;
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
	auto value = std::make_shared<NumAlg_BisectionSolver_Info>();
	value->SetTolerance(tol);
	value->SetMaxIterations(max_nb_iters);
	value->SetDelta(delta);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
