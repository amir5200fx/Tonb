#include <SeriesProps_WagenBTools.hxx>

#include <NumAlg_SteffenInterplFunc.hxx>
#include <Global_Table.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::NumAlg_InterplFunc> 
tnbLib::SeriesProps_WagenBTools::SteffenInterpol
(
	const std::vector<Standard_Real>& rPerR,
	const std::vector<Standard_Real>& xs
)
{
#ifdef _DEBUG
	if (rPerR.size() NOT_EQUAL xs.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid data has been detected!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG
	std::vector<std::pair<Standard_Real, Standard_Real>> qs;
	qs.reserve(rPerR.size());
	for (size_t i = 0; i < rPerR.size(); i++)
	{
		auto x = rPerR.at(i);
		auto y = xs.at(i);
		auto paired = std::make_pair(x, y);
		qs.push_back(std::move(paired));
	}
	auto alg = std::make_shared<NumAlg_SteffenInterplFunc>(std::move(qs));
	Debug_Null_Pointer(alg);

	Debug_If_Condition_Message(NOT alg->IsDone(), "the appliccation is not performed!");
	return std::move(alg);
}

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