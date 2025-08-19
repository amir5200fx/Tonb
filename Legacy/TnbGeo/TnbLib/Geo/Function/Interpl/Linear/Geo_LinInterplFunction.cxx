#include <Geo_LinInterplFunction.hxx>

#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Geo_LinInterplFunction::nbSamples = 2;

Standard_Integer 
tnbLib::Geo_LinInterplFunction::NbSamples() const
{
	return nbSamples;
}

Standard_Real 
tnbLib::Geo_LinInterplFunction::Value(const Standard_Real x) const
{
	return Geo_Tools::Interpolate(x, X0(), X1());
}

std::pair<Standard_Real, Standard_Real> 
tnbLib::Geo_LinInterplFunction::Sample
(
	const Standard_Integer theIndex
) const
{
	Debug_Bad_Index(theIndex, 0, NbSamples() - 1);
	return (&theX0_)[theIndex];
}

std::vector<std::pair<Standard_Real, Standard_Real>> 
tnbLib::Geo_LinInterplFunction::RetrieveSamples() const
{
	std::vector<std::pair<Standard_Real, Standard_Real>> samples;
	samples.reserve(2);

	samples.push_back(X0());
	samples.push_back(X1());
	return std::move(samples);
}