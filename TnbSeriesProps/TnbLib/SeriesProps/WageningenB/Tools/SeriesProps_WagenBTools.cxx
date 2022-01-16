#include <SeriesProps_WagenBTools.hxx>

#include <Global_Table.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Real 
tnbLib::SeriesProps_WagenBTools::RetrieveLinearTabValue
(
	const Standard_Real rPerR, 
	const Standard_Real P, 
	const Global_Table & theTable
)
{
	Check(rPerR, P, theTable);

	auto v = Global_Tools::Interpolate(rPerR, P, theTable);
	return v;
}

Standard_Real 
tnbLib::SeriesProps_WagenBTools::Yface
(
	const Standard_Real v1,
	const Standard_Real tMax, 
	const Standard_Real tte, 
	const Standard_Real tle, 
	const Standard_Real p
)
{
	if (p <= 0.0)
	{
		return v1 * (tMax - tte);
	}
	else
	{
		return v1 * (tMax - tle);
	}
}

Standard_Real 
tnbLib::SeriesProps_WagenBTools::Yback
(
	const Standard_Real v1, 
	const Standard_Real v2, 
	const Standard_Real tMax, 
	const Standard_Real tte,
	const Standard_Real tle,
	const Standard_Real p
)
{
	if (p <= 0.0)
	{
		return (v1 + v2)*(tMax - tte) + tte;
	}
	else
	{
		return (v1 + v2)*(tMax - tle) + tle;
	}
}