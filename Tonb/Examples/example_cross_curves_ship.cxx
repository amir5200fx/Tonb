#include <Tnb_Examples.hxx>

#include <Pln_CurveTools.hxx>
#include <Cad_Tools.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_Domain.hxx>
#include <Marine_SectionDistribution_Uniform.hxx>
#include <Marine_Graph.hxx>
#include <Marine_GraphCurve.hxx>
#include <CrossSection_xShapeStation.hxx>
#include <HydroStatic_CrossCurves.hxx>
#include <LegModel_DispNo1.hxx>
#include <OFstream.hxx>

#include <Bnd_Box.hxx>

void tnbLib::example_cross_curves_ship()
{
	auto ship = std::make_shared<LegModel_DispNo1>();
	Debug_Null_Pointer(ship);

	ship->Perform();

	const auto& myShape = ship->Entity();
	auto b0 = Cad_Tools::BoundingBox(myShape);
	auto box = Cad_Tools::BoundingBox(b0);

	auto domain = std::make_shared<Marine_Domain>();
	Debug_Null_Pointer(domain);

	domain->Perform(box);

	auto distb = std::make_shared<Marine_SectionDistribution_Uniform>();
	Debug_Null_Pointer(distb);

	distb->SetLower(box.P0().X());
	distb->SetUpper(box.P1().X());
	distb->SetNbSections(30);
	distb->Perform();

	const auto ym = MEAN(box.P0().Y(), box.P1().Y());
	Pnt3d Po(box.P0().X(), ym, box.P0().Z());
	gp_Ax2 ax = gp::XOY();
	ax.SetLocation(Po);

	auto model = std::make_shared<CrossSection_xShapeStation>(ax);
	Debug_Null_Pointer(model);

	model->LoadShape(myShape);
	model->LoadDistributor(distb);
	model->Perform();

	auto heel = MarineBase_Tools::HeelDistb(0, 90, 10);
	Debug_Null_Pointer(heel);
	
	auto crossCurves = std::make_shared<HydroStatic_CrossCurves>(domain);
	Debug_Null_Pointer(crossCurves);

	crossCurves->LoadModel(model);
	crossCurves->LoadHeel(heel);

	crossCurves->Perform();

	fileName myFileName("example_cross_curves_ship.plt");
	OFstream myFile(myFileName);

	const auto& curves = crossCurves->Graph()->Curves();
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);
		Pln_CurveTools::ExportToPlt(x->Curve(), myFile);
	}
}