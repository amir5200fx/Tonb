#include <Server_Cad2dObj_FirstParCurve.hxx>

#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>

#include <json.hpp>

void tnbLib::Server_Cad2dObj_FirstParCurve::Construct(const std::string& theValue)
{
	std::stringstream stream;
	stream << theValue;
	TNB_iARCH_FILE_TYPE ia(stream);
	std::shared_ptr<Pln_Edge> curve;
	ia >> curve;
	{
		auto value = curve->Curve()->FirstParameter();
		streamRealValueTnbServerObject(value);
	}
}
