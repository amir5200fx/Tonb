#include <Server_Cad2dObj_CalcPntOnCurve.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

#include <json.hpp>

const std::string tnbLib::Server_Cad2dObj_CalcPntOnCurve::Params::curve("curve");
const std::string tnbLib::Server_Cad2dObj_CalcPntOnCurve::Params::u("u");

void tnbLib::Server_Cad2dObj_CalcPntOnCurve::Construct(const std::string& theValue)
{
	std::shared_ptr<Pln_Edge> curve;
	double u = 0;
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
		auto value = curve->Curve()->Value(u);
		streamGoodTnbServerObject(value);
	}
	catchTnbServerErrors()
}
