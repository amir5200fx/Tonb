#include <Server_GeoObj_Ray2d.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Ray.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>
#include <Global_Serialization.hxx>

#include <json.hpp>

implementTnbServerParam(Server_GeoObj_Ray2d, point, "point");
implementTnbServerParam(Server_GeoObj_Ray2d, dir, "dir");

implementTnbServerConstruction(Server_GeoObj_Ray2d)
{
	Pnt2d point;
	Dir2d dir;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(point);
		}
		{
			loadTnbServerObject(dir);
		}
	}
	try
	{
		auto value = std::make_shared<Entity2d_Ray>(point, dir);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_GeoObj_Ray2d_Int, ray0, "ray0");
implementTnbServerParam(Server_GeoObj_Ray2d_Int, ray1, "ray1");

implementTnbServerConstruction(Server_GeoObj_Ray2d_Int)
{
	std::shared_ptr<Entity2d_Ray> ray0;
	std::shared_ptr<Entity2d_Ray> ray1;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(ray0);
		}
		{
			loadTnbServerObject(ray1);
		}
	}
	try
	{
		auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(*ray0, *ray1);
		nlohmann::json jData;
		{
			std::stringstream stream;
			stream << pt;
			jData["value"] = stream.str();
		}
		jData["u1"] = cond;
		std::stringstream stream;
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