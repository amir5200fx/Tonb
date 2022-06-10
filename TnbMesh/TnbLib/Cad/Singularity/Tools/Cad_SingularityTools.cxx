#include <Cad_SingularityTools.hxx>

#include <Cad_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Triangulation.hxx>

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

std::shared_ptr<tnbLib::Entity2d_Triangulation> 
tnbLib::Cad_SingularityTools::GetTriangulation
(
	const Entity2d_Box & theBox
)
{
	auto P0 = theBox.P0();
	auto P1 = theBox.Corner(Box2d_PickAlgorithm_SE);
	auto P2 = theBox.P1();
	auto P3 = theBox.Corner(Box2d_PickAlgorithm_NW);

	auto Pm = theBox.CalcCentre();

	auto triangulation = std::make_shared<Entity2d_Triangulation>();
	auto& pts = triangulation->Points();

	pts.reserve(5);
	pts.push_back(std::move(P0));
	pts.push_back(std::move(P1));
	pts.push_back(std::move(P2));
	pts.push_back(std::move(P3));
	pts.push_back(std::move(Pm));

	auto& triangles = triangulation->Connectivity();
	triangles.reserve(4);

	connectivity::triple t0;
	t0.Value(0) = 1;
	t0.Value(1) = 2;
	t0.Value(2) = 5;

	connectivity::triple t1;
	t1.Value(0) = 2;
	t1.Value(1) = 3;
	t1.Value(2) = 5;

	connectivity::triple t2;
	t2.Value(0) = 3;
	t2.Value(1) = 4;
	t2.Value(2) = 5;

	connectivity::triple t3;
	t3.Value(0) = 4;
	t3.Value(1) = 1;
	t3.Value(2) = 5;

	triangles.push_back(std::move(t0));
	triangles.push_back(std::move(t1));
	triangles.push_back(std::move(t2));
	triangles.push_back(std::move(t3));

	return std::move(triangulation);
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