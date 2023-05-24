#include <PtdShapeFit2d_AirfoilNose_t2.hxx>

#include <AirfoilPx_NoseCurve_t2.hxx>

#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Geo_CosineDistb.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Trsf2d.hxx>
#include <Geom2d_Curve.hxx>

std::shared_ptr<tnbLib::Cad2d_Plane>
tnbLib::curveLib::airfoilLib::Type2::RetrieveShape
(
	const std::vector<Standard_Real>& xs
) const
{
	auto
		[
			xo,
			yo,

			noseAngle,

			upperMax,
			upperMaxLoc,
			upperMaxAngle,
			upperNoseTight,
			upperTight,

			lowerMax,
			lowerMaxLoc,
			lowerMaxAngle,
			lowerNoseTight,
			lowerTight
		]
	= RetrieveParameters(xs);

	auto noseProfile = std::make_shared<tnbLib::profileLib::NoseCurve_t2>();
	noseProfile->SetXo(xo.value);
	noseProfile->SetYo(yo.value);

	noseProfile->SetNoseAngle(noseAngle.value);

	noseProfile->SetUpperMax(upperMax.value);
	noseProfile->SetUpperMaxLoc(upperMaxLoc.value);
	noseProfile->SetUpperMaxLoc(upperMaxAngle.value);
	noseProfile->SetUpperNoseTight(upperNoseTight.value);
	noseProfile->SetUpperMaxTight(upperTight.value);

	noseProfile->SetLowerMax(lowerMax.value);
	noseProfile->SetLowerMaxLoc(lowerMaxLoc.value);
	noseProfile->SetLowerMaxLoc(lowerMaxAngle.value);
	noseProfile->SetLowerNoseTight(lowerNoseTight.value);
	noseProfile->SetLowerMaxTight(lowerTight.value);

	noseProfile->Perform();
	const auto& curve = noseProfile->Surface();
	auto seg = std::make_shared<Pln_Curve>(Pln_CurveTools::MakeSegment(curve->LastCoord(), curve->FirstCoord()));

	std::vector<std::shared_ptr<Pln_Curve>> curves{ curve,seg };
	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane>
tnbLib::curveLib::airfoilLib::Type2::ExportPlane
(
	const std::vector<Standard_Real>& xs
) const
{
	return RetrieveShape(xs);
}