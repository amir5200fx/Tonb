#include <Geo_LinSamplingFunction.hxx>

#include <Geo_LinInterplFunction.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<Standard_Integer> 
tnbLib::Geo_LinSamplingFunction::Samples
(
	const Standard_Real x,
	const std::vector<Standard_Real>& theValues
) const
{
	std::vector<Standard_Integer> samples;
	samples.reserve(2);

#ifdef _DEBUG
	Global_Tools::CheckSorted(theValues, FunctionSIG);

	if (NOT INSIDE(x, FirstItem(theValues), LastItem(theValues)))
	{
		FatalErrorIn(FunctionSIG)
			<< " the value of x exceeds the span of the vector" << endl
			<< " - x: " << x << endl
			<< " - lower: " << FirstItem(theValues) << endl
			<< " - upper: " << LastItem(theValues) << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	const auto span = Global_Tools::FindSpan(x, theValues);

	samples.push_back(span);
	samples.push_back(span + 1);

	return std::move(samples);
}

Standard_Real 
tnbLib::Geo_LinSamplingFunction::Interpolate
(
	const Standard_Real x,
	const std::vector<std::pair<Standard_Real, Standard_Real>>& theValues
) const
{
	if (theValues.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "Unmatched between vector size and type of interpolation has been detected!" << endl
			<< abort(FatalError);
	}

	auto alg = std::make_shared<Geo_LinInterplFunction>(theValues[0], theValues[1]);
	return alg->Value(x);
}