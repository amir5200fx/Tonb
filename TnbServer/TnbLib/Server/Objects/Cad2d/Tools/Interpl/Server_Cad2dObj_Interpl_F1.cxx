#include <Server_Cad2dObj_Interpl_F1.hxx>

#include <Pln_CurveTools.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Standard_Failure.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Interpl_F1::Params::pnt_list = "pnt_list";
const std::string tnbLib::Server_Cad2dObj_Interpl_F1::Params::periodic = "periodic";
const std::string tnbLib::Server_Cad2dObj_Interpl_F1::Params::tol = "tol";
const std::string tnbLib::Server_Cad2dObj_Interpl_F1::Params::name = "name";

void tnbLib::Server_Cad2dObj_Interpl_F1::Construct(const std::string& theValue)
{
	std::vector<Pnt2d> pnt_list;
	int periodic = 0;
	double tol = 0;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(pnt_list);
		}
		{
			loadTnbServerObject(tol);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
		{
			loadTnbServerObject(periodic);
		}
	}
	
	try
	{
		auto geom = Pln_CurveTools::Interpolation(pnt_list, periodic, tol);
		auto edge = Pln_Tools::MakeEdge(geom);
		edge->SetName(name);
		streamGoodTnbServerObject(edge);
	}
	catch (Standard_Failure& x)
	{
		streamBadTnbServerObject(x.GetMessageString());
	}
	catch (...)
	{
		streamBadTnbServerObject("unable to create the segment");
	}
}
