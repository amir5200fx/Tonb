#include <Server_Cad2dObj_Interpl_F1.hxx>

#include <Pln_CurveTools.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Standard_Failure.hxx>

#include <json.hpp>
#include <Pln_Curve.hxx>

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
			//loadTnbServerObject(pnt_list);
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::pnt_list).get<std::string>());

			// Check if the parsed JSON is an array
			if (json_array.is_array()) {
				// Access elements of the array
				for (const auto& element : json_array) {
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					Pnt2d item;
					ia >> item;
					pnt_list.emplace_back(std::move(item));
				}
			}
			else {
				throw Server_Error("Couldn't load the point list");
			}
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
		edge->Curve()->SetName(name);
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
