#include <Server_GeoObj_Pnt2d.hxx>

#include <Pnt2d.hxx>
#include <Global_File.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Pnt2d::Params::x = "geo_pnt_x_2d";
const std::string tnbLib::Server_GeoObj_Pnt2d::Params::y = "geo_pnt_y_2d";

void tnbLib::Server_GeoObj_Pnt2d::Construct(const std::string& theValue)
{
	//std::cout << "POINT = " << theValue << std::endl;
	double x = 0, y = 0;
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
	}
	// streaming the value
	std::stringstream stream;
	auto value = Pnt2d(x, y);
	TNB_oARCH_FILE_TYPE oa(stream);
	oa << value;
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream.str();
	theStream_ << jData;
}
