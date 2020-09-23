#include <Geo_ProfileFun_Linear.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::GeoLib::ProfileFun_Linear::Value
(
	const Standard_Real x
) const
{
	Debug_If_Condition(Upper() <= Lower());
	const auto dx = Upper() - Lower();
	return Value0() + (x - Lower())*(Value1() - Value0()) / dx;
}