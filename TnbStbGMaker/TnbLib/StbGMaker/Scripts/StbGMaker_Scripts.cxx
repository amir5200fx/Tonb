//#include <StbGMaker_Scripts.hxx>
//
//#include <Geo_xDistb.hxx>
//#include <Cad2d_Plane.hxx>
//#include <Cad2d_Modeler.hxx>
//#include <Marine_Shapes.hxx>
//#include <StbGMaker_WP.hxx>
//#include <StbGMaker_ShapeTools.hxx>
//#include <StbGMaker_Creator.hxx>
//#include <StbGMaker_HullCreators.hxx>
//#include <StbGMaker_TankCreators.hxx>
//#include <StbGMaker_SailCreators.hxx>
//
//#include <TopoDS_Shape.hxx>
//
//std::shared_ptr<tnbLib::StbGMaker_Creator> 
//tnbLib::script::StbModelMaker::newModelMaker() const
//{
//	auto t = std::make_shared<StbGMaker_Creator>();
//	return std::move(t);
//}
//
//std::shared_ptr<tnbLib::marineLib::Shape_Sail> 
//tnbLib::script::StbModelMaker::newSailShape
//(
//	const TopoDS_Shape & s
//)
//{
//	auto t = StbGMaker_ShapeTools::Sail(s);
//	return std::move(t);
//}
//
//std::shared_ptr<tnbLib::marineLib::Shape_Hull> 
//tnbLib::script::StbModelMaker::newHullShape
//(
//	const TopoDS_Shape & s
//)
//{
//	auto t = StbGMaker_ShapeTools::Hull(s);
//	return std::move(t);
//}
//
//std::shared_ptr<tnbLib::marineLib::Shape_Tank> 
//tnbLib::script::StbModelMaker::newTankShape
//(
//	const TopoDS_Shape & s
//)
//{
//	auto t = StbGMaker_ShapeTools::Tank(s);
//	return std::move(t);
//}
//
//namespace tnbLib
//{
//
//	static void stb_gmaker_create_plane_wp(const std::shared_ptr<StbGMaker_WP>& theWp)
//	{
//		const auto& modeler = theWp->Modeler();
//		Debug_Null_Pointer(modeler);
//
//		Cad2d_Modeler::selctList l;
//		modeler->SelectAll(l);
//
//		modeler->MakePlane(l);
//	}
//
//	static void stb_gmaker_create_plane(const std::vector<std::shared_ptr<StbGMaker_WP>>& theWps)
//	{
//		for (const auto& x : theWps)
//		{
//			Debug_Null_Pointer(x);
//			stb_gmaker_create_plane_wp(x);
//		}
//	}
//}
//
//#ifdef DebugInfo
//#undef DebugInfo
//#endif // DebugInfo
//
//#include <chaiscript/chaiscript.hpp>
//
//void tnbLib::script::load_stb_gmaker(chaiscript::ChaiScript& chai)
//{
//	auto mod = std::make_shared<chaiscript::Module>();
//
//	typedef std::shared_ptr<StbGMaker_Creator> creator_t;
//	typedef std::shared_ptr<StbModelMaker> stbModelMaker_t;
//
//	mod->add(chaiscript::user_type<std::shared_ptr<StbModelMaker>>(), "StbModelMaker");
//	mod->add(chaiscript::fun([]() {auto t = std::make_shared<StbModelMaker>(); return std::move(t); }), "newStbModelMaker");
//	
//	mod->add(chaiscript::user_type<creator_t>(), "ModelMaker");
//	mod->add(chaiscript::fun([](const stbModelMaker_t& t)->creator_t {return t->newModelMaker(); }), "newModelMaker");
//
//	mod->add(chaiscript::fun([](const stbModelMaker_t& t, const TopoDS_Shape& s)->std::shared_ptr<marineLib::Shape_Sail> {auto tt = t->newSailShape(s); return std::move(tt); }), "newSailShape");
//	mod->add(chaiscript::fun([](const stbModelMaker_t& t, const TopoDS_Shape& s)->std::shared_ptr<marineLib::Shape_Hull> {auto tt = t->newHullShape(s); return std::move(tt); }), "newHullShape");
//	mod->add(chaiscript::fun([](const stbModelMaker_t& t, const TopoDS_Shape& s)->std::shared_ptr<marineLib::Shape_Tank> {auto tt = t->newTankShape(s); return std::move(tt); }), "newTankShape");
//
//	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_HullCreator>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "createWorkingPlanes");
//	mod->add(chaiscript::fun([](const std::shared_ptr<StbGMaker_TankCreator>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "createWorkingPlanes");
//	mod->add(chaiscript::fun([](const std::shared_ptr<stbGmakerLib::GeometricSailCreator_noShape>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "createWorkingPlanes");
//	mod->add(chaiscript::fun([](const std::shared_ptr<stbGmakerLib::GeometricSailCreator_Shape>& c, const std::shared_ptr<Geo_xDistb>& d)-> void {c->CreateWorkingPlanes(*d); }), "createWorkingPlanes");
//
//	mod->add(chaiscript::fun([](const creator_t& c, const std::shared_ptr<marineLib::Shape_Tank>& t)-> Standard_Integer {return c->CreateTankMaker(t); }), "createTankMaker");
//	mod->add(chaiscript::fun([](const creator_t& c, const std::shared_ptr<marineLib::Shape_Hull>& t)-> void {c->CreateHullMaker(t); }), "createHullMaker");
//	mod->add(chaiscript::fun([](const creator_t& c, const Standard_Real a, const Standard_Real z)-> Standard_Integer {return c->CreateConstAreaSailMaker(a, z); }), "createConstAreaSailMaker");
//	mod->add(chaiscript::fun([](const creator_t& c, const std::shared_ptr<Cad2d_Plane>& a, const Standard_Real z)-> Standard_Integer {return c->CreatePlaneGeomSailMaker(a, z); }), "createPlaneSailMaker");
//	mod->add(chaiscript::fun([](const creator_t& c, const std::shared_ptr<marineLib::Shape_Sail>& t)-> Standard_Integer {return c->CreateShapeGeomSailMaker(t); }), "createShapeSailMaker");
//
//	mod->add(chaiscript::fun([](const creator_t& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_TankCreator> {auto s = c->SelectTankMaker(i); return std::move(s); }), "getTankMaker");
//	mod->add(chaiscript::fun([](const creator_t& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_SailCreator> {auto s = c->SelectSailMaker(i); return std::move(s); }), "getSailMaker");
//	mod->add(chaiscript::fun([](const creator_t& c)-> const std::shared_ptr<StbGMaker_HullCreator>& {return c->HullMaker(); }), "getHullMaker");
//
//	mod->add(chaiscript::fun([](const creator_t& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_TankCreator> {auto s = c->RemoveTankMaker(i); return std::move(s); }), "removeTankMaker");
//	mod->add(chaiscript::fun([](const creator_t& c, const Standard_Integer i)-> std::shared_ptr<StbGMaker_SailCreator> {auto s = c->RemoveSailMaker(i); return std::move(s); }), "removeSailMaker");
//	mod->add(chaiscript::fun([](const creator_t& c)-> std::shared_ptr<StbGMaker_HullCreator> {return c->RemoveHullMaker(); }), "removeHullMaker");
//
//	mod->add(chaiscript::fun(&stb_gmaker_create_plane), "stb_gmaker_create_plane");
//
//	chai.add(mod);
//}