#include <PtdShapeFit2d_TypedAirfoil.hxx>

#include <PtdShapeFit2d_TypedAirfoil_Offsets.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_BoxTools.hxx>
#include <Pnt2d.hxx>

#include <Geom2d_Circle.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Trsf2d.hxx>

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::PtdShapeFit2d_TypedAirfoil::RetrieveShape
(
	const std::vector<Standard_Real>& xs
) const
{
	if (NOT OffsetPoints())
	{
		FatalErrorIn(FunctionSIG)
			<< "the offset points are not loaded." << endl
			<< abort(FatalError);
	}
	auto [xo, yo, chordLen, alpha] = RetrieveParameters(xs);
	auto c = chordLen.value;
	auto pts = OffsetPoints()->Coords();
	const auto& p0 = pts.at(0);
	const auto& p1 = pts.at(pts.size() - 1);
	if (p0.Distance(p1) > gp::Resolution())
	{
		FatalErrorIn(FunctionSIG)
			<< "the airfoil profile is not closed." << endl
			<< abort(FatalError);
	}
	for (auto& x : pts)
	{
		x *= c;
	}
	{
		gp_Trsf2d trsf;
		trsf.SetTranslation(Pnt2d(0, 0), Pnt2d(xo.value, yo.value));

		for (auto& x : pts)
		{
			x.Transform(trsf);
		}
	}
	{
		gp_Trsf2d trsf;
		trsf.SetRotation(Pnt2d(xo.value, yo.value), alpha.value);

		for (auto& x : pts)
		{
			x.Transform(trsf);
		}
	}
	auto curve = std::make_shared<Pln_Curve>
		(0, OffsetPoints()->Name(), Pln_CurveTools::Interpolation(pts));
	auto plane = Cad2d_Plane::MakePlane
	(Pln_Tools::MakeWire({ std::move(curve) }, 1.0E-6), nullptr);
	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane>
tnbLib::PtdShapeFit2d_TypedAirfoil::ExportPlane
(
	const std::vector<Standard_Real>& xs
) const
{
	return RetrieveShape(xs);
}