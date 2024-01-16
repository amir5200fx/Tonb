#include <Server_Cad2dObj_Curve.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <json.hpp>

void tnbLib::Server_Cad2dObj_Curve_ExportToPlt::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> edge;
	{
		std::stringstream stream;
		stream << theValue;
		TNB_iARCH_FILE_TYPE ia(stream);
		ia >> edge;
	}
	try
	{
		if (!edge)
		{
			throw Server_Error("the curve object is null");
		}
		std::stringstream str;
		edge->ExportToPlt(str);
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = str.str();
		theStream_ << jData;
	}
	catchTnbServerErrors()
}

#include <Pln_Tools.hxx>

implementTnbServerParam(Server_Cad2dObj_Curve_Trim, curve, "curve");
implementTnbServerParam(Server_Cad2dObj_Curve_Trim, u0, "u0");
implementTnbServerParam(Server_Cad2dObj_Curve_Trim, u1, "u1");
implementTnbServerParam(Server_Cad2dObj_Curve_Trim, name, "name");

implementTnbServerConstruction(Server_Cad2dObj_Curve_Trim)
{
	std::shared_ptr<Pln_Edge> curve;
	double u0;
	double u1;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(u0);
		}
		{
			loadTnbServerObject(u1);
		}
		{
			loadTnbServerString(name);
		}
	}
	try
	{
		if (!curve)
		{
			throw Server_Error("the curve object is null.");
		}
		auto geom = Pln_Tools::ConvertToTrimmedCurve(curve->Curve()->Geometry(), u0, u1);
		auto value = Pln_Tools::MakeEdge(geom);
		value->SetName(name);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Cad2dObj_Curve_SetName, curve, "curve");
implementTnbServerParam(Server_Cad2dObj_Curve_SetName, name, "name");

implementTnbServerConstruction(Server_Cad2dObj_Curve_SetName)
{
	std::shared_ptr<Pln_Edge> curve;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerString(name);
		}
	}
	try
	{
		if (!curve)
		{
			throw Server_Error("the curve object is null.");
		}
		curve->SetName(name);
		curve->Curve()->SetName(name);
		streamGoodTnbServerObject(curve);
	}
	catchTnbServerErrors()
}

implementTnbServerConstruction(Server_Cad2dObj_Curve_GetIdent)
{
	std::shared_ptr<Pln_Edge> curve;
	{
		loadNonJSONTnbServer(curve);
	}
	try
	{
		if (!curve)
		{
			throw Server_Error("the curve object is null.");
		}
		std::vector<std::string> idents;
		idents.emplace_back(std::to_string(curve->Index()));
		idents.emplace_back(curve->Name());
		nlohmann::json jData;
		jData[SENSE] = GetRespType(RespType::good);
		jData[VALUE] = idents;
		theStream_ << jData;
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Cad2dObj_Curve_CalcTangt, curve, "curve");
implementTnbServerParam(Server_Cad2dObj_Curve_CalcTangt, u, "u");

implementTnbServerConstruction(Server_Cad2dObj_Curve_CalcTangt)
{
	std::shared_ptr<Pln_Edge> curve;
	double u;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			loadTnbServerObject(u);
		}
	}
	try
	{
		if (!curve)
		{
			throw Server_Error("the curve object is null.");
		}
		auto [pt, t] = curve->Curve()->D1(u);
		streamGoodTnbServerObject(t);
	}
	catchTnbServerErrors()
}

implementTnbServerParam(Server_Cad2dObj_Nurbs, pnts, "pnts");
implementTnbServerParam(Server_Cad2dObj_Nurbs, weights, "weights");
implementTnbServerParam(Server_Cad2dObj_Nurbs, knots, "knots");
implementTnbServerParam(Server_Cad2dObj_Nurbs, deg, "deg");
implementTnbServerParam(Server_Cad2dObj_Nurbs, periodic, "periodic");
implementTnbServerParam(Server_Cad2dObj_Nurbs, name, "name");

implementTnbServerConstruction(Server_Cad2dObj_Nurbs)
{
	std::vector<Pnt2d> pnts;
	std::vector<double> weights;
	std::vector<double> knots;
	int deg;
	bool periodic = false;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(pnts);
		}
		{
			//loadTnbServerObject(pnt_list);
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::pnts).get<std::string>());

			// Check if the parsed JSON is an array
			if (json_array.is_array()) {
				// Access elements of the array
				for (const auto& element : json_array) {
					std::stringstream stream;
					stream << element.get<std::string>();
					TNB_iARCH_FILE_TYPE ia(stream);
					Pnt2d item;
					ia >> item;
					pnts.emplace_back(std::move(item));
				}
			}
			else {
				throw Server_Error("Couldn't load the point list");
			}
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::weights).get<std::string>());

			// Check if the parsed JSON is an array
			if (json_array.is_array()) {
				// Access elements of the array
				for (const auto& element : json_array) {
					weights.emplace_back(element.get<double>());
				}
			}
			else {
				throw Server_Error("Couldn't load the weight list");
			}
		}
		{
			nlohmann::json json_array = nlohmann::json::parse(loader.at(Params::knots).get<std::string>());

			// Check if the parsed JSON is an array
			if (json_array.is_array()) {
				// Access elements of the array
				for (const auto& element : json_array) {
					knots.emplace_back(element.get<double>());
				}
			}
			else {
				throw Server_Error("Couldn't load the knot list");
			}
		}
		{
			loadTnbServerObject(deg);
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
		auto g = Pln_Tools::MakeNurbs(pnts, weights, knots, deg, periodic);
		auto edge = Pln_Tools::MakeEdge(g);
		edge->SetName(name);
		edge->Curve()->SetName(name);
		streamGoodTnbServerObject(edge);
	}
	catchTnbServerErrors()
}