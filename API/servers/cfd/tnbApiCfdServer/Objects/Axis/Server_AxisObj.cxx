#include "Server_AxisObj.hxx"

#include "../../Server.hxx"

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_File.hxx>
#include <Global_Serialization.hxx>
#include <OpenCascade_Serialization.hxx>
#include <json.hpp>

#include "gp_Ax2d.hxx"

const std::string tnbLib::Server_AxisObj::Params::centre = "centre";
const std::string tnbLib::Server_AxisObj::Params::dir = "dir";

void tnbLib::Server_AxisObj::Construct(const std::string& theValue)
{
	Pnt2d centre;
	Dir2d dir;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of x:
		{
			std::stringstream stream;
			stream << loader.at(Params::centre).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> centre;
		}
		// loading the value of y:
		{
			std::stringstream stream;
			stream << loader.at(Params::dir).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> dir;
		}
	}
	// streaming the value
	std::stringstream stream;
	auto value = gp_Ax2d(centre, dir);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
