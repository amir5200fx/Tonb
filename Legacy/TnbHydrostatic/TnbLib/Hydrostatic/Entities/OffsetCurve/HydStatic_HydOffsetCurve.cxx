#include <HydStatic_HydOffsetCurve.hxx>

#include <Geo_Tools.hxx>

Standard_Integer 
tnbLib::HydStatic_HydOffsetCurve::NbSpans() const
{
	return (Standard_Integer)Qs().size() - 1;
}

Standard_Integer 
tnbLib::HydStatic_HydOffsetCurve::LowerSpan() const
{
	return Standard_Integer(0);
}

Standard_Integer 
tnbLib::HydStatic_HydOffsetCurve::UpperSpan() const
{
	return NbSpans() - 1;
}

Standard_Integer 
tnbLib::HydStatic_HydOffsetCurve::FindSpan(const Standard_Real x) const
{
	static auto find_span_helper = [](const std::pair<Standard_Real, Standard_Real>& x)
	{
		return x.first;
	};

	if (NOT IsInside(x))
	{
		FatalErrorIn(FunctionSIG)
			<< "the parameter is outside of the span!" << endl
			<< " - x: " << x << endl
			<< " - lower: " << Lower() << endl
			<< " - upper: " << Upper() << endl
			<< abort(FatalError);
	}

	auto span = Geo_Tools::FindSpan<std::pair<Standard_Real, Standard_Real>>(x, Qs(), find_span_helper);
	if (span > UpperSpan())
	{
		span = UpperSpan();
	}
	return span;
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::HydStatic_HydOffsetCurve::Span(const Standard_Integer i) const
{
	CheckSpan(i);

	const auto[x0, y0] = Qs()[i];
	const auto[x1, y1] = Qs()[i + 1];

	auto t = std::make_pair(x0, x1);
	return std::move(t);
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::HydStatic_HydOffsetCurve::SpanValue(const Standard_Integer i) const
{
	CheckSpan(i);

	const auto[x0, y0] = Qs()[i];
	const auto[x1, y1] = Qs()[i + 1];

	auto t = std::make_pair(y0, y1);
	return std::move(t);
}

Standard_Boolean 
tnbLib::HydStatic_HydOffsetCurve::IsInside(const Standard_Real x) const
{
	return (Standard_Boolean)(INSIDE(x, Lower(), Upper()));
}

Standard_Real 
tnbLib::HydStatic_HydOffsetCurve::Lower() const
{
	return FirstItem(Qs()).first;
}

Standard_Real 
tnbLib::HydStatic_HydOffsetCurve::Upper() const
{
	return LastItem(Qs()).first;
}

Standard_Real 
tnbLib::HydStatic_HydOffsetCurve::FirstValue() const
{
	return FirstItem(Qs()).second;
}

Standard_Real 
tnbLib::HydStatic_HydOffsetCurve::LastValue() const
{
	return LastItem(Qs()).second;
}

Standard_Real 
tnbLib::HydStatic_HydOffsetCurve::Value(const Standard_Real x) const
{
	const auto span = FindSpan(x);

	return Geo_Tools::Interpolate(x, Qs()[span], Qs()[span + 1]);
}

Standard_Real 
tnbLib::HydStatic_HydOffsetCurve::Value
(
	const Standard_Integer span,
	const Standard_Real x
) const
{
#ifdef _DEBUG
	CheckSpan(span);
#endif // _DEBUG

	return Geo_Tools::Interpolate(x, Qs()[span], Qs()[span + 1]);
}

void tnbLib::HydStatic_HydOffsetCurve::CheckSpan(const Standard_Integer i) const
{
	if (NOT INSIDE(i, LowerSpan(), UpperSpan()))
	{
		FatalErrorIn(FunctionSIG)
			<< " the index, i, exceeds the span boundaries." << endl
			<< " - i: " << endl
			<< " - lower: " << LowerSpan() << endl
			<< " - upper: " << UpperSpan() << endl
			<< abort(FatalError);
	}
}