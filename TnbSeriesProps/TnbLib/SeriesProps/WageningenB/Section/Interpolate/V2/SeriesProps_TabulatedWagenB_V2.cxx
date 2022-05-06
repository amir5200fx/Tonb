#include <SeriesProps_TabulatedWagenB_V2.hxx>

#include <SeriesProps_WagenB_TableV2.hxx>
#include <SeriesProps_WagenBTools.hxx>
#include <Geo_InterplFunction.hxx>
#include <Geo_SamplingFunction.hxx>
#include <Geo_TableFunction.hxx>
#include <Global_Tools.hxx>
#include <Global_Table.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::seriesProps::TabulatedWagenB_V2::maxTabulatedRadius = 0.9;

Standard_Real 
tnbLib::seriesProps::TabulatedWagenB_V2::Value
(
	const Standard_Real rPerR,
	const Standard_Real P
) const
{
	if (NOT RadiusFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no radius function has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT PFun())
	{
		FatalErrorIn(FunctionSIG)
			<< "no P function has been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(wagenB::table_v2);
	const auto& table = wagenB::table_v2;

	if (INSIDE(rPerR, MaxTabulatedRadius(), maxRadius))
	{
		auto r = MaxTabulatedRadius();
		return Value(r, P);
	}
	else if (INSIDE(rPerR, minRadius, MaxTabulatedRadius()))
	{
		if (INSIDE(P, minP, maxP))
		{
			auto func = std::make_shared<Geo_TableFunction>(PFun(), RadiusFun());
			Debug_Null_Pointer(func);

			return func->Value(P, rPerR, *wagenB::table_v2);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "the P exceeds the span of the values" << endl
				<< " - P: " << P << endl
				<< " - minP: " << minP << endl
				<< " - maxP: " << maxP << endl
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "the rPerR exceeds the span of the radius" << endl
			<< " - rPerR: " << rPerR << endl
			<< " - minRadius: " << minRadius << endl
			<< " - maxRadius: " << maxRadius << endl
			<< abort(FatalError);
	}
	return 0;
}