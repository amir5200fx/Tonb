#include <Geo2d_NormalizePts.hxx>

#include <Geo_BoxTools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Geo2d_NormalizePts::Perform()
{
	const auto b = Geo_BoxTools::GetBox(Points(), 0);
	const auto[dx, dy] = b.Length();

	if (dx <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "no area is defined by the domain in x-direction!" << endl
			<< abort(FatalError);
	}

	if (dy <= gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "no area is defined by the domain in y-direction!" << endl
			<< abort(FatalError);
	}

	const auto x0 = b.P0().X();
	const auto y0 = b.P0().Y();

	std::vector<Pnt2d> pts;
	pts.reserve(Points().size());
	for (const auto& p : Points())
	{
		auto x = (p.X() - x0) / dx;
		auto y = (p.Y() - y0) / dy;

		Pnt2d pt(x, y);
		pts.push_back(std::move(pt));
	}
	NormalizedRef() = std::move(pts);
	Change_IsDone() = Standard_True;
}