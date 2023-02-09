#include <Pln_GapCurve.hxx>

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Pln_GapCurve::CreateCurve
(
	const Standard_Integer theIndex,
	const word& theName,
	const Handle(Geom2d_Curve)& theGeom
) const
{
	auto curve = std::make_shared<Pln_GapCurve>(theIndex, theName, theGeom);
	return std::move(curve);
}