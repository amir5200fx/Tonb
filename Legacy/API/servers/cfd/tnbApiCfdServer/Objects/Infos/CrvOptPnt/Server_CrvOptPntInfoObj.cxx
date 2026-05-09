#include "Server_CrvOptPntInfoObj.hxx"

#include "../../../Server.hxx"

#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <json.hpp>

const std::string tnbLib::Server_CrvOptPntInfoObj::Params::tol = "meshcrv_optnode_tol";
const std::string tnbLib::Server_CrvOptPntInfoObj::Params::under_relax = "meshcrv_optnode_ur";
const std::string tnbLib::Server_CrvOptPntInfoObj::Params::max_lev = "meshcrv_optnode_maxlev";


void tnbLib::Server_CrvOptPntInfoObj::Construct(const std::string& theValue)
{
	double tol = 0;
	double ur = 0;
	int max_lev = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of tol.
		{
			std::stringstream stream;
			stream << loader.at(Params::tol).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> tol;
		}
		// loading the value of ur.
		{
			std::stringstream stream;
			stream << loader.at(Params::under_relax).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> ur;
		}
		// loading the value of max_lev
		{
			std::stringstream stream;
			stream << loader.at(Params::max_lev).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> max_lev;
		}
	}
	// streaming the value
	std::stringstream stream;
	nlohmann::json jData;
	auto value = std::make_shared<Mesh_CurveOptmPoint_Correction_Info>();
	value->SetTolerance(tol);
	value->SetMaxLevel(max_lev);
	value->SetUnderRelaxation(ur);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
