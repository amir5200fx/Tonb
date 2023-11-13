#include <Server_GeoObj_Dir3d.hxx>

#include <Dir3d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Dir3d::Params::u = "geo_dir_u_3d";
const std::string tnbLib::Server_GeoObj_Dir3d::Params::v = "geo_dir_v_3d";
const std::string tnbLib::Server_GeoObj_Dir3d::Params::w = "geo_dir_w_3d";

void tnbLib::Server_GeoObj_Dir3d::Construct(const std::string& theValue)
{
	double u = 0, v = 0, w = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of u:
		{
			std::stringstream stream;
			stream << loader.at(Params::u).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> u;
		}
		// loading the value of v:
		{
			std::stringstream stream;
			stream << loader.at(Params::v).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> v;
		}
		// loading the value of w:
		{
			std::stringstream stream;
			stream << loader.at(Params::w).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> w;
		}
	}
	// streaming the value
	nlohmann::json jData;
	try
	{
		std::stringstream stream;
		auto value = Dir3d(u, v, w);
		TNB_oARCH_FILE_TYPE oa(stream);
		oa << value;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = stream.str();
	}
	catch (Standard_Failure& x)
	{
		jData[SENSE] = GetRespType(RespType::bad);
		jData[VALUE] = x.GetMessageString();
	}
	theStream_ << jData;
}