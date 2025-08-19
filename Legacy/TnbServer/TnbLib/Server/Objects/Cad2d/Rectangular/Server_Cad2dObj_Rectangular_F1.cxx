#include <Server_Cad2dObj_Rectangular_F1.hxx>

#include <Cad2d_Plane.hxx>
#include <Geo_Serialization.hxx>
#include <Pnt2d.hxx>
#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Rectangular_F1::Params::axis("axis");
const std::string tnbLib::Server_Cad2dObj_Rectangular_F1::Params::height("height");
const std::string tnbLib::Server_Cad2dObj_Rectangular_F1::Params::length("length");
const std::string tnbLib::Server_Cad2dObj_Rectangular_F1::Params::name("name");

void tnbLib::Server_Cad2dObj_Rectangular_F1::Construct(const std::string& theValue)
{
	gp_Ax2d axis;
	double height = 0;
	double length = 0;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(axis);
		}
		{
			loadTnbServerObject(height);
		}
		{
			loadTnbServerObject(length);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	try
	{
		auto value = Cad2d_Plane::MakeBox(axis, length, height);
		value->SetName(name);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Cad2dObj_Rectangular_F1::MakeEmpty()
{
	std::shared_ptr<Cad2d_Plane> value;
	streamGoodTnbServerObject(value);
}
