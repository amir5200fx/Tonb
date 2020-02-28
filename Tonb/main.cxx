#include <Standard_TypeDef.hxx>

#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_System.hxx>
#include <TnbCad2d_System.hxx>
#include <dimensionedScalar.hxx>

#include <gp_Pln.hxx>
#include <Geom_Plane.hxx>
#include <Marine_Section.hxx>
#include <Marine_CmpSection.hxx>
#include <Marine_VesselModel.hxx>
#include <Marine_SectionDistribution_Uniform.hxx>
#include <Marine_ModelMaker_Shape.hxx>
#include <Marine_FlatWave.hxx>
#include <LegModel_DispNo1.hxx>
#include <Cad_FastDiscrete.hxx>
#include <FastDiscrete_System.hxx>
#include <FastDiscrete_Params.hxx>
#include <Cad2d_CmptLib.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Pln_Tools.hxx>

#include <Poly_Triangulation.hxx>
#include <Bnd_Box.hxx>
#include <Geom2d_Circle.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Ax2d.hxx>

#include <Tnb_Examples.hxx>

#include <armadillo.h>

using namespace tnbLib;

Standard_Integer main()
{

	//example_union_plane_box();
	//example_create_marine_vessel();
	//example_create_ship();
	//example_calculate_volume_ship();
	//example_transform_shape2d();
	example_geo_compt_polygons();

	/*gp_Ax2d ax(gp_Pnt2d(0, 0), gp_Dir2d(1, 0));
	Handle(Geom2d_Curve) c = new Geom2d_Circle(gp_Circ2d(ax, 1.0));

	auto inf = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	std::cout << Cad2d_CmptLib::AreaUnderCurve(Pln_Tools::ConvertToTrimmedCurve(c, c->FirstParameter(), c->LastParameter()), 1, inf) << std::endl;
	std::cout << Cad2d_CmptLib::Centre(Pln_Tools::ConvertToTrimmedCurve(c, c->FirstParameter(), c->LastParameter()), inf) << std::endl;
	PAUSE;
	return 0;*/

	fileName name("out.plt");
	OFstream myFile(name);
	/*sysLib::init_TnbCad2d();

	auto pln = Cad2d_Plane::MakeBox(Pnt2d(0, 0), Pnt2d(1.0, 0.38), sysLib::gl_cad2d_plane_info);
	Debug_Null_Pointer(pln);*/

	/*dimensionedScalar dim0("CB", dimless, 0.1);
	dimensionedScalar dim1("CB", dimless, 0.5);

	auto d = dim0*dim0 + dim1;

	myFile << d << endl;*/

	/*auto ship = std::make_shared<LegModel_DispNo1>();
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
	wave->SetVerticalDirection(Dir3d(.1, 0, 0.99498743710662));
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

	auto maker = std::make_shared<Marine_ModelMaker_Shape>();
	Debug_Null_Pointer(maker);

	maker->LoadShape(myShape);
	maker->LoadDistributor(distb);
	maker->Perform();

	auto vessel = std::dynamic_pointer_cast<Marine_VesselModel>(maker->Model());
	Debug_Null_Pointer(vessel);

	for (const auto& sec : vessel->Sections())
	{
		const auto& x = sec.second;
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
	}*/

	PAUSE;
	return 0;
}