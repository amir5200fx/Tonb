#include <ISC08_Tools.hxx>

#include <Geo_Tools.hxx>
#include <ISC08_Factor.hxx>
#include <ISC08_Table.hxx>
#include <HydStatic_hArmCurve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom2d_Line.hxx>

std::shared_ptr<tnbLib::HydStatic_hArmCurve> 
tnbLib::ISC08_Tools::HeelingArm
(
	const isc08Lib::Lw & theLw2
)
{
	Handle(Geom2d_Line) line = 
		new Geom2d_Line(gp_Pnt2d(0, theLw2()), gp_Vec2d(1, 0));
	Debug_Null_Pointer(line);

	auto heeling = std::make_shared<HydStatic_hArmCurve>(0, "gust wind heeling arm", line);
	Debug_Null_Pointer(heeling);

	return std::move(heeling);
}

Standard_Boolean 
tnbLib::ISC08_Tools::CheckData
(
	const marineLib::B & B,
	const marineLib::TM & d
)
{
	return NOT B() / d() <= 3.5;
}

Standard_Boolean 
tnbLib::ISC08_Tools::CheckData
(
	const marineLib::KG & KG, 
	const marineLib::TM & d
)
{
	const auto x = KG() / d() - 1.0;
	return NOT INSIDE(x, isc08Lib::min_KG_per_d_minus_1, isc08Lib::max_KG_per_d_minus_1);
}

Standard_Boolean 
tnbLib::ISC08_Tools::CheckData
(
	const isc08Lib::T & T
)
{
	return NOT(T() <= isc08Lib::max_T);
}

Standard_Real 
tnbLib::ISC08_Tools::Factor
(
	const Standard_Real x,
	const isc08Lib::BilgeBarCondition cond
)
{
	switch (cond)
	{
	case isc08Lib::BilgeBarCondition::round_bilged_or_having_no_bilge_or_bar_keels: return 1.0;
	case isc08Lib::BilgeBarCondition::sharp_bilges: return 0.7;
	default:
		const auto v = Table(x, isc08Lib::table2343);
		return v;
	}
}

Standard_Real 
tnbLib::ISC08_Tools::Table
(
	const Standard_Real x,
	const ISC08_Table & theTable
)
{
	const auto& spans = theTable.Spans;
	const auto& values = theTable.Values;

#ifdef DEBUG
	CheckTable(theTable, "Standard_Real ISC08_Tools::Table(Args...)");
#endif // DEBUG

	if (x <= spans[0])
	{
		return values[0];
	}
	if (x >= spans[spans.size() - 1])
	{
		return values[values.size() - 1];
	}

	const auto span = Geo_Tools::FindSpan(x, spans);

	const auto x0 = spans[span - 1];
	const auto x1 = spans[span];

	const auto y0 = values[span - 1];
	const auto y1 = values[span];

	return y0 + (y1 - y0)*(x - x0) / (x1 - x0);
}

void tnbLib::ISC08_Tools::CheckTable
(
	const ISC08_Table & theTable,
	const word & theName
)
{
	const auto& spans = theTable.Spans;
	const auto& values = theTable.Values;

	if (spans.size() NOT_EQUAL values.size())
	{
		FatalErrorIn(theName)
			<< "Invalid Table" << endl
			<< abort(FatalError);
	}
}

