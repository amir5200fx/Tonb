#include <Tnb_Examples.hxx>

#include <Entity3d_Box.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <LegModel_DispNo1.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_System.hxx>
#include <FastDiscrete_Params.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>

#include <Pln_Wire.hxx>
#include <Marine_Body.hxx>
#include <Marine_Section.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_SectionDistribution_Uniform.hxx>
#include <MarineBase_Tools.hxx>
#include <CrossSection_xShapeStation.hxx>

#include <Bnd_Box.hxx>
#include <gp_Pln.hxx>
#include <Geom_Plane.hxx>
#include <Poly_Triangulation.hxx>
#include <TopoDS_Shape.hxx>

void tnbLib::example_calculate_volume_ship()
{
	auto ship = std::make_shared<LegModel_DispNo1>();
	Debug_Null_Pointer(ship);

	ship->Perform();

	const auto& myShape = ship->Entity();

	auto b0 = Cad_Tools::BoundingBox(myShape);
	auto box = Cad_Tools::BoundingBox(b0);

	auto domain = box.OffSet(box.Diameter()*0.2);
	auto wave = std::make_shared<Marine_FlatWave>(domain);
	Debug_Null_Pointer(wave);

	wave->SetCurrent(Vec3d(-1.0, -0.0, 0));
	wave->SetVerticalDirection(Dir3d(.0, 0, 1));

	wave->SetPointOnWater(Pnt3d(75, 0, 8));

	wave->Perform();

	auto distb = std::make_shared<Marine_SectionDistribution_Uniform>();
	Debug_Null_Pointer(distb);

	distb->SetLower(box.P0().X());
	distb->SetUpper(box.P1().X());
	distb->SetNbSections(60);
	distb->Perform();

	const auto ym = MEAN(box.P0().Y(), box.P1().Y());
	Pnt3d Po(box.P0().X(), ym, box.P0().Z());
	gp_Ax2 ax = gp::XOY();
	ax.SetLocation(Po);

	auto maker = std::make_shared<CrossSection_xShapeStation>(ax);
	Debug_Null_Pointer(maker);

	maker->LoadShape(myShape);
	maker->LoadDistributor(distb);
	maker->Perform();

	auto waters = MarineBase_Tools::WaterSections(*maker, *wave, domain, 1.0E-3, 1.0E-6);

	auto wetted = MarineBase_Tools::WettedSections(maker->Sections(), waters);

	auto info = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	Debug_Null_Pointer(info);

	info->SetTolerance(1.0e-4);
	info->SetNbInitIterations(2);

	const auto volumeQ = MarineBase_Tools::CalcVolume(wetted->Sections(), info);

	cout << "Volume of the wetted areas = " << MarineBase_Tools::CalcArea(volumeQ, info) << std::endl;
	
	const auto bxQ = MarineBase_Tools::CalcWaterPlaneArea(wetted->Sections(), info);

	cout << "WL section area = " << MarineBase_Tools::CalcArea(bxQ, info) << std::endl;

	const auto wetSurfAreaQ = MarineBase_Tools::CalcWettedHullSurfaceArea(wetted->Sections(), info);

	cout << "Wetted Area = " << MarineBase_Tools::CalcArea(wetSurfAreaQ, info) << std::endl;
}