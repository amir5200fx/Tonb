#include <Server_Cad2dObj_LastParCurve.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

#include <json.hpp>

void tnbLib::Server_Cad2dObj_LastParCurve::Construct(const std::string& theValue)
{
	std::stringstream stream;
	stream << theValue;
	TNB_iARCH_FILE_TYPE ia(stream);
	std::shared_ptr<Pln_Edge> curve;
	ia >> curve;
	{
		auto value = curve->Curve()->LastParameter();
		streamRealValueTnbServerObject(value);
	}
}
