#include <Geo3d_PatchCloud_TriSamplesLev0.hxx>

#include <Pnt2d.hxx>

std::vector<tnbLib::Pnt2d> 
tnbLib::Geo3d_PatchCloud_TriSamplesLev0::CalcSamples
(
	const Pnt2d & theP0,
	const Pnt2d & theP1, 
	const Pnt2d & theP2
) const
{
	static const Standard_Real C3 = 1.0 / 3.0;
	const auto xm = C3 * (theP0.X() + theP1.X() + theP2.X());
	const auto ym = C3 * (theP0.Y() + theP1.Y() + theP2.Y());
	Pnt2d pm(xm, ym);
	std::vector<Pnt2d> samples;
	samples.push_back(std::move(pm));
	return std::move(samples);
}