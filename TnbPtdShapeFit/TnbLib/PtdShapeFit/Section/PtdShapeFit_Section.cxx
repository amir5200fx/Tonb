#include <PtdShapeFit_Section.hxx>

#include <Pln_Curve.hxx>

#include <Geom2dAPI_ProjectPointOnCurve.hxx>

const std::string tnbLib::PtdShapeFit_Section::extension =
".pshfitsect";

Standard_Real 
tnbLib::PtdShapeFit_Section::CalcDistance
(
	const Pnt2d& thePnt, 
	const Pln_Curve& theCurve
)
{
	Geom2dAPI_ProjectPointOnCurve proj(thePnt, theCurve.Geometry());
	return proj.LowerDistance();
}