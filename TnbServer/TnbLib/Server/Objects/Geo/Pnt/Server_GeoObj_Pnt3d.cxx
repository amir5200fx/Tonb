#include <Server_GeoObj_Pnt3d.hxx>

#include <Pnt3d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Pnt3d::Params::x = "geo_pnt_x_3d";
const std::string tnbLib::Server_GeoObj_Pnt3d::Params::y = "geo_pnt_y_3d";
const std::string tnbLib::Server_GeoObj_Pnt3d::Params::z = "geo_pnt_z_3d";

void tnbLib::Server_GeoObj_Pnt3d::Construct(const std::string& theValue)
{
	//std::cout << "POINT = " << theValue << std::endl;
	double x = 0, y = 0, z = 0;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of x:
		{
			std::stringstream stream;
			stream << loader.at(Params::x).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> x;
		}
		// loading the value of y:
		{
			std::stringstream stream;
			stream << loader.at(Params::y).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> y;
		}
		// loading the value of y:
		{
			std::stringstream stream;
			stream << loader.at(Params::z).get<std::string>();
			TNB_iARCH_FILE_TYPE ia(stream);
			ia >> z;
		}
	}
	// streaming the value
	std::stringstream stream;
	auto value = Pnt3d(x, y, z);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}