#include <PtdShapeFit2d_AirfoilLeading_t1.hxx>

#include <AirfoilPx_LeadingCurve_t1.hxx>

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
tnbLib::curveLib::airfoilLib::Leading_t1::RetrieveShape
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
			upperTight,
			upperWeight0,
			upperWeight1,
			upperWeight2,

			lowerMax,
			lowerMaxLoc,
			lowerMaxAngle,
			lowerTight,
			lowerWeight0,
			lowerWeight1,
			lowerWeight2
		]
	= RetrieveParameters(xs);

	auto noseProfile = std::make_shared<tnbLib::profileLib::LeadingCurve_t1>();
	noseProfile->SetXo(xo.value);
	noseProfile->SetYo(yo.value);

	noseProfile->SetNoseAngle(noseAngle.value);

	noseProfile->SetUpperMax(upperMax.value);
	noseProfile->SetUpperMaxLoc(upperMaxLoc.value);
	noseProfile->SetUpperMaxAngle(upperMaxAngle.value);
	noseProfile->SetUpperTight(upperTight.value);
	noseProfile->SetUpperWeight0(upperWeight0.value);
	noseProfile->SetUpperWeight1(upperWeight1.value);
	noseProfile->SetUpperWeight2(upperWeight2.value);

	noseProfile->SetLowerMax(lowerMax.value);
	noseProfile->SetLowerMaxLoc(lowerMaxLoc.value);
	noseProfile->SetLowerMaxAngle(lowerMaxAngle.value);
	noseProfile->SetLowerTight(lowerTight.value);
	noseProfile->SetLowerWeight0(lowerWeight0.value);
	noseProfile->SetLowerWeight1(lowerWeight1.value);
	noseProfile->SetLowerWeight2(lowerWeight2.value);

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
tnbLib::curveLib::airfoilLib::Leading_t1::ExportPlane
(
	const std::vector<Standard_Real>& xs
) const
{
	return RetrieveShape(xs);
}