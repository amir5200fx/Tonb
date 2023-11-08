#include <Server_Cad2dObj_Area_F1.hxx>

#include <Server_Error.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Edge.hxx>
#include <TnbError.hxx>
#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_Area_F1::Params::curve_list = "curve_list";
const std::string tnbLib::Server_Cad2dObj_Area_F1::Params::name = "name";

void tnbLib::Server_Cad2dObj_Area_F1::Construct(const std::string& theValue)
{
	std::vector<std::shared_ptr<Pln_Edge>> curve_list;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve_list);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	if (curve_list.empty())
	{
		std::shared_ptr<Cad2d_Plane> value;
		streamWarningTnbServerObject(value, "the curve list was empty.");
		return;
	}
	const auto modeler = std::make_shared<Cad2d_Modeler>();
	modeler->Import(curve_list);

	try
	{
		Cad2d_Modeler::selctList l;
		modeler->SelectAll(l);
		modeler->MakePlanes(l);

		if (modeler->NbPlanes() > 1)
		{
			throw Server_Error("no multiple planes construction is permitted!");
		}
		if (!modeler->NbPlanes())
		{
			throw Server_Error("no plane has been created.");
		}
		auto value = modeler->Planes().begin()->second;
		value->SetName(name);
		streamGoodTnbServerObject(value);
	}
	catch (error& x)
	{
		streamBadTnbServerObject(x.message());
	}
	catch (Standard_Failure& x)
	{
		streamBadTnbServerObject(x.GetMessageString());
	}
	catch (Server_Error& x)
	{
		streamBadTnbServerObject(x.what());
	}
	streamUnknownBadTnbServerObject()
}

void tnbLib::Server_Cad2dObj_Area_F1::MakeEmpty()
{
	std::shared_ptr<Cad2d_Plane> value;
	streamGoodTnbServerObject(value);
}
