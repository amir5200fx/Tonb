#include <Cad_SingularityTools.hxx>

#include <Cad_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>

#include <Geom2d_Curve.hxx>

std::vector<std::shared_ptr<tnbLib::Pln_Curve>>
tnbLib::Cad_SingularityTools::RetrieveSides
(
	const Entity2d_Box & theBox
)
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(4);

	auto c0 = std::make_shared<Pln_Curve>(Pln_CurveTools::MakeSegment(theBox.P0(), theBox.Corner(Box2d_PickAlgorithm_SE)));
	auto c1 = std::make_shared<Pln_Curve>(Pln_CurveTools::MakeSegment(theBox.Corner(Box2d_PickAlgorithm_SE), theBox.P1()));
	auto c2 = std::make_shared<Pln_Curve>(Pln_CurveTools::MakeSegment(theBox.P1(), theBox.Corner(Box2d_PickAlgorithm_NW)));
	auto c3 = std::make_shared<Pln_Curve>(Pln_CurveTools::MakeSegment(theBox.Corner(Box2d_PickAlgorithm_NW), theBox.P0()));
	curves.push_back(std::move(c0));
	curves.push_back(std::move(c1));
	curves.push_back(std::move(c2));
	curves.push_back(std::move(c3));
	return std::move(curves);
}

Handle(Geom2d_Curve) 
tnbLib::Cad_SingularityTools::GetParaCurve
(
	const Pnt2d & theP0,
	const Pnt2d & theP1
)
{
	auto geom = Pln_CurveTools::MakeSegment(theP0, theP1);
	return std::move(geom);
}

Handle(Geom2d_Curve) 
tnbLib::Cad_SingularityTools::GetParaCurve
(
	const std::vector<Pnt2d>& thePts
)
{
	auto geom = Pln_CurveTools::Interpolation(thePts);
	return std::move(geom);
}

tnbLib::Pnt2d 
tnbLib::Cad_SingularityTools::FindParametricCoord
(
	const Entity2d_Polygon & thePoly, 
	const Geom_Surface & theSurface,
	const Standard_Real theLength
)
{
#ifdef _DEBUG
	Entity2d_Polygon::Check(thePoly);
#endif // _DEBUG
	const auto& pts = thePoly.Points();

	Standard_Real d = 0;
	auto p0 = Cad_Tools::CalcCoord(pts.at(0), theSurface);
	for (size_t i = 1; i < pts.size(); i++)
	{
		auto p1 = Cad_Tools::CalcCoord(pts.at(i), theSurface);
		d += Distance(p0, p1);

		if (d >= theLength)
		{
			return MEAN(pts.at(i - 1), pts.at(i));
		}
		p0 = std::move(p1);
	}
	FatalErrorIn(FunctionSIG)
		<< "no coordinates have been found!" << endl
		<< abort(FatalError);
	return pts[0];
}