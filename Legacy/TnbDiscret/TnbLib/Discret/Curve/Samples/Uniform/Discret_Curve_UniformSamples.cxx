#include <Discret_Curve_UniformSamples.hxx>

std::vector<Standard_Real> 
tnbLib::Discret_Curve_UniformSamples::CalcXs
(
	const Standard_Real x0,
	const Standard_Real x1
) const
{
	const auto nbSegs = NbSamples() - 1;
	const auto du = (x1 - x0) / (Standard_Real)(nbSegs);
	std::vector<Standard_Real> xs;
	xs.reserve(NbSamples());
	xs.push_back(x0);
	for (size_t i = 1; i < nbSegs; i++)
	{
		auto u = x0 + i * du;
		xs.push_back(u);
	}
	xs.push_back(x1);
	return std::move(xs);
}