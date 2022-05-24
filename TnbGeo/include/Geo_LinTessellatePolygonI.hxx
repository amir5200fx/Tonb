#pragma once
#include <Entity_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class Point>
inline void tnbLib::Geo_LinTessellatePolygon<Point>::Tessellate
(
	const Standard_Integer nbLevels
)
{
	if (NOT this->Polygon())
	{
		FatalErrorIn(FunctionSIG)
			<< "no polygon has been loaded!" << endl
			<< abort(FatalError);
	}
	const auto nbSeg = (Standard_Integer)std::pow(2.0, (double)nbLevels);
	const auto du = (1.0) / (Standard_Real)nbSeg;

	const auto nbSeg0 = this->Polygon()->NbPoints() - 1;
	const auto nbInners = nbSeg - 1;

	std::vector<Point> pts;
	pts.reserve(nbSeg0*nbInners + nbSeg0 + 1);
	for (size_t i = 1; i <= nbSeg0; i++)
	{
		const auto& p0 = this->Polygon()->GetPoint(i - 1);
		const auto& p1 = this->Polygon()->GetPoint(i);

		pts.push_back(p0);

		auto inners = CalcInners(p0, p1, du, nbSeg);
		for (auto& x : inners)
		{
			pts.push_back(std::move(x));
		}
	}
	pts.push_back(this->Polygon()->LastPoint());

	auto poly = std::make_shared<Entity_Polygon<Point>>(std::move(pts), 0);
	this->TessellatedRef() = std::move(poly);

	this->Change_IsDone() = Standard_True;
}

template<class Point>
inline std::vector<Point> 
tnbLib::Geo_LinTessellatePolygon<Point>::CalcInners
(
	const Point & theP0,
	const Point & theP1, 
	const Standard_Real du,
	const Standard_Integer n
)
{
	std::vector<Point> pts;
	pts.reserve(n - 1);
	for (size_t i = 1; i < n; i++)
	{
		auto pt = theP0 + (theP1 - theP0)*du*(Standard_Real)i;
		pts.push_back(std::move(pt));
	}
	return std::move(pts);
}