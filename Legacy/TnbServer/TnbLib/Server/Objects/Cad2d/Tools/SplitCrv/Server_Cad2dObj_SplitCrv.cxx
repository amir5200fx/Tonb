#include <Server_Cad2dObj_SplitCrv.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <json.hpp>


const std::string tnbLib::Server_Cad2dObj_SplitCrv::Params::curve("curve");
const std::string tnbLib::Server_Cad2dObj_SplitCrv::Params::u("u");

void tnbLib::Server_Cad2dObj_SplitCrv::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	double u = 0;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(u);
		}
	}
	try
	{
		auto [c0, c1] = curve->Curve()->Split(u);
		nlohmann::json jData;
		std::stringstream stream;
		{
			std::stringstream stream;
			TNB_oARCH_FILE_TYPE oa(stream);
			oa << c0;
			jData["c0"] = stream.str();
		}
		{
			std::stringstream stream;
			TNB_oARCH_FILE_TYPE oa(stream);
			oa << c1;
			jData["c1"] = stream.str();
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
