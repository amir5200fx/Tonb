#include <Server_Cad2dObj_Circle_F1.hxx>

#include <Global_File.hxx>
#include <Geo_Serialization.hxx>
#include <Cad2d_Plane.hxx>

#include <gp_Ax2d.hxx>
#include <gp_Circ2d.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Circle_F1::Params::axis = "axis";
const std::string tnbLib::Server_Cad2dObj_Circle_F1::Params::radius = "radius";
const std::string tnbLib::Server_Cad2dObj_Circle_F1::Params::name = "name";

void tnbLib::Server_Cad2dObj_Circle_F1::Construct(const std::string& theValue)
{
	gp_Ax2d axis;
	double radius = 0;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(axis);
		}
		{
			loadTnbServerObject(radius);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	// stream the value
	try
	{
		gp_Circ2d g(axis, radius);
		auto value = Cad2d_Plane::MakeCircle(g);
		value->SetName(name);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Cad2dObj_Circle_F1::MakeEmpty()
{
	std::shared_ptr<Cad2d_Plane> value;
	streamGoodTnbServerObject(value);
}
