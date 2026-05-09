#include <PtdShapeFit2d_Circle.hxx>

#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Pnt2d.hxx>

#include <Geom2d_Circle.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Ax2d.hxx>

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::PtdShapeFit2d_Circle::RetrieveShape
(
	const std::vector<Standard_Real>& xs
) const
{
	auto [xo, yo, radius] = RetrieveParameters(xs);
	auto centre = Pnt2d(xo.value, yo.value);
	gp_Ax2d ax(centre, Dir());

	gp_Circ2d gcircle(ax, radius.value);
	auto shape = Cad2d_Plane::MakeCircle(gcircle);
	return std::move(shape);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::PtdShapeFit2d_Circle::ExportPlane
(
	const std::vector<Standard_Real>& xs
) const
{
	return RetrieveShape(xs);
}