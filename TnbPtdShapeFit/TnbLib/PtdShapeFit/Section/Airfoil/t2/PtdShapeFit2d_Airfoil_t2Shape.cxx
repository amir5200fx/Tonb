#include <PtdShapeFit2d_Airfoil_t2.hxx>

#include <PtdShapeFit2d_UpperAirfoilCurve.hxx>
#include <PtdShapeFit2d_LowerAirfoilCurve.hxx>
#include <AirfoilPx_PxCamberProfile_t1.hxx>
#include <AirfoilPx_PxThickProfile_t2.hxx>
#include <AirfoilPx.hxx>

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
tnbLib::airfoilLib::Type2::RetrieveShape
(
	const std::vector<Standard_Real>& xs
) const
{
	auto
		[
			xo,
			yo,
			chordLen,

			maxCamb,
			maxCambLoc,

			leadCambSteep,
			leadCambSteepTight,
			leadCambSteepWeight,

			trailCambSteep,
			trailCambSteepTight,
			trailCambSteepWeight,

			maxThick,
			maxThickLoc,

			leadThickSteepTight1,
			leadThickSteepTight2,

			trailThickSteep,
			trailThickSteepTight,
			trailThickSteepVelocity
		]
	= RetrieveParameters(xs);

	auto camberProfile = std::make_shared<profileLib::CamberProfile_t1>();
	camberProfile->SetMax(maxCamb.value);
	camberProfile->SetMaxLoc(maxCambLoc.value);

	camberProfile->SetLeadSteep(leadCambSteep.value);
	camberProfile->SetLeadSteepTight(leadCambSteepTight.value);
	camberProfile->SetLeadSteepWeight(leadCambSteepWeight.value);

	camberProfile->SetTrailSteep(trailCambSteep.value);
	camberProfile->SetTrailSteepTight(trailCambSteepTight.value);
	camberProfile->SetTrailSteepWeight(trailCambSteepWeight.value);

	auto thickProfile = std::make_shared<profileLib::PxThick_t2>();
	thickProfile->SetMax(maxThick.value);
	thickProfile->SetMaxLoc(maxThickLoc.value);

	thickProfile->SetLeadSteepTight1(leadThickSteepTight1.value);
	thickProfile->SetLeadSteepTight2(leadThickSteepTight2.value);

	thickProfile->SetTrailSteep(trailThickSteep.value);
	thickProfile->SetTrailSteepTight(trailThickSteepTight.value);
	thickProfile->SetTrailSteepVelocity(trailThickSteepVelocity.value);

	auto dist = std::make_shared<Geo_CosineDistb>(NbOffsetPoints());
	dist->SetLower(0);
	dist->SetUpper(chordLen.value);
	dist->Perform();

	auto airfoil = std::make_shared<AirfoilPx>();
	airfoil->SetCamberProfile(camberProfile);
	airfoil->SetThickProfile(thickProfile);
	airfoil->SetXs(dist);

	airfoil->Perform();

	gp_Trsf2d trsf;
	trsf.SetTranslation(Pnt2d(0, 0), Pnt2d(xo.value, yo.value));

	//trsf.Invert();
	airfoil->UpperSurface()->Geometry()->Transform(trsf);
	airfoil->UpperSurface()->Geometry()->Reverse();
	airfoil->LowerSurface()->Geometry()->Transform(trsf);

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	{
		auto upper = std::make_shared<PtdShapeFit2d_UpperAirfoilCurve>
			(
				airfoil->UpperSurface()->Index(),
				airfoil->UpperSurface()->Name(),
				airfoil->UpperSurface()->Geometry()
				);
		curves.push_back(std::move(upper));
	}
	{
		auto lower = std::make_shared<PtdShapeFit2d_LowerAirfoilCurve>
			(
				airfoil->LowerSurface()->Index(),
				airfoil->LowerSurface()->Name(),
				airfoil->LowerSurface()->Geometry()
				);
		curves.push_back(std::move(lower));
	}
	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr);
	Debug_Null_Pointer(plane);

	//std::cout << xo.value << ", " << yo.value << std::endl;

	/*OFstream myFile("plane.plt");
	plane->ExportToPlt(myFile);

	std::exit(1);*/


	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::airfoilLib::Type2::ExportPlane
(
	const std::vector<Standard_Real>& xs
) const
{
	auto
		[
			xo,
			yo,
			chordLen,

			maxCamb,
			maxCambLoc,

			leadCambSteep,
			leadCambSteepTight,
			leadCambSteepWeight,

			trailCambSteep,
			trailCambSteepTight,
			trailCambSteepWeight,

			maxThick,
			maxThickLoc,

			leadThickSteepTight1,
			leadThickSteepTight2,

			trailThickSteep,
			trailThickSteepTight,
			trailThickSteepVelocity
		]
	= RetrieveParameters(xs);

	auto camberProfile = std::make_shared<profileLib::CamberProfile_t1>();
	camberProfile->SetMax(maxCamb.value);
	camberProfile->SetMaxLoc(maxCambLoc.value);

	camberProfile->SetLeadSteep(leadCambSteep.value);
	camberProfile->SetLeadSteepTight(leadCambSteepTight.value);
	camberProfile->SetLeadSteepWeight(leadCambSteepWeight.value);

	camberProfile->SetTrailSteep(trailCambSteep.value);
	camberProfile->SetTrailSteepTight(trailCambSteepTight.value);
	camberProfile->SetTrailSteepWeight(trailCambSteepWeight.value);

	auto thickProfile = std::make_shared<profileLib::PxThick_t2>();
	thickProfile->SetMax(maxThick.value);
	thickProfile->SetMaxLoc(maxThickLoc.value);

	thickProfile->SetLeadSteepTight1(leadThickSteepTight1.value);
	thickProfile->SetLeadSteepTight2(leadThickSteepTight2.value);

	thickProfile->SetTrailSteep(trailThickSteep.value);
	thickProfile->SetTrailSteepTight(trailThickSteepTight.value);
	thickProfile->SetTrailSteepVelocity(trailThickSteepVelocity.value);

	auto dist = std::make_shared<Geo_CosineDistb>(NbOffsetPoints());
	dist->SetLower(0);
	dist->SetUpper(chordLen.value);
	dist->Perform();

	auto airfoil = std::make_shared<AirfoilPx>();
	airfoil->SetCamberProfile(camberProfile);
	airfoil->SetThickProfile(thickProfile);
	airfoil->SetXs(dist);

	airfoil->Perform();

	gp_Trsf2d trsf;
	trsf.SetTranslation(Pnt2d(0, 0), Pnt2d(xo.value, yo.value));

	//trsf.Invert();
	airfoil->UpperSurface()->Geometry()->Transform(trsf);
	airfoil->UpperSurface()->Geometry()->Reverse();
	airfoil->LowerSurface()->Geometry()->Transform(trsf);

	std::vector<std::shared_ptr<Pln_Curve>> 
		curves{ airfoil->UpperSurface(), airfoil->LowerSurface() };
	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr);
	Debug_Null_Pointer(plane);

	//std::cout << xo.value << ", " << yo.value << std::endl;

	/*OFstream myFile("plane.plt");
	plane->ExportToPlt(myFile);

	std::exit(1);*/


	return std::move(plane);
}