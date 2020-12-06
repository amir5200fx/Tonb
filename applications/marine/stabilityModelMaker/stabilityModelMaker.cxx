#include <Dir3d.hxx>
#include <Geo_xDistb.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Geo_Tools.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad2d_Modeler_Tools.hxx>
#include <Cad_ShapeTools.hxx>
#include <Cad_Tools.hxx>
#include <Cad_FastDiscrete.hxx>
#include <CadIO_IGES.hxx>
#include <CadIO_STEP.hxx>
#include <Marine_Shapes.hxx>
#include <StbGMaker_Edge.hxx>
#include <StbGMaker_WP.hxx>
#include <StbGMaker_ShapeTools.hxx>
#include <StbGMaker_Creator.hxx>
#include <StbGMaker_HullCreators.hxx>
#include <StbGMaker_TankCreators.hxx>
#include <StbGMaker_SailCreators.hxx>
#include <StbGMaker_Model.hxx>
#include <FastDiscrete_Params.hxx>

#include <Bnd_Box.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS_Shape.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <gp_Elips2d.hxx>
#include <gp_Circ2d.hxx>
#include <gp_Parab2d.hxx>
#include <gp_Hypr2d.hxx>
#include <Poly_Triangulation.hxx>


namespace tnbLib
{

	static const double tol = 1.0E-4;
	static const auto gMaker = std::make_shared<StbGMaker_Creator>();
	static const auto disctInfo = std::make_shared<FastDiscrete_Params>();
	static const auto curveDisctInfo = std::make_shared<Geo_ApprxCurve_Info>();


	typedef std::shared_ptr<StbGMaker_Creator> creator_t;
	typedef std::shared_ptr<marineLib::Shape_Tank> tank_t;
	typedef std::shared_ptr<marineLib::Shape_Sail> sail_t;
	typedef std::shared_ptr<marineLib::Shape_Hull> hull_t;

	typedef std::shared_ptr<StbGMaker_HullCreator> hullCreator_t;
	typedef std::shared_ptr<StbGMaker_SailCreator> sailCreator_t;
	typedef std::shared_ptr<StbGMaker_TankCreator> tankCreator_t;

	typedef std::shared_ptr<StbGMaker_WP> wp_t;

	typedef std::shared_ptr<Geo_xDistb> xDisbt_t;
	typedef std::shared_ptr<Geo_ApprxCurve_Info> apprxCurveInfo_t;

	typedef std::shared_ptr<Pln_Edge> edge_t;
	typedef std::shared_ptr<Pln_Ring> ring_t;

	//- global functions

	const auto& getCurveDiscrtInfo()
	{
		return curveDisctInfo;
	}

	const auto& getDiscrtInfo()
	{
		return disctInfo;
	}

	//
	//- set the triangulation parameters
	//
	void setAngle(const std::shared_ptr<FastDiscrete_Params>& par, const double angl)
	{
		par->Angle = angl;
	}

	void setDeflection(const std::shared_ptr<FastDiscrete_Params>& par, const double def)
	{
		par->Deflection = def;
	}

	void setMinSize(const std::shared_ptr<FastDiscrete_Params>& par, const double x)
	{
		par->MinSize = x;
	}

	void setParallel(const std::shared_ptr<FastDiscrete_Params>& par, const double p)
	{
		par->InParallel = p;
	}

	void setDefault(const std::shared_ptr<FastDiscrete_Params>& par)
	{
		par->Angle = 0.15;
		par->Deflection = 0.01;
		par->MinSize = Precision::Confusion();
		par->InParallel = Standard_True;
	}

	void setAngle(const apprxCurveInfo_t& t, const double ang)
	{
		t->SetAngle(ang);
	}

	void setApprox(const apprxCurveInfo_t& t, const double x)
	{
		t->SetApprox(x);
	}

	void setMinSize(const apprxCurveInfo_t& t, const double x)
	{
		t->SetMinSize(x);
	}

	void setMaxNbDivisions(const apprxCurveInfo_t& t, int n)
	{
		n = std::max(n, 5);
		t->SetMaxNbSubdivision(n);
	}

	void setInitNbDivisions(const apprxCurveInfo_t& t, int n)
	{
		n = std::max(n, 2);
		t->SetInitNbSubdivision(n);
	}

	void setNbSamples(const apprxCurveInfo_t& t, int n)
	{
		n = std::max(n, 3);
		t->SetNbSamples(n);
	}

	void setDefaults(const apprxCurveInfo_t& t)
	{
		t->SetAngle(Geo_ApprxCurve_Info::DEFAULT_ANGLE);
		t->SetApprox(Geo_ApprxCurve_Info::DEFAULT_APPROX);
		t->SetInitNbSubdivision(Geo_ApprxCurve_Info::DEFAULT_INIT_NB_SUBDIVIDE);
		t->SetMaxNbSubdivision(Geo_ApprxCurve_Info::DEFAULT_MAX_NB_SUBDIVIDE);
		t->SetMinSize(Geo_ApprxCurve_Info::DEFAULT_MIN_SIZE);
		t->SetNbSamples(Geo_ApprxCurve_Info::DEFAULT_NB_SAMPLES);
	}

	//- end of the triangulation parameters

	auto boundingBox(const TopoDS_Shape& s)
	{
		auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(s));
		return std::move(b);
	}

	auto diaSize(const TopoDS_Shape& s)
	{
		auto b = boundingBox(s);
		return b.Diameter();
	}

	void triangulationShape(const TopoDS_Shape& s)
	{
		Cad_FastDiscrete::Triangulation(s, *disctInfo);
	}

	void autoTriangulation(const TopoDS_Shape& s, const double w)
	{
		auto r = diaSize(s);
		setDeflection(getDiscrtInfo(), w*r);
		triangulationShape(s);
	}

	auto getTriangulation(const TopoDS_Shape& s)
	{
		auto poly = Cad_Tools::RetrieveTriangulation(s);
		std::vector<std::shared_ptr<Entity3d_Triangulation>> tris;
		for (const auto& x : poly)
		{
			if (x)
			{
				tris.push_back(Cad_Tools::Triangulation(x));
			}
		}
		return std::move(tris);
	}

	const auto& getMaker()
	{
		return gMaker;
	}

	const auto& getHull()
	{
		return getMaker()->HullMaker();
	}

	const auto& createHullMaker()
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

	const auto& createHullMaker(const hull_t& t)
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

	auto createTankMaker()
	{
		auto t = getMaker()->SelectTankMaker(getMaker()->CreateTankMaker());
		return std::move(t);
	}

	auto createTankMaker(const tank_t& t)
	{
		auto item = getMaker()->SelectTankMaker(getMaker()->CreateTankMaker(t));
		return std::move(item);
	}

	auto createSailMaker()
	{
		auto t = getMaker()->SelectSailMaker(getMaker()->CreateShapeGeomSailMaker());
		return std::move(t);
	}

	auto createSailMaker(const sail_t& s)
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

	// Create Working Planes

	auto createWP(const hullCreator_t& m, const double x)
	{
		auto t = m->SelectWP(m->CreateWorkingPlane(x));
		return std::move(t);

	}

	auto createWP(const tankCreator_t& m, const double x)
	{
		auto t = m->SelectWP(m->CreateWorkingPlane(x));
		return std::move(t);
	}

	auto createWP(const sailCreator_t& m, const double x)
	{
		auto volumetric = std::dynamic_pointer_cast<StbGMaker_VolumeSailCreator>(m);
		if (!volumetric)
		{
			FatalErrorIn(FunctionSIG)
				<< "the sail creator is not volumetric." << endl
				<< abort(FatalError);
		}
		auto t = volumetric->SelectWP(volumetric->CreateWorkingPlane(x));
		return std::move(t);
	}

	void createWPs(const hullCreator_t& m, const std::shared_ptr<Geo_xDistb>& dist)
	{
		m->CreateWorkingPlanes(*dist);
	}

	void createWPs(const tankCreator_t& m, const std::shared_ptr<Geo_xDistb>& dist)
	{
		m->CreateWorkingPlanes(*dist);
	}

	void createWPs(const sailCreator_t& m, const std::shared_ptr<Geo_xDistb>& dist)
	{
		auto volumetric = std::dynamic_pointer_cast<StbGMaker_VolumeSailCreator>(m);
		if (!volumetric)
		{
			FatalErrorIn(FunctionSIG)
				<< "the sail creator is not volumetric." << endl
				<< abort(FatalError);
		}
		volumetric->CreateWorkingPlanes(*dist);
	}


	//- discretization of the curves

	void uniformDiscretize(const edge_t& e, int n)
	{
		const auto& geom = e->Curve()->Geometry();
		auto mesh = Pln_Tools::UniformDiscrete(geom, std::max(n, 5));
		e->Mesh() = std::move(mesh);
	}

	void discretize(const edge_t& e)
	{
		e->Approx(getCurveDiscrtInfo());
	}

	void discretize(const wp_t& wp, int n)
	{
		const auto& modeler = wp->Modeler();
		const auto& edges = modeler->Edges();
		for (const auto& x : edges)
		{
			discretize(x.second);
			wp->Approx(x.second);
		}
	}

	auto getMesh(const wp_t& wp)
	{
		auto t = wp->MakeMesh();
		return std::move(t);
	}

	//- spacing functions


	

	//- io functions

	/*void exportToPlt(const wp_t& wp, const fileName& name)
	{
		
	}*/

	void exportToPlt(const std::shared_ptr<Entity3d_Triangulation>& t, const fileName& name)
	{
		OFstream f(name);
		t->ExportToPlt(f);
	}

	void exportToPlt(const TopoDS_Shape& sh, const fileName& name)
	{
		OFstream f(name);
		auto tris = getTriangulation(sh);
		for (const auto&x : tris)
		{
			Debug_Null_Pointer(x);
			x->ExportToPlt(f);
		}
	}

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

	/*void createSegment(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto geom = cad2dLib::Modeler_Tools::MakeSegment(p0, p1);
		wp->Modeler()->Import(std::move(geom));
	}*/
	
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
		return Dir3d(0, 0, 0);
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
		return gp_Ax2(pt, dir);
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
		return TopoDS_Shape();
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
		return TopoDS_Shape();
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
		return TopoDS_Shape();
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
		return TopoDS_Shape();
	}

	TopoDS_Shape createSphere(const Pnt3d& pt, const double r)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(pt, r);
			return std::move(sphere);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		return TopoDS_Shape();
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r);
			return std::move(sphere);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		return TopoDS_Shape();
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r, const double ang1)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r, ang1);
			return std::move(sphere);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		return TopoDS_Shape();
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r, const double ang1, const double ang2)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r, ang1, ang2);
			return std::move(sphere);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		return TopoDS_Shape();
	}

	TopoDS_Shape createSphere(const gp_Ax2& ax, const double r, const double ang1, const double ang2, const double ang3)
	{
		try
		{
			auto sphere = Cad_ShapeTools::Sphere(ax, r, ang1, ang2, ang3);
			return std::move(sphere);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn("TopoDS_Shape createSphere()")
				<< x.GetMessageString() << endl
				<< abort(FatalError);
		}
		return TopoDS_Shape();
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

	std::shared_ptr<Geo_xDistb> createUniformDistb(const double x0, const double x1, const int n)
	{
		auto d = std::make_shared<Geo_UniDistb>(n);
		d->SetLower(x0);
		d->SetUpper(x1);
		d->Perform();
		return std::move(d);
	}

	std::shared_ptr<Geo_xDistb> createCosineDistb(const double x0, const double x1, const int n)
	{
		auto d = std::make_shared<Geo_CosineDistb>(n);
		d->SetLower(x0);
		d->SetUpper(x1);
		d->Perform();
		return std::move(d);
	}

	// - spacing

	/*auto xBound(const TopoDS_Shape& s)
	{
		auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(s));
		auto t = b.Bound(0);
		return std::move(t);
	}*/

	std::shared_ptr<Geo_xDistb> createUniformDistb(const TopoDS_Shape& sh, int n, const double tol)
	{
		n = std::max(n, 3);
		auto b = boundingBox(sh);
		auto x0 = b.P0().X();
		auto x1 = b.P1().X();
		auto dx = x1 - x0;
		auto clip = tol * dx;
		x0 += clip;
		x1 -= clip;
		if (x1 <= x0)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid boundary values for a distribution profile" << endl
				<< abort(FatalError);
		}
		auto t = createUniformDistb(x0, x1, n);
		return std::move(t);
	}

	std::shared_ptr<Geo_xDistb> createCosineDistb(const TopoDS_Shape& sh, int n, const double tol)
	{
		n = std::max(n, 3);
		auto b = boundingBox(sh);
		auto x0 = b.P0().X();
		auto x1 = b.P1().X();
		auto dx = x1 - x0;
		auto clip = tol * dx;
		x0 += clip;
		x1 -= clip;
		if (x1 <= x0)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid boundary values for a distribution profile" << endl
				<< abort(FatalError);
		}
		auto t = createCosineDistb(x0, x1, n);
		return std::move(t);
	}

	//***** Working Planes' Functions:

	//Curves and edges:

	auto wpEdge(std::shared_ptr<Pln_Edge>&& edge)
	{
		auto e = std::make_shared<StbGMaker_Edge<Pln_Edge>>(std::move(*edge));
		return std::move(e);
	}

	auto wpEdge(std::shared_ptr<Pln_Ring>&& edge)
	{
		auto e = std::make_shared<StbGMaker_Edge<Pln_Ring>>(std::move(*edge));
		return std::move(e);
	}

	void createSegment(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1)
	{
		auto edge = cad2dLib::Modeler_Tools::MakeSegment(p0, p1);
		auto edge3 = wpEdge(std::move(edge));
		wp->Modeler()->Import(std::move(edge3));
	}

	 void createSegment(const wp_t& wp, const Pnt2d& p0, const double ang, const double l)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeSegment(p0, ang, l);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createCircArc(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircArc(p0, p1, p2);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createCircArc(const wp_t& wp, const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircArc(p0, v0, p1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	
	 void createCircArc(const wp_t& wp, const gp_Circ2d& c, const double ang0, const double ang1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircArc(c, ang0, ang1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createCircArc(const wp_t& wp, const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircArc(c, p0, p1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createElipsArc(const wp_t& wp, const gp_Elips2d& e, const double ang0, const double ang1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeElipsArc(e, ang0, ang1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createElipsArc(const wp_t& wp, const gp_Elips2d& e, const Pnt2d& p0, const Pnt2d& p1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeElipsArc(e, p0, p1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createHyprArc(const wp_t& wp, const gp_Hypr2d& h, const double ang0, const double ang1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeHyprArc(h, ang0, ang1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createHyprArc(const wp_t& wp, const gp_Hypr2d& h, const Pnt2d& p0, const Pnt2d& p1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeHyprArc(h, p0, p1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createParabArc(const wp_t& wp, const gp_Parab2d& par, const double ang0, const double ang1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeParbArc(par, ang0, ang1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createParabArc(const wp_t& wp, const gp_Parab2d& par, const Pnt2d& p0, const Pnt2d& p1)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeParabArc(par, p0, p1);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }
	
	 // Shapes:

	 void createCircle(const wp_t& wp, const gp_Circ2d& c)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircle(c);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 // a circle parallel to another circle and passing through a point:
	 void createCircle(const wp_t& wp, const gp_Circ2d& c, const Pnt2d& p0)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircle(c, p0);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createCircle(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircle(p0, p1, p2);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createCircle(const wp_t& wp, const Pnt2d& c, const double r)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircle(c, r);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createCircle(const wp_t& wp, const Pnt2d& c, const Pnt2d& p0)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeCircle(c, p0);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 void createEllipse(const wp_t& wp, const gp_Elips2d& e)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeEllipse(e);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 //! Make an Ellipse centered on the point Center, where
			//! -   the major axis of the ellipse is defined by Center and S1,
			//! -   its major radius is the distance between Center and S1, and
			//! -   its minor radius is the distance between S2 and the major axis.
			//! The implicit orientation of the ellipse is:
			//! -   the sense defined by Axis or E,
			//! -   the sense defined by points Center, S1 and S2,
			//! -   the trigonometric sense if Sense is not given or is true, or
			//! -   the opposite sense if Sense is false.

	 void createEllipse(const wp_t& wp, const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)
	 {
		 auto edge = cad2dLib::Modeler_Tools::MakeEllipse(s0, s1, c);
		 auto edge3 = wpEdge(std::move(edge));
		 wp->Modeler()->Import(std::move(edge3));
	 }

	 /*void createRectangular(const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1)
	 {
		 auto rec = cad2dLib::Modeler_Tools::MakeRectangular(p0, p1);
		 wp->Modeler()->Import(std::move(rec));
	 }

	 void createRectangular(const wp_t& wp, const gp_Ax2d& ax, const double dx, const double dy)
	 {
		 auto rec = cad2dLib::Modeler_Tools::MakeRectangular(ax, dx, dy);
		 wp->Modeler()->Import(std::move(rec));
	 }*/
	
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

		//- default values
		setDefault(getDiscrtInfo());

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->auto{auto t = importIges(name); return std::move(t); }), "importIGES");
		mod->add(chaiscript::fun([](const std::string& name)->auto{auto t = importStep(name); return std::move(t); }), "importSTEP");

		mod->add(chaiscript::fun([](const std::string& name)->const auto& {return importHullMakerFromIGES(name); }), "createHullFromIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> const auto& {return importHullMakerFromSTEP(name); }), "createHullFromSTEP");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importTankMakerFromIGES(name); return std::move(t); }), "createTankFromIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importTankMakerFromSTEP(name); return std::move(t); }), "createTankFromSTEP");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importSailMakerFromIGES(name); return std::move(t); }), "createSailFromIGES");
		mod->add(chaiscript::fun([](const std::string& name)-> auto {auto t = importSailMakerFromSTEP(name); return std::move(t); }), "createSailFromSTEP");

		mod->add(chaiscript::fun([]()-> auto {auto t = getMaker()->ExportModel(); return std::move(t); }), "createModel");

		mod->add(chaiscript::fun([](const TopoDS_Shape& sh, const std::string& name)->void {exportToPlt(sh, name); }), "exportToPlt");

		mod->add(chaiscript::fun([](const wp_t& wp, const std::string& name)->void {exportToPlt(wp, name); }))

		//- triangulation

		mod->add(chaiscript::fun([]()-> const auto& {return getDiscrtInfo(); }), "getDiscrtInfo");

		mod->add(chaiscript::fun([](const std::shared_ptr<FastDiscrete_Params>& par, const double v) ->void {setAngle(par, Geo_Tools::DegToRadian(v)); }), "setAngle");
		mod->add(chaiscript::fun([](const std::shared_ptr<FastDiscrete_Params>& par, const double v) ->void {setDeflection(par, v); }), "setDeflection");
		mod->add(chaiscript::fun([](const std::shared_ptr<FastDiscrete_Params>& par, const double v) ->void {setMinSize(par, v); }), "setMinSize");
		mod->add(chaiscript::fun([](const std::shared_ptr<FastDiscrete_Params>& par, const bool v) ->void {setParallel(par, v); }), "setParallel");
		mod->add(chaiscript::fun([](const std::shared_ptr<FastDiscrete_Params>& par)->void {setDefault(par); }), "setDefaults");

		mod->add(chaiscript::fun([](const TopoDS_Shape& sh)->void {triangulationShape(sh); }), "triangulation");
		mod->add(chaiscript::fun([](const TopoDS_Shape& sh, const double tol)->void {autoTriangulation(sh, tol); }), "triangulation");

		mod->add(chaiscript::fun([]()-> const auto& {return getCurveDiscrtInfo(); }), "getCurveDiscrtInfo");

		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p, const double x)->void {setAngle(p, x); }), "setAngle");
		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p, const double x)->void {setApprox(p, x); }), "setApprox");
		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p, const double x)->void {setMinSize(p, x); }), "setMinSize");
		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p, const int n)->void {setMaxNbDivisions(p, n); }), "setMaxNbDivisions");
		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p, const int n)->void {setInitNbDivisions(p, n); }), "setInitNbDivisions");
		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p, const int n)->void {setNbSamples(p, n); }), "setNbSamples");
		mod->add(chaiscript::fun([](const apprxCurveInfo_t& p)->void {setDefaults(p); }), "setDefaults");

		mod->add(chaiscript::fun([](const wp_t& wp)->void {discretize(wp, 20); }), "discretize");
		mod->add(chaiscript::fun([](const wp_t& wp, int n)->void {discretize(wp, n); }), "discretize");

		//- spacing

		mod->add(chaiscript::fun([](double x0, double x1, int n)->auto{auto t = createUniformDistb(x0, x1, n); return std::move(t); }), "createUniformSpacing");
		mod->add(chaiscript::fun([](double x0, double x1, int n)->auto{auto t = createCosineDistb(x0, x1, n); return std::move(t); }), "createCosineSpacing");
		mod->add(chaiscript::fun([](const TopoDS_Shape& sh, int n)-> auto {auto t = createUniformDistb(sh, n, tol); return std::move(t); }), "createUniformSpacing");
		mod->add(chaiscript::fun([](const TopoDS_Shape& sh, int n)-> auto {auto t = createCosineDistb(sh, n, tol); return std::move(t); }), "createCosineSpacing");

		//- shapes

		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{auto t = createHull(s); }), "createHullShape");
		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{auto t = createTank(s); }), "createTankShape");
		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{auto t = createSail(s); }), "createSailShape");

		mod->add(chaiscript::fun([](const TopoDS_Shape& s)->auto{return diaSize(s); }), "diaSize");
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

	void setCreators(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->const auto& {return createHullMaker(); }), "createHullMaker");
		mod->add(chaiscript::fun([](const hull_t& s)-> const auto& {return createHullMaker(s); }), "createHullMaker");

		mod->add(chaiscript::fun([]()-> auto {auto t = createTankMaker(); return std::move(t); }), "createTankMaker");
		mod->add(chaiscript::fun([](const tank_t& s)-> auto {auto t = createTankMaker(s); return std::move(t); }), "createTankMaker");

		mod->add(chaiscript::fun([]()->auto {auto t = createSailMaker(); return std::move(t); }), "createSailMaker");
		mod->add(chaiscript::fun([](const sail_t& s)-> auto {auto t = createSailMaker(s); return std::move(t); }), "createSailMaker");
	}

	void setWotkingPlanes(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const hullCreator_t& m, const double x)-> auto{auto t = createWP(m, x); return std::move(t); }), "createHullWP");
		mod->add(chaiscript::fun([](const tankCreator_t& m, const double x)->auto {auto t = createWP(m, x); return std::move(t); }), "createTankWP");
		mod->add(chaiscript::fun([](const sailCreator_t& m, const double x)->auto {auto t = createWP(m, x); return std::move(t); }), "createSailWP");

		mod->add(chaiscript::fun([](const hullCreator_t& m, const std::shared_ptr<Geo_xDistb>& d)->void {createWPs(m, d); }), "createHullWPs");
		mod->add(chaiscript::fun([](const tankCreator_t& m, const std::shared_ptr<Geo_xDistb>& d)->void {createWPs(m, d); }), "createHullWPs");
		mod->add(chaiscript::fun([](const sailCreator_t& m, const std::shared_ptr<Geo_xDistb>& d)->void {createWPs(m, d); }), "createHullWPs");

		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1)->void { createSegment(wp, p0, p1); }), "createSegment");
		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& p0, const double ang, const double l)-> void {createSegment(wp, p0, ang, l); }), "createSegment");

		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)->void {createCircArc(wp, p0, p1, p2); }), "createCircArc");
		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& p0, const Vec2d& v0, const Pnt2d& p1)-> void {createCircArc(wp, p0, v0, p1); }), "createCircArc");
		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Circ2d& c, const double ang0, const double ang1)->void {createCircArc(wp, c, ang0, ang1); }), "createCircArc");
		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Circ2d& c, const Pnt2d& p0, const Pnt2d& p1)->void {createCircArc(wp, c, p0, p1); }), "createCircArc");

		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Elips2d& e, const double ang0, const double ang1)-> void {createElipsArc(wp, e, ang0, ang1); }), "createElipArc");
		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Elips2d& e, const Pnt2d& p0, const Pnt2d& p1)-> void {createElipsArc(wp, e, p0, p1); }), "createElipArc");

		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Hypr2d& h, const double ang0, const double ang1)-> void {createHyprArc(wp, h, ang0, ang1); }), "createHyprArc");
		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Hypr2d& h, const Pnt2d& p0, const Pnt2d& p1)-> void {createHyprArc(wp, h, p0, p1); }), "createHyprArc");

		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Parab2d& p, const double ang0, const double ang1)-> void {createParabArc(wp, p, ang0, ang1); }), "createParabArc");
		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Parab2d& p, const Pnt2d& p0, const Pnt2d& p1)-> void {createParabArc(wp, p, p0, p1); }), "createParabArc");

		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Circ2d& c)-> void {createCircle(wp, c); }), "createCircle");
		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Circ2d& c, const Pnt2d& p0)-> void {createCircle(wp, c, p0); }), "createCircle");
		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2)-> void {createCircle(wp, p0, p1, p2); }), "createCircle");
		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& c, const double r)-> void {createCircle(wp, c, r); }), "createCircle");
		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& c, const Pnt2d& p0)-> void {createCircle(wp, c, p0); }), "createCircle");

		mod->add(chaiscript::fun([](const wp_t& wp, const gp_Elips2d& e)->void {createEllipse(wp, e); }), "createEllipse");
		mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& s0, const Pnt2d& s1, const Pnt2d& c)->void {createEllipse(wp, s0, s1, c); }), "createEllipse");

		//mod->add(chaiscript::fun([](const wp_t& wp, const Pnt2d& p0, const Pnt2d& p1)->void {createRectangular(wp, p0, p1); }), "createRectangular");
		//mod->add(chaiscript::fun([](const wp_t& wp, const gp_Ax2d& ax, const double dx, const double dy)-> void {createRectangular(wp, ax, dx, dy); }), "createRectangular");



	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}


using namespace tnbLib;

int main(int argc, char *argv[])
{
	FatalError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);
			setDefaultShapes(mod);
			setCreators(mod);
			setWotkingPlanes(mod);

			chai.add(mod);

			fileName myFileName("stbModelMaker");

			try
			{
				chai.eval_file(myFileName);
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}

