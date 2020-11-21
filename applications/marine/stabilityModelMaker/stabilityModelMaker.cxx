#include <Dir3d.hxx>
#include <Geo_xDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad2d_Modeler_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Tools.hxx>
#include <CadIO_IGES.hxx>
#include <CadIO_STEP.hxx>
#include <Marine_Shapes.hxx>
#include <StbGMaker_WP.hxx>
#include <StbGMaker_ShapeTools.hxx>
#include <StbGMaker_Creator.hxx>
#include <StbGMaker_HullCreators.hxx>
#include <StbGMaker_TankCreators.hxx>
#include <StbGMaker_SailCreators.hxx>

#include <Bnd_Box.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Shape.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>


namespace tnbLib
{

	static const double tol = 1.0E-4;
	static const auto gMaker = std::make_shared<StbGMaker_Creator>();


	typedef std::shared_ptr<StbGMaker_Creator> creator_t;
	typedef std::shared_ptr<marineLib::Shape_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Shape_Sail> sail_t;
	typedef std::shared_ptr<marineLib::Shape_Hull> hull_t;

	typedef std::shared_ptr<StbGMaker_HullCreator> hullCreator_t;
	typedef std::shared_ptr<StbGMaker_SailCreator> sailCreator_t;
	typedef std::shared_ptr<StbGMaker_TankCreator> tankCreator_t;

	typedef std::shared_ptr<StbGMaker_WP> wp_t;

	typedef std::shared_ptr<Geo_xDistb> xDisbt_t;

	//- global functions

	const auto& getMaker()
	{
		return gMaker;
	}

	const auto& getHull()
	{
		return getMaker()->HullMaker();
	}

	const auto& createHull()
	{
		if (getHull())
		{
			FatalErrorIn(FunctionSIG)
				<< "the hullMaker is already created!" << endl
				<< abort(FatalError);
		}
		getMaker()->CreateHullMaker();
		return getHull();
	}

	const auto& createHull(const hull_t& t)
	{
		if (getHull())
		{
			FatalErrorIn(FunctionSIG)
				<< "the hullMaker is already created!" << endl
				<< abort(FatalError);
		}
		getMaker()->CreateHullMaker(t);
		return getHull();
	}

	auto createTank()
	{
		auto t = getMaker()->SelectTankMaker(getMaker()->CreateTankMaker());
		return std::move(t);
	}

	auto createTank(const tank_t& t)
	{
		auto t = getMaker()->SelectTankMaker(getMaker()->CreateTankMaker(t));
		return std::move(t);
	}

	auto createSail()
	{
		auto t = getMaker()->SelectSailMaker(getMaker()->CreateShapeGeomSailMaker());
		return std::move(t);
	}

	auto createSail(const sail_t& s)
	{
		auto t = getMaker()->SelectSailMaker(getMaker()->CreateShapeGeomSailMaker(s));
		return std::move(t);
	}

	auto getNbTanks()
	{
		return getMaker()->NbTanks();
	}

	auto getNbSails()
	{
		return getMaker()->NbSails();
	}

	//- spacing functions



	//- io functions

	TopoDS_Shape importIges(const fileName& name)
	{
		CadIO_IGES iges_reader;
		iges_reader.ReadFile(name);

		auto shape = iges_reader.Shape();
		return std::move(shape);
	}

	TopoDS_Shape importStep(const fileName& name)
	{
		CadIO_STEP step_reader;
		step_reader.ReadFile(name);

		auto shape = step_reader.Shape();
		return std::move(shape);
	}

	const auto& importHullMakerFromIGES(const fileName& name)
	{
		const auto& maker = getMaker();
		if (maker->HullMaker())
		{
			FatalErrorIn(FunctionSIG)
				<< "the hull maker has been created, already!"
				<< abort(FatalError);
		}

		auto shape = importIges(name);
		maker->CreateHullMaker(StbGMaker_ShapeTools::Hull(shape));
		return maker->HullMaker();
	}

	const auto& importHullMakerFromSTEP(const fileName& name)
	{
		const auto& maker = getMaker();
		if (maker->HullMaker())
		{
			FatalErrorIn(FunctionSIG)
				<< "the hull maker has been created, already!"
				<< abort(FatalError);
		}

		auto shape = importStep(name);
		maker->CreateHullMaker(StbGMaker_ShapeTools::Hull(shape));
		return maker->HullMaker();
	}

	auto importTankMakerFromIGES(const fileName& name)
	{
		const auto& maker = getMaker();
		auto shape = importIges(name);

		auto t = maker->SelectTankMaker(maker->CreateTankMaker(StbGMaker_ShapeTools::Tank(shape)));
		return std::move(t);
	}

	auto importTankMakerFromSTEP(const fileName& name)
	{
		const auto& maker = getMaker();
		auto shape = importStep(name);

		auto t = maker->SelectTankMaker(maker->CreateTankMaker(StbGMaker_ShapeTools::Tank(shape)));
		return std::move(t);
	}

	auto importSailMakerFromIGES(const fileName& name)
	{
		const auto& maker = getMaker();
		auto shape = importIges(name);

		auto t = maker->SelectSailMaker(maker->CreateShapeGeomSailMaker(StbGMaker_ShapeTools::Sail(shape)));
		return std::move(t);
	}

	auto importSailMakerFromSTEP(const fileName& name)
	{
		const auto& maker = getMaker();
		auto shape = importStep(name);

		auto t = maker->SelectSailMaker(maker->CreateShapeGeomSailMaker(StbGMaker_ShapeTools::Sail(shape)));
		return std::move(t);
	}

	void exportTo(const word& name)
	{
		auto model = getMaker()->ExportModel();
		fileName myFileName(name);
		std::ofstream myFile(myFileName);

		boost::archive::polymorphic_binary_oarchive ar(myFile);

		ar << model;
	}

	// HullMaker functions 

	auto creatHullSection(const double x)
	{
		auto t = getHull()->SelectWP(getHull()->CreateWorkingPlane(x));
		return std::move(t);
	}
	
	// Working Plane

	void createSegment(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = cad2dLib::Modeler_Tools::MakeSegment(p0, p1);
		wp->Modeler()->Import(std::move(geom));
	}
	
	void createCirArc(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	{
		auto geom = cad2dLib::Modeler_Tools::MakeCircArc(p0, p1, p2);
		wp->Modeler()->Import(std::move(geom));
	}
	
	void createCirArc(const wp_t& wp, const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p1)
	{
		auto geom = cad2dLib::Modeler_Tools::MakeCircArc(p0, v0, p1);
		wp->Modeler()->Import(std::move(geom));
	}


	void createCirArc(const wp_t& wp, const gp_Circ2d& circ, const double alpha0, const double alpha1)
	{
		auto geom = cad2dLib::Modeler_Tools::MakeCircArc(circ, alpha0, alpha1);
		wp->Modeler()->Import(std::move(geom));
	}

		//   


	Pnt3d createPoint(const double x, const double y, const double z)
	{
		Pnt3d pt(x, y, z);
		return std::move(pt);
	}

	Dir3d createDirection(const double x, const double y, const double z)
	{
		try
		{
			Dir3d dir(x, y, z);
			return std::move(dir);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("Dir3d createDirection(const double x, const double y, const double z)")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}	
	}

	gp_Ax2 createAxis(const Pnt3d& pt, const Dir3d& dir)
	{
		try
		{
			gp_Ax2 ax(pt, dir);
			return std::move(ax);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("gp_Ax2 createAxis(const Pnt3d& pt, const Dir3d& dir)")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createCylinder(const gp_Ax2& ax, const double r, const double h)
	{
		try
		{
			auto cyl = Cad_ShapeTools::Cylinder(ax, r, h);
			return std::move(cyl);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createCylinder(const gp_Ax2& ax, const double r, const double h)")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createBox(const Pnt3d& p0, const Pnt3d& p1)
	{
		try
		{
			auto box = Cad_ShapeTools::Box(p0, p1);
			return std::move(box);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createBox(const Pnt3d& p0, const Pnt3d& p1)")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createBox(const Pnt3d& p0, const double dx, const double dy, const double dz)
	{
		try
		{
			auto box = Cad_ShapeTools::Box(p0, dx, dy, dz);
			return std::move(box);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createBox()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createBox(const gp_Ax2& ax, const double dx, const double dy, const double dz)
	{
		try
		{
			auto box = Cad_ShapeTools::Box(ax, dx, dy, dz);
			return std::move(box);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createBox()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createSphere(const Pnt3d& pt, const double r)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(pt, r);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r, const double ang1)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r, ang1);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r, const double ang1, const double ang2)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r, ang1, ang2);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r, const double ang1, const double ang2, const double ang3)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r, ang1, ang2, ang3);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
	}

	auto createHull(const TopoDS_Shape& s)
	{
		auto shape = StbGMaker_ShapeTools::Hull(s);
		return std::move(shape);
	}

	auto createTank(const TopoDS_Shape& s)
	{
		auto shape = StbGMaker_ShapeTools::Tank(s);
		return std::move(shape);
	}

	auto createSail(const TopoDS_Shape& s)
	{
		auto shape = StbGMaker_ShapeTools::Sail(s);
		return std::move(shape);
	}

	auto boundingBox(const TopoDS_Shape& s)
	{
		auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(s));
		return std::move(b);
	}

	auto createUniformDistb(const double x0, const double x1, const int n)
	{
		auto d = std::make_shared<Geo_UniDistb>(n);
		d->SetLower(x0);
		d->SetUpper(x1);
		d->Perform();
		return std::move(d);
	}

	auto createCosineDistb(const double x0, const double x1, const int n)
	{
		auto d = std::make_shared<Geo_CosineDistb>(n);
		d->SetLower(x0);
		d->SetUpper(x1);
		d->Perform();
		return std::move(d);
	}

	// - spacing

	auto xBound(const TopoDS_Shape& s)
	{
		auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(s));
		auto t = b.Bound(0);
		return std::move(t);
	}

	auto makeCreator()
	{
		auto t = std::make_shared<StbGMaker_Creator>();
		return std::move(t);
	}

	auto createTankMaker(const creator_t& t, const tank_t& k)
	{
		return t->CreateTankMaker(k);
	}

	auto createCustomTankMaker(const creator_t& t)
	{
		return t->CreateTankMaker();
	}

	void createHullMaker(const creator_t& t, const hull_t& h)
	{
		t->CreateHullMaker(h);
	}

	auto createCustomHullMaker(const creator_t& t)
	{
		return t->CreateHullMaker();
	}

	auto createShapeSailMaker(const creator_t& t, const sail_t& s)
	{
		return t->CreateShapeGeomSailMaker(s);
	}

	auto selectTankMaker(const creator_t& t, const int id)
	{
		auto item = t->SelectTankMaker(id);
		return std::move(item);
	}

	auto selectSailMaker(const creator_t& t, const int id)
	{
		auto item = t->SelectSailMaker(id);
		return std::move(item);
	}

	const auto& hullMaker(const creator_t& t)
	{
		return t->HullMaker();
	}

	void createWPs(const hullCreator_t& t, const xDisbt_t& d)
	{
		t->CreateWorkingPlanes(*d);
	}

	void createWPs(const tankCreator_t& t, const xDisbt_t& d)
	{
		t->CreateWorkingPlanes(*d);
	}

	
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->const auto& {return importHullMakerFromIGES(name); }), "createHullFromIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> const auto& {return importHullMakerFromSTEP(name); }), "createHullFromSTEP");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importTankMakerFromIGES(name); return std::move(t); }), "createTankFromIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importTankMakerFromSTEP(name); return std::move(t); }), "createTankFromSTEP");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importSailMakerFromIGES(name); return std::move(t); }), "createSailFromIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importSailMakerFromSTEP(name); return std::move(t); }), "createSailFromSTEP");

		//- spacing

		//- shapes

		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{auto t = createHull(s); }), "createHullShape");
		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{auto t = createTank(s); }), "createTankShape");
		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{auto t = createSail(s); }), "createSailShape");
	}

	void setDefaultShapes(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const double x, const double y, const double z)->auto{auto t = createPoint(x, y, z); return std::move(t); }), "createPoint");
		mod->add(chaiscript::fun([](const double x, const double y, const double z)->auto {auto t = createDirection(x, y, z); return std::move(t); }), "createDirection");
		mod->add(chaiscript::fun([](const Pnt3d& pt, const Dir3d& dir)->auto{auto t = createAxis(pt, dir); return std::move(t); }), "createAxis");

		mod->add(chaiscript::fun([](const gp_Ax2& ax, const double r, const double h)-> auto{auto t = createCylinder(ax, r, h); return std::move(t); }), "createCylinder");
		mod->add(chaiscript::fun([](const Pnt3d& p0, const Pnt3d& p1)-> auto {auto t = createBox(p0, p1); return std::move(t); }), "createBox");
		mod->add(chaiscript::fun([](const Pnt3d& p0, const double dx, const double dy, const double dz)-> auto {auto t = createBox(p0, dx, dy, dz); return std::move(t); }), "createBox");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, const double dx, const double dy, const double dz)->auto {auto t = createBox(ax, dx, dy, dz); return std::move(t); }), "createBox");
		mod->add(chaiscript::fun([](const Pnt3d& pt, const double r)->auto{auto t = createSphere(pt, r); return std::move(t); }), "createSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, const double r)-> auto{auto t = createSphere(ax, r); return std::move(t); }), "createSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, const double r, const double ang1)->auto {auto t = createSphere(ax, r, ang1); return std::move(t); }), "createSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, const double r, const double ang1, const double ang2)->auto{auto t = createSphere(ax, r, ang1, ang2); return std::move(t); }), "createSphere");
		mod->add(chaiscript::fun([](const gp_Ax2& ax, const double r, const double ang1, const double ang2, const double ang3)->auto{auto t = createSphere(ax, ang1, ang2, ang3); return std::move(t); }), "createSphere");

		
	}


}

using namespace tnbLib;

int main(int argc, char *argv[])
{
	gMaker->CreateHullMaker();

}

