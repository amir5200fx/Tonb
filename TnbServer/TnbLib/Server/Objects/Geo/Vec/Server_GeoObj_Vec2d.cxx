#include <Server_GeoObj_Vec2d.hxx>

#include <Vec2d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Vec2d::Params::u = "geo_vec_u_2d";
const std::string tnbLib::Server_GeoObj_Vec2d::Params::v = "geo_vec_v_2d";

void tnbLib::Server_GeoObj_Vec2d::Construct(const std::string& theValue)
{
	double u = 0, v = 0;
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
	}
	// streaming the value
	std::stringstream stream;
	auto value = Vec2d(u, v);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
