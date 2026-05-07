#include "Server_MeshCrvInfoObj.hxx"

#include "../../../Server.hxx"

#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <json.hpp>

const std::string tnbLib::Server_MeshCrvInfoObj::Params::under_relax = "meshcrv_ur";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::max_lev = "meshcrv_maxlev";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::bisect_info = "meshcrv_bisect_info";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::corr_info = "meshcrv_corr_info";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::ignore_non_convg = "meshcrv_ignore_nonconvg";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::overall_integ_info = "meshcrv_overall_integ_info";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::newton_integ_info = "meshcrv_integ_info";
const std::string tnbLib::Server_MeshCrvInfoObj::Params::iter_info = "meshcrv_iter_info";

void tnbLib::Server_MeshCrvInfoObj::Construct(const std::string& theValue)
{
	double ur = 0;
	int max_lev = 0;
	bool sense = true;
	std::shared_ptr<NumAlg_BisectionSolver_Info> bisect_info;
	std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> corr_info;
	std::shared_ptr<NumAlg_AdaptiveInteg_Info> overall_integ_info;
	std::shared_ptr<NumAlg_AdaptiveInteg_Info> integ_info;
	std::shared_ptr<NumAlg_NewtonSolver_Info> iter_info;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of the ur.
		{
			std::stringstream stream;
			stream << loader.at(Params::under_relax).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> ur;
		}
		// loading the value of the max_lev
		{
			std::stringstream stream;
			stream << loader.at(Params::max_lev).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> max_lev;
		}
		// loading the value of the sense
		{
			std::stringstream stream;
			stream << loader.at(Params::ignore_non_convg).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> sense;
		}
		// loading the value of the bisect_info.
		{
			std::stringstream stream;
			stream << loader.at(Params::bisect_info).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> bisect_info;
		}
		// loading the value of the corr_info.
		{
			std::stringstream stream;
			stream << loader.at(Params::corr_info).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> corr_info;
		}
		// loading the value of the integ_info.
		{
			std::stringstream stream;
			stream << loader.at(Params::newton_integ_info).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> integ_info;
		}
		// loading the value of the overall integ_info.
		{
			std::stringstream stream;
			stream << loader.at(Params::overall_integ_info).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> overall_integ_info;
		}
		// loading the value of the inter_info.
		{
			std::stringstream stream;
			stream << loader.at(Params::iter_info).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> iter_info;
		}
	}
	// streaming the value
	std::stringstream stream;
	nlohmann::json jData;
	auto value = std::make_shared<Mesh_Curve_Info>();
	value->SetUnderRelaxation(ur);
	value->SetIgnoreNonConvergency(sense);
	value->SetLengthCalcMaxLevel(max_lev);

	value->OverrideOverallLengthIntgInfo(overall_integ_info);
	value->OverrideNewtonIterInfo(iter_info);
	value->OverrideNewtonIntgInfo(integ_info);
	value->OverrideBisectAlgInfo(bisect_info);
	value->OverrideCorrAlgInfo(corr_info);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}