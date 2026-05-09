#include <Server_Cad2dObj_CalcCrvLength.hxx>

#include <Mesh2d_Curve.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <Geo_MetricPrcsr_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_CalcCrvLength::Params::curve("curve");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength::Params::lower("lower");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength::Params::upper("upper");
const std::string tnbLib::Server_Cad2dObj_CalcCrvLength::Params::info("info");

void tnbLib::Server_Cad2dObj_CalcCrvLength::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	double lower = 0;
	double upper = 0;
	std::shared_ptr<Values> info;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(lower);
		}
		{
			loadTnbServerObject(upper);
		}
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(info);
		}
	}
	try
	{
		const auto& g = curve->Curve()->Geometry();
		auto size_fun = std::make_shared<GeoSizeFun2d_Uniform>(1.0, curve->BoundingBox(0));
		auto metric_info = std::make_shared<Geo_MetricPrcsr_Info>(info->integ_info);
		auto metric_prcsr = std::make_shared<Geo2d_MetricPrcsr>(size_fun, metric_info);
		auto mesh_info = std::make_shared<Mesh_Curve_Info>();
		mesh_info->OverrideOverallLengthIntgInfo(info->integ_info);
		mesh_info->SetIgnoreNonConvergency(info->ignore_non_conv);
		mesh_info->SetLengthCalcMaxLevel(info->max_nb_subs);
		auto alg = std::make_shared<Mesh2d_Curve>(g, lower, upper, metric_prcsr, mesh_info);
		auto value = alg->CalcLengthWithChecking(info->max_nb_subs);
		streamRealValueTnbServerObject(value);
	}
	catchTnbServerErrors()
}
