#include "Server_AdaptIntegInfoObj.hxx"

#include "../../../Server.hxx"

#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <json.hpp>

const std::string tnbLib::Server_AdaptIntegInfoObj::Params::tol = "adapt_integ_tol";
const std::string tnbLib::Server_AdaptIntegInfoObj::Params::max_nb_iters = "adapt_integ_max_nb_iters";
const std::string tnbLib::Server_AdaptIntegInfoObj::Params::min_nb_iters = "adapt_integ_min_nb_iters";

void tnbLib::Server_AdaptIntegInfoObj::Construct(const std::string& theValue)
{
	double tol = 0;
	int max_nb_iters = 0;
	int min_nb_iters = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of tol.
		{
			std::stringstream stream;
			stream << loader.at(Params::tol).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> tol;
		}
		// loading the value of max_nb_iters
		{
			std::stringstream stream;
			stream << loader.at(Params::max_nb_iters).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> max_nb_iters;
		}
		// loading the value of min_nb_iters
		{
			std::stringstream stream;
			stream << loader.at(Params::min_nb_iters).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> min_nb_iters;
		}
	}
	// streaming the value
	std::stringstream stream;
	nlohmann::json jData;
	auto value = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	value->SetTolerance(tol);
	value->SetMaxNbIterations(max_nb_iters);
	value->SetNbInitIterations(min_nb_iters);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
