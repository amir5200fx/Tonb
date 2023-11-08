#include <Server_Cad2dObj_RevCrv.hxx>

#include <Pln_Tools.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

#include <json.hpp>

void tnbLib::Server_Cad2dObj_RevCrv::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	std::string name;
	{
		defineTnbServerParser(theValue);
		{
			loadTnbServerObject(curve);
		}
		{
			name = loader.at(Params::name).get<std::string>();
		}
	}
	try
	{
		const auto& c = curve->Curve();
		c->Reverse();
		auto value = Pln_Tools::MakeEdge(c);
		value->SetName(name);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}

void tnbLib::Server_Cad2dObj_RevCrv::MakeEmpty()
{
	std::shared_ptr<Pln_Edge> value;
	streamGoodTnbServerObject(value);
}
