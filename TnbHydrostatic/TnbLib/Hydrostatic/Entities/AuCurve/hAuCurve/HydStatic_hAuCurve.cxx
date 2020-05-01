#include <HydStatic_hAuCurve.hxx>

tnbLib::HydStatic_hAuCurve::HydStatic_hAuCurve
(
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theCurve)
{
}

tnbLib::HydStatic_hAuCurve::HydStatic_hAuCurve
(
	const Standard_Integer theIndex,
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theCurve)
{
}

tnbLib::HydStatic_hAuCurve::HydStatic_hAuCurve
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const Handle(Geom2d_Curve)& theCurve
)
	: HydStatic_AuCurve(theIndex, theName, theCurve)
{
}

#include <HydStatic_Tools.hxx>
#include <MarineBase_Tools.hxx>

std::shared_ptr<tnbLib::HydStatic_hAuCurve>
tnbLib::HydStatic_hAuCurve::AuCurve
(
	const std::vector<HydStatic_GzQ>& theQs
)
{
	const auto offsets = HydStatic_Tools::OffsetsFrom(theQs);
	const auto curve = MarineBase_Tools::Curve(offsets);
	Debug_Null_Pointer(curve);

	auto rAu = std::make_shared<HydStatic_hAuCurve>(std::move(curve));
	Debug_Null_Pointer(rAu);
	return std::move(rAu);
}