#include <MarineRepairSect_TwoEdgeMissSection.hxx>

#include <MarineRepairSect_HoverSegment.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	auto MakeCurve(const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = Pln_CurveTools::MakeSegment(p0, p1);
		Debug_Null_Pointer(geom);

		auto curve = std::make_shared<Pln_Curve>(std::move(geom));
		return std::move(curve);
	}

	auto MakeCurves(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& q0, const Pnt2d& q1)
	{
		std::vector<std::shared_ptr<Pln_Curve>> curves;
		auto c0 = MakeCurve(p0, p1);
		auto c1 = MakeCurve(q0, q1);

		curves.push_back(std::move(c0));
		curves.push_back(std::move(c1));
		return std::move(curves);
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>> 
tnbLib::MarineRepairSect_TwoEdgeMissSection::FillingCurves() const
{
	if (NOT Segment0())
	{
		FatalErrorIn(FunctionSIG)
			<< "segment0 is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Segment1())
	{
		FatalErrorIn(FunctionSIG)
			<< "segment1 is loaded!" << endl
			<< abort(FatalError);
	}

	const auto& seg0 = Segment0()->Segment();
	const auto& seg1 = Segment1()->Segment();

	Debug_Null_Pointer(seg0);
	Debug_Null_Pointer(seg1);

	const auto& n0 = seg0->Node0();
	const auto& n1 = seg0->Node1();

	const auto& n2 = seg1->Node0();
	const auto& n3 = seg1->Node1();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	Debug_Null_Pointer(n3);

	const auto& v0 = n0->Vtx();
	Debug_Null_Pointer(v0);

	const auto& v1 = n1->Vtx();
	Debug_Null_Pointer(v1);

	const auto& q0 = n2->Vtx();
	Debug_Null_Pointer(q0);

	const auto& q1 = n3->Vtx();
	Debug_Null_Pointer(q1);

	if (Geo_Tools::HasIntersection_cgal(v0->Coord(), q0->Coord(), v1->Coord(), q1->Coord()))
	{
		if (Geo_Tools::HasIntersection_cgal(v0->Coord(), q1->Coord(), v1->Coord(), q0->Coord()))
		{
			FatalErrorIn(FunctionSIG)
				<< "degeneracy has been detected: invalid section." << endl
				<< abort(FatalError);
		}

		auto curves = MakeCurves(v0->Coord(), q1->Coord(), v1->Coord(), q0->Coord());
		return std::move(curves);
	}
	else 
	{
		auto curves = MakeCurves(v0->Coord(), q0->Coord(), v1->Coord(), q1->Coord());
		return std::move(curves);
	}
}