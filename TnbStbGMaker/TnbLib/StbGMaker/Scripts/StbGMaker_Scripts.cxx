#include <StbGMaker_Scripts.hxx>

#include <Geo_xDistb.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Modeler.hxx>
#include <Marine_Shapes.hxx>
#include <StbGMaker_WP.hxx>
#include <StbGMaker_ShapeTools.hxx>
#include <StbGMaker_Creator.hxx>
#include <StbGMaker_HullCreators.hxx>
#include <StbGMaker_TankCreators.hxx>
#include <StbGMaker_SailCreators.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	static void stb_gmaker_create_plane_wp(const std::shared_ptr<StbGMaker_WP>& theWp)
	{
		const auto& modeler = theWp->Modeler();
		Debug_Null_Pointer(modeler);

		Cad2d_Modeler::selctList l;
		modeler->SelectAll(l);

		modeler->MakePlane(l);
	}

	static void stb_gmaker_create_plane(const std::vector<std::shared_ptr<StbGMaker_WP>>& theWps)
	{
		for (const auto& x : theWps)
		{
			Debug_Null_Pointer(x);
			stb_gmaker_create_plane_wp(x);
		}
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

void tnbLib::script::load_stb_gmaker(chaiscript::ChaiScript& chai)
{
	auto mod = std::make_shared<chaiscript::Module>();

	mod->add(chaiscript::user_type<marineLib::Shape_Sail>(), "marine_shape_sail");
	mod->add(chaiscript::user_type<marineLib::Shape_Hull>(), "marine_shape_hull");
	mod->add(chaiscript::user_type<marineLib::Shape_Tank>(), "marine_shape_tank");
	mod->add(chaiscript::user_type<Marine_Shape>(), "marine_shape");

	mod->add(chaiscript::fun(&StbGMaker_ShapeTools::Hull), "stb_model_create_hull");
	mod->add(chaiscript::fun(&StbGMaker_ShapeTools::Sail), "stb_model_create_sail");
	mod->add(chaiscript::fun(&StbGMaker_ShapeTools::Tank), "stb_model_create_tank");

	mod->add(chaiscript::user_type<StbGMaker_Creator>(), "stb_model_creator");
	mod->add(chaiscript::fun([]() {auto s = std::make_shared<StbGMaker_Creator>(); return std::move(s); }), "stb_model_creator");

	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_HullCreator>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "create_wps");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_TankCreator>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "create_wps");
	mod->add(chaiscript::fun([](const std::shared_ptr<stbGmakerLib::GeometricSailCreator_noShape>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "create_wps");
	mod->add(chaiscript::fun([](const std::shared_ptr<stbGmakerLib::GeometricSailCreator_Shape>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "create_wps");

	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const std::shared_ptr<marineLib::Shape_Tank>& t)-> Standard_Integer {return c->CreateTankMaker(t); }), "create_tank_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const std::shared_ptr<marineLib::Shape_Hull>& t)-> void {c->CreateHullMaker(t); }), "create_hull_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const Standard_Real a, const Standard_Real z)-> Standard_Integer {return c->CreateConstAreaSailMaker(a, z); }), "create_const_area_sail_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const std::shared_ptr<Cad2d_Plane>& a, const Standard_Real z)-> Standard_Integer {return c->CreatePlaneGeomSailMaker(a, z); }), "create_plane_sail_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const std::shared_ptr<marineLib::Shape_Sail>& t)-> Standard_Integer {return c->CreateShapeGeomSailMaker(t); }), "create_shape_sail_maker");

	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_TankCreator> {auto s = c->SelectTankMaker(i); return std::move(s); }), "select_tank_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_SailCreator> {auto s = c->SelectSailMaker(i); return std::move(s); }), "select_sail_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c)-> const std::shared_ptr<StbGMaker_HullCreator>& {return c->HullMaker(); }), "hull_maker");

	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_TankCreator> {auto s = c->RemoveTankMaker(i); return std::move(s); }), "remove_tank_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_SailCreator> {auto s = c->RemoveSailMaker(i); return std::move(s); }), "remove_sail_maker");
	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_Creator>& c)-> std::shared_ptr<StbGMaker_HullCreator> {return c->RemoveHullMaker(); }), "remove_hull_maker");

	mod->add(chaiscript::fun(&stb_gmaker_create_plane), "stb_gmaker_create_plane");

	chai.add(mod);
}