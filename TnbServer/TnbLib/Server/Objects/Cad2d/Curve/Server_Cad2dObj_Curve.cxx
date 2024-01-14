#include <Server_Cad2dObj_Curve.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

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

implementTnbServerParam(Server_Cad2dObj_Curve_D1, curve, "curve");
implementTnbServerParam(Server_Cad2dObj_Curve_D1, u, "u");

implementTnbServerConstruction(Server_Cad2dObj_Curve_D1)
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
		const auto& g = curve->Curve();
		auto [pt, value] = g->D1(u);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}