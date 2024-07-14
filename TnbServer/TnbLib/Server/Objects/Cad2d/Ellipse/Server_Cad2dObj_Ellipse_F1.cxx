#include <Server_Cad2dObj_Ellipse_F1.hxx>

#include <Global_Done.hxx>
#include <Geo_Serialization.hxx>
#include <Cad2d_Plane.hxx>

#include <gp_Ax2d.hxx>
#include <gp_Elips2d.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Ellipse_F1::Params::axis = "axis";
const std::string tnbLib::Server_Cad2dObj_Ellipse_F1::Params::major = "major";
const std::string tnbLib::Server_Cad2dObj_Ellipse_F1::Params::minor = "minor";
const std::string tnbLib::Server_Cad2dObj_Ellipse_F1::Params::name = "name";

void tnbLib::Server_Cad2dObj_Ellipse_F1::Construct(const std::string& theValue)
{
	gp_Ax2d axis;
	double major;
	double minor;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(axis);
		}
		{
			loadTnbServerObject(major);
		}
		{
			loadTnbServerObject(minor);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	try
	{
		gp_Elips2d g(axis, major, minor);
		auto value = Cad2d_Plane::MakeEllipse(g);
		value->SetName(name);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}
