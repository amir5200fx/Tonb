#include <HydStatic_rAuCurve.hxx>

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theCurve)
{
	// empty body
}

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	Handle(Geom2d_Curve) && theCurve
)
	: HydStatic_AuCurve(std::move(theCurve))
{
	// empty body
}

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	const Standard_Integer theIndex,
	const word& theName,
	Handle(Geom2d_Curve)&& theCurve
)
	: HydStatic_AuCurve(theIndex, theName, std::move(theCurve))
{
	// empty body
}

tnbLib::HydStatic_rAuCurve::HydStatic_rAuCurve
(
	const Standard_Integer theIndex,
	const word & theName,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theName, theCurve)
{
	// empty body
}

#include <HydStatic_Tools.hxx>
#include <MarineBase_Tools.hxx>

std::shared_ptr<tnbLib::HydStatic_rAuCurve> 
tnbLib::HydStatic_rAuCurve::AuCurve
(
	const std::vector<HydStatic_GzQ>& theQs,
	const hydStcLib::CurveMakerType t
)
{
	const auto offsets = HydStatic_Tools::OffsetsFrom(theQs);
	const auto curve = MarineBase_Tools::Curve(offsets);
	Debug_Null_Pointer(curve);

	auto rAu = hydStcLib::MakeCurve<HydStatic_rAuCurve>(std::move(curve), t);
	Debug_Null_Pointer(rAu);
	return std::move(rAu);
}