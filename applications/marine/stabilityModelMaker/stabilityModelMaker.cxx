
#include <Dir3d.hxx>
#include <Geo_xDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Tools.hxx>
#include <Marine_Shapes.hxx>
#include <StbGMaker_WP.hxx>
#include <StbGMaker_ShapeTools.hxx>
#include <StbGMaker_Creator.hxx>
#include <StbGMaker_HullCreators.hxx>
#include <StbGMaker_TankCreators.hxx>
#include <StbGMaker_SailCreators.hxx>

#include <Standard_Failure.hxx>
#include <TopoDS_Shape.hxx>


namespace tnbLib
{

	static const Standard_Real tol = 1.0E-4;

	Pnt3d createPoint(const Standard_Real x, const Standard_Real y, const Standard_Real z)
	{
		Pnt3d pt(x, y, z);
		return std::move(pt);
	}

	Dir3d createDirection(const Standard_Real x, const Standard_Real y, const Standard_Real z)
	{
		try
		{
			Dir3d dir(x, y, z);
			return std::move(dir);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("Dir3d createDirection(const Standard_Real x, const Standard_Real y, const Standard_Real z)")
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

	TopoDS_Shape createCylinder(const gp_Ax2& ax, const Standard_Real r, const Standard_Real h)
	{
		try
		{
			auto cyl = Cad_ShapeTools::Cylinder(ax, r, h);
			return std::move(cyl);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createCylinder(const gp_Ax2& ax, const Standard_Real r, const Standard_Real h)")
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

	TopoDS_Shape createBox(const Pnt3d& p0, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz)
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

	TopoDS_Shape createBox(const gp_Ax2& ax, const Standard_Real dx, const Standard_Real dy, const Standard_Real dz)
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

	TopoDS_Shape createSphere(const Pnt3d& pt, const Standard_Real r)
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

	TopoDS_Shape createSphere(const gp_Ax2& ax, const Standard_Real r)
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

	TopoDS_Shape createSphere(const gp_Ax2& ax, const Standard_Real r, const Standard_Real ang1)
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

	TopoDS_Shape createSphere(const gp_Ax2& ax, const Standard_Real r, const Standard_Real ang1, const Standard_Real ang2)
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

	TopoDS_Shape createSphere(const gp_Ax2& ax, const Standard_Real r, const Standard_Real ang1, const Standard_Real ang2, const Standard_Real ang3)
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

	auto createUniformDistb(const Standard_Real x0, const Standard_Real x1, const Standard_Integer n)
	{
		auto d = std::make_shared<Geo_UniDistb>(n);
		d->SetLower(x0);
		d->SetUpper(x1);
		d->Perform();
		return std::move(d);
	}

	auto createCosineDistb(const Standard_Real x0, const Standard_Real x1, const Standard_Integer n)
	{
		auto d = std::make_shared<Geo_CosineDistb>(n);
		d->SetLower(x0);
		d->SetUpper(x1);
		d->Perform();
		return std::move(d);
	}

	typedef std::shared_ptr<StbGMaker_Creator> creator_t;
	typedef std::shared_ptr<marineLib::Shape_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Shape_Sail> sail_t;
	typedef std::shared_ptr<marineLib::Shape_Hull> hull_t;

	typedef std::shared_ptr<StbGMaker_HullCreator> hullCreator_t;
	typedef std::shared_ptr<StbGMaker_SailCreator> sailCreator_t;
	typedef std::shared_ptr<StbGMaker_TankCreator> tankCreator_t;

	typedef std::shared_ptr<Geo_xDistb> xDisbt_t;

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

	auto selectTankMaker(const creator_t& t, const Standard_Integer id)
	{
		auto item = t->SelectTankMaker(id);
		return std::move(item);
	}

	auto selectSailMaker(const creator_t& t, const Standard_Integer id)
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

int main(int argc, char *argv[])
{
	

}

