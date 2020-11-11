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
//#include <Marine_VesselModel.hxx>
//#include <Marine_ModelMaker_Shape.hxx>
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
//#include <vld.h>

#include <Field.hxx>
#include <Ostream.hxx>
#include <IFstream.hxx>

#include <SectPx_FrameAPI.hxx>
#include <SectPx_Script.hxx>
#include <CadModel_Scripts.hxx>
#include <Cad_Scripts.hxx>
#include <Cad2d_Scripts.hxx>
#include <Geo_Scripts.hxx>
#include <IO_Scripts.hxx>
#include <StbGMaker_Scripts.hxx>


#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include "global_scripts.hxx"
#include <chaiscript/chaiscript.hpp>

#include <exprtk.hpp>

using namespace tnbLib;


template <typename T>
void stddev_example()
{
	typedef exprtk::symbol_table<T> symbol_table_t;
	typedef exprtk::expression<T>     expression_t;
	typedef exprtk::parser<T>             parser_t;

	const std::string expression_string =
		"2*x";

	std::vector<T> x;
	T y;

	symbol_table_t symbol_table;
	symbol_table.add_vector("x", x);
	//symbol_table.add_variable("x", y);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);

	x = { 2.0, 3.0, 4.0 };
	y = 2.0;
	auto v = expression.value();
	std::cout << "value = " << v << std::endl;
}

Standard_Integer main()
{
	tnbLib::FatalError.throwExceptions();

	//return Wt::WRun("test.html", std::vector<std::string>());


	//auto frame = SectPx_FrameAPI::CreateFrame();
	chaiscript::ChaiScript chai;

	//chai.add(chaiscript::fun(&yy::myFun), "my_fun");
	//chai.add(chaiscript::fun(&yy::print), "my_print");
	global_scripts(chai);
	script::load_sectpx(chai);
	script::load_geo(chai);
	script::load_cad_model(chai);
	script::load_cad(chai);
	script::load_stb_gmaker(chai);
	script::load_io_tecplot(chai);
	script::load_cad2d(chai);
	/*PAUSE;
	chai.eval
	(
		R"(puts(var x = create_fixed_par(0.1) );)"
	);*/
	fileName myFileName("nozzle.txt");
	//IFstream myFile(myFileName);
	try
	{
		chai.eval_file(myFileName);
	}
	catch (const chaiscript::exception::eval_error& x)
	{
		std::cout << x.pretty_print();
		std::cout << '\n';
	}

	/*fileName myFileName("openFoamTest.txt");
	OFstream myFile(myFileName);

	Field<scalar> f(5, 0.25);
	Field<scalar> g(5, 0.01);
	f[2] = 0.1;
	f[0] = -0.23;
	myFile << "f = " << f << endl;
	myFile << "g = " << g << endl;

	auto m = tnbLib::max(f, g);
	myFile << "max(f, g) = " << m << endl;

	auto p = f + g;
	myFile << "+(f, g) = " << p << endl;*/
	//example_union_plane_box();
	//example_create_marine_vessel();
	//example_create_ship();
	//example_calculate_volume_ship();
	//example_transform_shape2d();
	//example_geo_compt_polygons();
	//example_cross_curves_ship();
	//example_cad2d_modeler();
	//example_stb_gmaker_creator();
	//example_sect_px_field_function();

	/*gp_Ax2d ax(gp_Pnt2d(0, 0), gp_Dir2d(1, 0));
	Handle(Geom2d_Curve) c = new Geom2d_Circle(gp_Circ2d(ax, 1.0));

	auto inf = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	std::cout << Cad2d_CmptLib::AreaUnderCurve(Pln_Tools::ConvertToTrimmedCurve(c, c->FirstParameter(), c->LastParameter()), 1, inf) << std::endl;
	std::cout << Cad2d_CmptLib::Centre(Pln_Tools::ConvertToTrimmedCurve(c, c->FirstParameter(), c->LastParameter()), inf) << std::endl;
	PAUSE;
	return 0;*/

	//fileName name("out.plt");
	//OFstream myFile(name);
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