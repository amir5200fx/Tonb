#include <Server_Cad2dObj_Area_F1.hxx>

#include <Server_Error.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Entity2d_Polygon.hxx>
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
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::curve_list).get<std::string>());

			// Check if the parsed JSON is an array
			if (json_array.is_array()) {
				// Access elements of the array
				for (const auto& element : json_array) {
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					std::shared_ptr<Pln_Edge> edge;
					ia >> edge;
					curve_list.emplace_back(std::move(edge));
				}
			}
			else {
				throw Server_Error("Couldn't load the curve list");
			}
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
	modeler->SetMaxRadius(1.e-6); // this should be available through settings
	try
	{
		Cad2d_Modeler::selctList l;
		modeler->SelectAll(l);
		//Cad2d_Modeler::verbose = 1;
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

void tnbLib::Server_Cad2dObj_Area_ExportToPlt::Construct(const std::string& theValue)
{
	std::shared_ptr<Cad2d_Plane> area;
	{
		loadNonJSONTnbServer(area);
	}
	try
	{
		if (!area)
		{
			throw Server_Error("the area object is null.");
		}
		std::stringstream str;
		area->ExportToPlt(str);
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = str.str();
		theStream_ << jData;
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Cad2dObj_Area_GetCurves::Construct(const std::string& theValue)
{
	std::shared_ptr<Cad2d_Plane> area;
	{
		loadNonJSONTnbServer(area);
	}
	try
	{
		if (!area)
		{
			throw Server_Error("the area object is null.");
		}
		std::vector<std::shared_ptr<Pln_Entity>> entities;
		area->RetrieveSegmentsTo(entities);
		std::sort(entities.begin(), entities.end(),
		          [](const std::shared_ptr<Pln_Entity>& e0, const std::shared_ptr<Pln_Entity>& e1)
		          {
			          return e0->Index() < e1->Index();
		          });
		std::vector<std::string> edges;
		for (const auto& ent: entities)
		{
			auto edge = std::dynamic_pointer_cast<Pln_Edge>(ent);
			std::stringstream stream;
			TNB_oARCH_FILE_TYPE io(stream);
			io << edge;
			edges.emplace_back(stream.str());
		}
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = edges;
		theStream_ << jData;
	}
	catchTnbServerErrors()
}

implementTnbServerConstruction(Server_Cad2dObj_Area_GetOuterPolygon)
{
	std::shared_ptr<Cad2d_Plane> area;
	{
		loadNonJSONTnbServer(area);
	}
	try
	{
		if (!area)
		{
			throw Server_Error("the area object is null.");
		}
		const auto& outer = area->OuterWire();
		auto poly = outer->Polygon();
		streamGoodTnbServerObject(poly);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Cad2dObj_Area_Trsf, trsf, "trsf");
implementTnbServerParam(Server_Cad2dObj_Area_Trsf, area, "area");

implementTnbServerConstruction(Server_Cad2dObj_Area_Trsf)
{
	gp_Trsf2d trsf;
	std::shared_ptr<Cad2d_Plane> area;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(trsf);
		}
		{
			loadTnbServerObject(area);
		}
	}
	try
	{
		if (NOT area)
		{
			throw Server_Error("the area object is null.");
		}
		area->Transform(trsf);
		streamGoodTnbServerObject(area);
	}
	catchTnbServerErrors()
}