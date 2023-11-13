#include <Server_Cad2dObj_Segment2d_F1.hxx>

#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Edge.hxx>
#include <Pnt2d.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Segment2d_F1::Params::p0 = "p0";
const std::string tnbLib::Server_Cad2dObj_Segment2d_F1::Params::p1 = "p1";
const std::string tnbLib::Server_Cad2dObj_Segment2d_F1::Params::name = "name";

void tnbLib::Server_Cad2dObj_Segment2d_F1::Construct(const std::string& theValue)
{
	Pnt2d p0;
	Pnt2d p1;
	std::string name;
	{
		nlohmann::json loader = nlohmann::json::parse(theValue);
		{
			loadTnbServerObject(p0);
		}
		{
			loadTnbServerObject(p1);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	try
	{
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		auto value = Pln_Tools::MakeEdge(geom);
		streamGoodTnbServerObject(value);
	}
	catch (Standard_Failure& x)
	{
		streamBadTnbServerObject(x.GetMessageString());
	}
	streamUnknownBadTnbServerObject()
}
