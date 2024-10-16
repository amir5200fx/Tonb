#include <Server_GeoObj_Vec3d.hxx>

#include <Vec3d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Vec3d::Params::u = "geo_vec_u_3d";
const std::string tnbLib::Server_GeoObj_Vec3d::Params::v = "geo_vec_v_3d";
const std::string tnbLib::Server_GeoObj_Vec3d::Params::w = "geo_vec_w_3d";

void tnbLib::Server_GeoObj_Vec3d::Construct(const std::string& theValue)
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
	std::stringstream stream;
	auto value = Vec3d(u, v, w);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
