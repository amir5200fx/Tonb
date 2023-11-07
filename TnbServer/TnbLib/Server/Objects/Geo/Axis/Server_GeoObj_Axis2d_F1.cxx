#include <Server_GeoObj_Axis2d_F1.hxx>

#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_File.hxx>
#include <Geo_Serialization.hxx>
#include <json.hpp>

#include <gp_Ax2d.hxx>

const std::string tnbLib::Server_GeoObj_Axis2d_F1::Params::centre = "centre";
const std::string tnbLib::Server_GeoObj_Axis2d_F1::Params::dir = "dir";

void tnbLib::Server_GeoObj_Axis2d_F1::Construct(const std::string& theValue)
{
	Pnt2d centre;
	Dir2d dir;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		// loading the value of centre:
		{
			loadTnbServerObject(centre);
		}
		// loading the value of direction:
		{
			loadTnbServerObject(dir);
		}
	}
	// streaming the value
	auto value = gp_Ax2d(centre, dir);
	streamGoodTnbServerObject(value);
}
