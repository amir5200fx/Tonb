#include <Server_GeoObj_Pnt2d.hxx>

#include <Pnt2d.hxx>
#include <json.hpp>

const std::string tnbLib::Server_GeoObj_Pnt2d_SetX::Params::value("value");
const std::string tnbLib::Server_GeoObj_Pnt2d_SetX::Params::point("point");

void tnbLib::Server_GeoObj_Pnt2d_SetX::Construct(const std::string& theValue)
{
	Pnt2d point;
	double value;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(point);
		}
		{
			loadTnbServerObject(value);
		}
	}
	point.SetX(value);
	streamGoodTnbServerObject(point);
}

const std::string tnbLib::Server_GeoObj_Pnt2d_SetY::Params::value("value");
const std::string tnbLib::Server_GeoObj_Pnt2d_SetY::Params::point("point");

void tnbLib::Server_GeoObj_Pnt2d_SetY::Construct(const std::string& theValue)
{
	Pnt2d point;
	double value;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(point);
		}
		{
			loadTnbServerObject(value);
		}
	}
	point.SetY(value);
	streamGoodTnbServerObject(point);
}

implementTnbServerParam(Server_GeoObj_Pnt2d_Trsf, trsf, "trsf");
implementTnbServerParam(Server_GeoObj_Pnt2d_Trsf, pnt, "pnt");

implementTnbServerConstruction(Server_GeoObj_Pnt2d_Trsf)
{
	gp_Trsf2d trsf;
	Pnt2d pnt;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(pnt);
		}
	}
	pnt.Transform(trsf);
	streamGoodTnbServerObject(pnt);
}