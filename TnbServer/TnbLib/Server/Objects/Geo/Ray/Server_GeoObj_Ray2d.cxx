#include <Server_GeoObj_Ray2d.hxx>

#include <json.hpp>
#include <Entity2d_Ray.hxx>
#include <Pnt2d.hxx>
#include <Geo_Tools.hxx>

implementTnbServerParam(Server_GeoObj_Ray2d, pnt, "pnt");
implementTnbServerParam(Server_GeoObj_Ray2d, vec, "vec");

implementTnbServerConstruction(Server_GeoObj_Ray2d)
{
	Pnt2d pnt;
	Vec2d vec;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(pnt);
		}
		{
			loadTnbServerObject(vec);
		}
	}
	auto value = std::make_shared<Entity2d_Ray>(pnt, vec);
	streamGoodTnbServerObject(value);
}

implementTnbServerParam(Server_GeoObj_Ray2d_Intersect, ray0, "ray0");
implementTnbServerParam(Server_GeoObj_Ray2d_Intersect, ray1, "ray1");

implementTnbServerConstruction(Server_GeoObj_Ray2d_Intersect)
{
	std::shared_ptr<Entity2d_Ray> ray0, ray1;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(ray0);
		}
		{
			loadTnbServerObject(ray1);
		}
	}
	auto [pt, cond] = Geo_Tools::CalcIntersectionPoint_cgal(*ray0, *ray1);
	std::stringstream stream_j;
	{
		nlohmann::json jData;
		{
			std::stringstream stream;
			TNB_oARCH_FILE_TYPE oa(stream);
			oa << pt;
			jData["pt"] = stream.str();
		}
		{
			jData["cond"] = cond;
		}
		stream_j << jData;
	}
	nlohmann::json jData;
	jData[SENSE] = GetRespType(RespType::good);
	jData[VALUE] = stream_j.str();
	theStream_ << jData;
}