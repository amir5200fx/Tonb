#include <Server_Cad2dObj_PrjPntCrv.hxx>

#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

#include <json.hpp>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <StdFail_NotDone.hxx>

const std::string tnbLib::Server_Cad2dObj_PrjPntCrv::Params::u0("u0");
const std::string tnbLib::Server_Cad2dObj_PrjPntCrv::Params::u1("u1");
const std::string tnbLib::Server_Cad2dObj_PrjPntCrv::Params::curve("curve");
const std::string tnbLib::Server_Cad2dObj_PrjPntCrv::Params::pnt("pnt");

void tnbLib::Server_Cad2dObj_PrjPntCrv::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	Pnt2d pnt;
	double u0 = 0;
	double u1 = 0;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(pnt);
		}
		{
			loadTnbServerObject(u0);
		}
		{
			loadTnbServerObject(u1);
		}
	}
	try
	{
		Geom2dAPI_ProjectPointOnCurve
			alg(pnt, curve->Curve()->Geometry(), u0, u1);
		Pnt2d pt = alg.NearestPoint();
		auto par = alg.LowerDistanceParameter();
		nlohmann::json jData;
		std::stringstream stream;
		{
			std::stringstream stream;
			TNB_oARCH_FILE_TYPE oa(stream);
			oa << pt;
			jData["pt"] = stream.str();
		}
		{
			std::stringstream stream;
			TNB_oARCH_FILE_TYPE oa(stream);
			oa << par;
			jData["par"] = par;
		}
		stream << jData;
		{
			nlohmann::json jData1;
			jData1[SENSE] = GetRespType(RespType::good);
			jData1[VALUE] = stream.str();
			theStream_ << jData1;
		}
	}
	catchTnbServerErrors()
}
