#include <PtdShapeFit2d_AirfoilGlobal_t1.hxx>

#include <AirfoilPx_GlobalCurve_t1.hxx>

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
tnbLib::curveLib::airfoilLib::Global_t1::RetrieveShape
(
	const std::vector<Standard_Real>& xs
) const
{
	auto
		[
			xo,
			yo,

			noseAngle,

			chordLen,

			upperMax,
			upperMaxLoc,
			upperNoseTight,
			upperMaxTight,
			upperTrailAngle,
			upperMaxVel,
			upperTrailVel,

			lowerMax,
			lowerMaxLoc,
			lowerNoseTight,
			lowerMaxTight,
			lowerTrailAngle,
			lowerMaxVel,
			lowerTrailVel
		]
	= RetrieveParameters(xs);

	/*std::cout << xo.name << ", " << xo.value << std::endl;
	std::cout << yo.name << ", " << yo.value << std::endl << std::endl;

	std::cout << noseAngle.name << ", " << noseAngle.value << std::endl << std::endl;

	std::cout << chordLen.name << ", " << chordLen.value << std::endl << std::endl;

	std::cout << upperMax.name << ", " << upperMax.value << std::endl;
	std::cout << upperMaxLoc.name << ", " << upperMaxLoc.value << std::endl;
	std::cout << upperNoseTight.name << ", " << upperNoseTight.value << std::endl;
	std::cout << upperMaxTight.name << ", " << upperMaxTight.value << std::endl;
	std::cout << upperTrailAngle.name << ", " << upperTrailAngle.value << std::endl;
	std::cout << upperMaxVel.name << ", " << upperMaxVel.value << std::endl;
	std::cout << upperTrailVel.name << ", " << upperTrailVel.value << std::endl << std::endl;

	std::cout << lowerMax.name << ", " << lowerMax.value << std::endl;
	std::cout << lowerMaxLoc.name << ", " << lowerMaxLoc.value << std::endl;
	std::cout << lowerNoseTight.name << ", " << lowerNoseTight.value << std::endl;
	std::cout << lowerMaxTight.name << ", " << lowerMaxTight.value << std::endl;
	std::cout << lowerTrailAngle.name << ", " << lowerTrailAngle.value << std::endl;
	std::cout << lowerMaxVel.name << ", " << lowerMaxVel.value << std::endl;
	std::cout << lowerTrailVel.name << ", " << lowerTrailVel.value << std::endl << std::endl;

	std::exit(1);*/
	auto profile = std::make_shared<tnbLib::profileLib::GlobalCurve_t1>();
	profile->SetXo(xo.value);
	profile->SetYo(yo.value);

	profile->SetNoseAngle(noseAngle.value);

	profile->SetChordLen(chordLen.value);

	profile->SetUpperMax(upperMax.value);
	profile->SetUpperMaxLoc(upperMaxLoc.value);
	profile->SetUpperNoseTight(upperNoseTight.value);
	profile->SetUpperMaxTight(upperMaxTight.value);
	profile->SetUpperTrailAngle(upperTrailAngle.value);
	profile->SetUpperMaxVel(upperMaxVel.value);
	profile->SetUpperTrailVel(upperTrailVel.value);

	profile->SetLowerMax(lowerMax.value);
	profile->SetLowerMaxLoc(lowerMaxLoc.value);
	profile->SetLowerNoseTight(lowerNoseTight.value);
	profile->SetLowerMaxTight(lowerMaxTight.value);
	profile->SetLowerTrailAngle(lowerTrailAngle.value);
	profile->SetLowerMaxVel(lowerMaxVel.value);
	profile->SetLowerTrailVel(lowerTrailVel.value);

	profile->Perform();
	const auto& curve = profile->Surface();

	auto wire = Pln_Tools::MakeWire({ curve }, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane>
tnbLib::curveLib::airfoilLib::Global_t1::ExportPlane
(
	const std::vector<Standard_Real>& xs
) const
{
	return RetrieveShape(xs);
}