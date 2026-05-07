#include <PtdShapeFit2d_Airfoil_t1.hxx>

#include <PtdShapeFit2d_UpperAirfoilCurve.hxx>
#include <PtdShapeFit2d_LowerAirfoilCurve.hxx>
#include <AirfoilPx_PxCamberProfile_t1.hxx>
#include <AirfoilPx_PxThickProfile_t1.hxx>
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
tnbLib::airfoilLib::Type1::RetrieveShape
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

			leadThickSteep,
			leadThickSteepTight,
			leadThickSteepWeight,

			trailThickSteep,
			trailThickSteepTight,
			trailThickSteepWeight
		]
	= RetrieveParameters(xs);

	/*std::cout << xo.name << ": " << xo.value << std::endl;
	std::cout << yo.name << ": " << yo.value << std::endl << std::endl;

	std::cout << chordLen.value << ": " << chordLen.name << std::endl << std::endl;

	std::cout << maxCamb.name << ": " << maxCamb.value << std::endl;
	std::cout << maxCambLoc.name << ": " << maxCambLoc.value << std::endl;
	std::cout << leadCambSteep.name << ": " << leadCambSteep.value << std::endl;
	std::cout << leadCambSteepTight.name << ": " << leadCambSteepTight.value << std::endl;
	std::cout << leadCambSteepWeight.name << ": " << leadCambSteepWeight.value << std::endl;
	std::cout << trailCambSteep.name << ": " << trailCambSteep.value << std::endl;
	std::cout << trailCambSteepTight.name << ": " << trailCambSteepTight.value << std::endl;
	std::cout << trailCambSteepWeight.name << ": " << trailCambSteepWeight.value << std::endl << std::endl;

	std::cout << maxThick.name << ": " << maxThick.value << std::endl;
	std::cout << maxThickLoc.name << ": " << maxThickLoc.value << std::endl;
	std::cout << leadThickSteep.name << ": " << leadThickSteep.value << std::endl;
	std::cout << leadThickSteepTight.name << ": " << leadThickSteepTight.value << std::endl;
	std::cout << leadThickSteepWeight.name << ": " << leadThickSteepWeight.value << std::endl;
	std::cout << trailThickSteep.name << ": " << trailThickSteep.value << std::endl;
	std::cout << trailThickSteepTight.name << ": " << trailThickSteepTight.value << std::endl;
	std::cout << trailThickSteepWeight.name << ": " << trailThickSteepWeight.value << std::endl << std::endl;

	PAUSE;*/

	auto camberProfile = std::make_shared<profileLib::CamberProfile_t1>();
	camberProfile->SetMax(maxCamb.value);
	camberProfile->SetMaxLoc(maxCambLoc.value);

	camberProfile->SetLeadSteep(leadCambSteep.value);
	camberProfile->SetLeadSteepTight(leadCambSteepTight.value);
	camberProfile->SetLeadSteepWeight(leadCambSteepWeight.value);

	camberProfile->SetTrailSteep(trailCambSteep.value);
	camberProfile->SetTrailSteepTight(trailCambSteepTight.value);
	camberProfile->SetTrailSteepWeight(trailCambSteepWeight.value);

	auto thickProfile = std::make_shared<profileLib::PxThick_t1>();
	thickProfile->SetMax(maxThick.value);
	thickProfile->SetMaxLoc(maxThickLoc.value);

	thickProfile->SetLeadSteep(leadThickSteep.value);
	thickProfile->SetLeadSteepTight(leadThickSteepTight.value);
	thickProfile->SetLeadSteepWeight(leadThickSteepWeight.value);

	thickProfile->SetTrailSteep(trailThickSteep.value);
	thickProfile->SetTrailSteepTight(trailThickSteepTight.value);
	thickProfile->SetTrailSteepWeight(trailThickSteepWeight.value);

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
tnbLib::airfoilLib::Type1::ExportPlane(const std::vector<Standard_Real>& xs) const
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

			leadThickSteep,
			leadThickSteepTight,
			leadThickSteepWeight,

			trailThickSteep,
			trailThickSteepTight,
			trailThickSteepWeight
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

	auto thickProfile = std::make_shared<profileLib::PxThick_t1>();
	thickProfile->SetMax(maxThick.value);
	thickProfile->SetMaxLoc(maxThickLoc.value);

	thickProfile->SetLeadSteep(leadThickSteep.value);
	thickProfile->SetLeadSteepTight(leadThickSteepTight.value);
	thickProfile->SetLeadSteepWeight(leadThickSteepWeight.value);

	thickProfile->SetTrailSteep(trailThickSteep.value);
	thickProfile->SetTrailSteepTight(trailThickSteepTight.value);
	thickProfile->SetTrailSteepWeight(trailThickSteepWeight.value);

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