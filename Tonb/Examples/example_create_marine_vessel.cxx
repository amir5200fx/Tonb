#include <Tnb_Examples.hxx>

#include <Entity3d_Box.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <LegModel_DispNo1.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_System.hxx>
#include <FastDiscrete_Params.hxx>

#include <Pln_Wire.hxx>
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

using namespace tnbLib;

void tnbLib::example_create_marine_vessel()
{
	fileName name("example_create_marine_vessel.plt");
	OFstream myFile(name);

	auto ship = std::make_shared<LegModel_DispNo1>();
	Debug_Null_Pointer(ship);

	ship->Perform();

	const auto& myShape = ship->Entity();

	auto b0 = Cad_Tools::BoundingBox(myShape);
	auto box = Cad_Tools::BoundingBox(b0);

	FastDiscrete_Params params;
	params.Deflection = 1.0e-4*box.Diameter();
	params.Angle = 1.0;

	Cad_FastDiscrete::Triangulation(myShape, params);

	auto myTris = Cad_Tools::RetrieveTriangulation(myShape);

	for (const auto& x : myTris)
	{
		auto mesh = Cad_Tools::Triangulation(*x);
		mesh->ExportToPlt(myFile);
	}

	auto domain = box.OffSet(box.Diameter()*0.2);
	auto wave = std::make_shared<Marine_FlatWave>(domain);
	Debug_Null_Pointer(wave);

	wave->SetCurrent(Vec3d(-1.0, -0.0, 0));
	wave->SetVerticalDirection(Dir3d(.0, 0, 1));

	wave->SetPointOnWater(Pnt3d(75, 0, 5));

	wave->Perform();
	
	auto water = Cad_Tools::Triangulation(wave->SurfaceGeometry(), 20, 20);
	Debug_Null_Pointer(water);

	water->ExportToPlt(myFile);

	auto distb = std::make_shared<Marine_SectionDistribution_Uniform>();
	Debug_Null_Pointer(distb);

	distb->SetLower(box.P0().X());
	distb->SetUpper(box.P1().X());
	distb->SetNbSections(40);
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

	gp_Ax1 ax1(ax.Location(), ax.XDirection());

	MarineBase_Tools::Heel(maker, ax1, 20);

	auto waters = MarineBase_Tools::WaterSections(*maker, *wave, domain, 1.0E-3, 1.0E-6);
	auto wetted = MarineBase_Tools::WettedSections(maker, waters);

	for (const auto& x : maker->Sections())
	{
		Debug_Null_Pointer(x);

		const auto& sys = x->CoordinateSystem();
		Handle(Geom_Plane) pl = new Geom_Plane(gp_Pln(sys));

		for (const auto& w : x->Sections())
		{
			Debug_Null_Pointer(w);

			Debug_Null_Pointer(w->Wire());
			const auto& wire = *w->Wire();

			auto poly2d = wire.Polygon();

			Entity3d_Polygon poly3d;
			auto& pts = poly3d.Points();

			for (const auto& x : poly2d->Points())
			{
				gp_Pnt p3 = pl->Value(x.X(), x.Y());
				pts.push_back(p3);
			}
			poly3d.ExportToPlt(myFile);
		}
	}

	for (const auto& x : wetted)
	{
		Debug_Null_Pointer(x);

		const auto& sys = x->CoordinateSystem();
		Handle(Geom_Plane) pl = new Geom_Plane(gp_Pln(sys));

		for (const auto& w : x->Sections())
		{
			Debug_Null_Pointer(w);

			Debug_Null_Pointer(w->Wire());
			const auto& wire = *w->Wire();

			auto poly2d = wire.Polygon();

			Entity3d_Polygon poly3d;
			auto& pts = poly3d.Points();

			for (const auto& x : poly2d->Points())
			{
				gp_Pnt p3 = pl->Value(x.X(), x.Y());
				pts.push_back(p3);
			}
			poly3d.ExportToPlt(myFile);
		}
	}

	/*{
		

		for (const auto& w : waters)
		{
			Debug_Null_Pointer(w);

			const auto& sys = w->CoordinateSystem();
			Handle(Geom_Plane) pl = new Geom_Plane(gp_Pln(sys));

			Debug_Null_Pointer(w->Wire());
			const auto& wire = *w->Wire();

			auto poly2d = wire.Polygon();

			Entity3d_Polygon poly3d;
			auto& pts = poly3d.Points();

			for (const auto& x : poly2d->Points())
			{
				gp_Pnt p3 = pl->Value(x.X(), x.Y());
				pts.push_back(p3);
			}
			poly3d.ExportToPlt(myFile);
		}
	}*/
	
}