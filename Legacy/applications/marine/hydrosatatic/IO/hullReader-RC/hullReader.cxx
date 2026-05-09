#include <Marine_CmpSection.hxx>
#include <Marine_SectTools.hxx>
#include <MarineBase_Tools.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_Shapes.hxx>
#include <OpenCascade_Serialization.hxx>
#include <Cad2d_RemoveNonManifold.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad_ShapeSection.hxx>
#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <gp_Lin2d.hxx>
#include <gp_Lin.hxx>
#include <gp_Pnt.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <Bnd_Box.hxx>
#include <Geom2d_Curve.hxx>
#include <ProjLib.hxx>


#include <memory>

namespace tnbLib
{
	static bool loadTag = false;
	static bool bodyTypeTag = false;
	static bool makeShapeHull = true;

	static std::shared_ptr<Cad_Shape> myHull;
	static unsigned short verbose(0);

	static const unsigned int DEFAULT_NB_SECTIONS = 25;
	static const unsigned int DEFAULT_MIN_NB_SECTIONS = 10;
	static auto nbSections = DEFAULT_NB_SECTIONS;

	static std::string myDistbAlg = "uniform";

	static const double DEFAULT_MIN_TOL = 1.0E-4;
	static const double DEFAULT_MAX_TOL = 1.0E-3;
	static const double DEFAULT_TOL = 1.0E-6;

	static auto myMinTol = DEFAULT_MIN_TOL;
	static auto myMaxTol = DEFAULT_MAX_TOL;
	static auto myTol = DEFAULT_TOL;

	static int myNbPts = 5;

	static gp_Ax2d myAxis = gp::OY2d();

	typedef std::shared_ptr<Pln_Curve> curve_t;

	enum class bodyType
	{
		full,
		symm
	};

	static bodyType myBodyType;

	typedef std::shared_ptr<Marine_Body> body_t;

	static body_t myBody;

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> myHull;		
		}

		if (NOT myHull)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT myBody)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been created!" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myBody;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto calcDistance(const gp_Pnt2d& pt, const gp_Lin2d& line)
	{
		return line.Distance(pt);
	}

	auto calcD1D2(const curve_t& curve, const gp_Lin2d& line)
	{
		auto p0 = curve->FirstCoord();
		auto p1 = curve->LastCoord();

		auto d0 = line.Distance(p0);
		auto d1 = line.Distance(p1);

		auto t = std::make_pair(d0, d1);
		return std::move(t);
	}

	auto areOverlaped(const curve_t& curve, const gp_Lin2d& line, int nbPts, double eps)
	{
		const auto u0 = curve->FirstParameter();
		const auto u1 = curve->LastParameter();
		auto du = (u1 - u0) / (double)nbPts;
		for (int i = 0; i < nbPts; i++)
		{
			auto u = u0 + 0.5*du;
			auto pt = curve->Value(u);
			auto d = line.Distance(pt);

			if (d > eps) return false;
		}
		return true;
	}

	auto calcBoundingBox(const TopoDS_Shape& shape)
	{
		auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(shape));
		return std::move(b);
	}

	auto X0(const Entity3d_Box& b)
	{
		return std::min(b.P0().X(), b.P1().X());
	}

	auto X1(const Entity3d_Box& b)
	{
		return std::max(b.P0().X(), b.P1().X());
	}

	auto Y0(const Entity3d_Box& b)
	{
		return std::min(b.P0().Y(), b.P1().Y());
	}

	auto Y1(const Entity3d_Box& b)
	{
		return std::max(b.P0().Y(), b.P1().Y());
	}

	auto X0(const Entity2d_Box& b)
	{
		return std::min(b.P0().X(), b.P1().X());
	}

	auto X1(const Entity2d_Box& b)
	{
		return std::max(b.P0().X(), b.P1().X());
	}

	auto isValidSimulation(const Entity3d_Box& b)
	{
		const auto xo = myAxis.Location().X();
		bodyTypeTag = true;
		myBodyType = bodyType::symm;
		if (std::abs(xo - Y0(b)) <= myTol * std::abs(Y0(b) - Y1(b))) return true;
		//if (xo > Y1(b)) return true;
		auto ym = MEAN(Y0(b), Y1(b));
		myBodyType = bodyType::full;
		return (std::abs(ym - xo) <= myTol*std::abs(Y0(b) - Y1(b)));
	}



	auto retrieveFlipCurves(const std::vector<curve_t>& curves, double tol)
	{
		std::vector<curve_t> flipCurves;
		gp_Lin2d line(myAxis);
		gp_Trsf2d trans;
		trans.SetMirror(myAxis);
		for (const auto& x : curves)
		{
			if (NOT areOverlaped(x, line, myNbPts, tol))
			{
				auto g = Handle(Geom2d_Curve)::DownCast(x->Geometry()->Transformed(trans));
				auto c = std::make_shared<Pln_Curve>(0, "flipped " + x->Name(), std::move(g));
				flipCurves.push_back(std::move(c));
			}
		}
		return std::move(flipCurves);
	}

	std::shared_ptr<Geo_xDistb> calcDistrb(double x0, double x1, int n, const std::string& alg)
	{
		if (n < DEFAULT_MIN_NB_SECTIONS)
		{
			n = DEFAULT_MIN_NB_SECTIONS;
		}

		if (alg IS_EQUAL "uniform")
		{
			auto distb = std::make_shared<Geo_UniDistb>(n);
			distb->SetLower(x0);
			distb->SetUpper(x1);
			distb->Perform();
			return std::move(distb);
		}
		else if (alg IS_EQUAL "cosine")
		{
			auto distb = std::make_shared<Geo_CosineDistb>(n);
			distb->SetLower(x0);
			distb->SetUpper(x1);
			distb->Perform();
			return std::move(distb);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< " invalid algorithm for a geometric distribution has been detected!" << endl
				<< " algorithms: 'uniform', 'cosine'" << endl
				<< abort(FatalError);
		}
		return nullptr;
	}

	std::vector<std::pair<TopoDS_Shape, Standard_Real>> 
		retrieveShapeSections(const Geo_xDistb& dist, const TopoDS_Shape& shape)
	{
		gp_Dir dir(1, 0, 0);
		std::vector<std::pair<TopoDS_Shape, Standard_Real>> sections;
		sections.reserve(dist.Size());
		for (auto x : dist.Values())
		{
			gp_Pnt pt(x, 0, 0);		
			gp_Pln pln(pt, dir);

			Cad_ShapeSection alg(pln, shape);
			alg.Perform();

			const auto& section = alg.Section();
			if (section.IsNull())
			{
				continue;
			}
			auto paired = std::make_pair(std::move(section), x);
			sections.push_back(std::move(paired));
		}
		return std::move(sections);
	}

	void checkBodyType(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& segments)
	{
		switch (myBodyType)
		{
		case tnbLib::bodyType::full:
		{
			for (const auto& x : segments)
			{
				if (NOT x->IsRing())
				{
					FatalErrorIn(FunctionSIG)
						<< "invalid type of section has been detected!" << endl
						<< " Please check the body type of the application." << endl
						<< " the current setting is: " << (myBodyType IS_EQUAL bodyType::full ? "Full" : "Symmetry") << endl
						<< abort(FatalError);
				}
			}
			break;
		}
		case tnbLib::bodyType::symm:
		{
			//- do nothing
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unidentified type of body has been detected!" << endl
				<< abort(FatalError);
			break;
		}
	}

	auto retrieveSymmSectionCurves(const std::vector<std::shared_ptr<Pln_Curve>>& curves)
	{
		gp_Trsf2d tr;
		tr.SetMirror(gp::OY2d());
		std::vector<Handle(Geom2d_Curve)> gCurves;
		gCurves.reserve(curves.size());
		for (const auto& x : curves)
		{
			const auto& geometry = x->Geometry();
			auto copy = Handle(Geom2d_Curve)::DownCast(geometry->Transformed(tr));
			Debug_Null_Pointer(copy);
			gCurves.push_back(std::move(copy));
		}

		std::vector<std::shared_ptr<Pln_Curve>> allCurves;
		allCurves.reserve(2 * curves.size());
		for (const auto& x : curves)
		{
			allCurves.push_back(x);
		}
		for (const auto& x : Marine_SectTools::CurveCreator(gCurves, Marine_SectionType::displacer))
		{
			allCurves.push_back(x);
		}
		return std::move(allCurves);
	}

	auto retrieveMergedEdges(const std::vector<std::shared_ptr<Pln_Curve>>& plnCurves)
	{
		const auto b = Pln_Tools::BoundingBox(plnCurves);
		const auto d = b.Diameter();

		const auto minTol = d * myMinTol;
		const auto maxTol = d * myMaxTol;

		const auto mergedEdges = Pln_Tools::RetrieveMergedEdges(plnCurves, minTol, maxTol);

		Cad2d_RemoveNonManifold alg(mergedEdges);
		alg.Perform();

		const auto compoundEdges = alg.RetrieveCompundEdges();
		return std::move(compoundEdges);
	}

	auto repairFullSection(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& segments, double tol)
	{
		gp_Lin2d line(myAxis);
		std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> dangles;
		for (const auto& x : segments)
		{
			if (NOT x->IsRing())
			{
				const auto& n0 = x->Node0();
				const auto& n1 = x->Node1();

				auto d0 = calcDistance(n0->Vtx()->Coord(), line);
				auto d1 = calcDistance(n1->Vtx()->Coord(), line);

				if (d0 > tol AND d1 > tol)
				{
					dangles.push_back(x);
				}

				
			}
		}

		if (dangles.empty())
		{
			return std::shared_ptr<Pln_Curve>();
		}
		if (dangles.size() > 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid section  has been detected!" << endl
				<< abort(FatalError);
		}

		const auto& seg = segments[0];
		const auto& n0 = seg->Node0();
		const auto& n1 = seg->Node1();

		auto geom = Pln_CurveTools::MakeSegment(n0->Vtx()->Coord(), n1->Vtx()->Coord());
		auto curve = std::make_shared<Pln_Curve>(std::move(geom));
		return std::move(curve);
	}

	auto repairSymmSection(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& segments, double tol)
	{
		gp_Lin2d line(myAxis);
		std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> dangles;
		for (const auto& x : segments)
		{
			if (NOT x->IsRing())
			{
				const auto& n0 = x->Node0();
				const auto& n1 = x->Node1();

				auto d0 = calcDistance(n0->Vtx()->Coord(), line);
				auto d1 = calcDistance(n1->Vtx()->Coord(), line);

				if (d0 <= tol AND d1 <= tol)
				{
					continue;
				}

				if (d0 > tol AND d1 > tol)
				{
					FatalErrorIn(FunctionSIG)
						<< "invalid section has been detected!" << endl
						<< abort(FatalError);
				}

				dangles.push_back(x);
			}
		}
		if (dangles.empty())
		{
			return std::shared_ptr<Pln_Curve>();
		}
		if (dangles.size() > 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid section  has been detected!" << endl
				<< abort(FatalError);
		}
		const auto& seg = segments[0];
		const auto& n0 = seg->Node0();
		const auto& n1 = seg->Node1();

		const auto d0 = calcDistance(n0->Vtx()->Coord(), line);
		const auto d1 = calcDistance(n1->Vtx()->Coord(), line);

		if (d0 > tol)
		{
			const auto& coord = n0->Vtx()->Coord();
			auto pproj = Geo_Tools::ProjectToLine_cgal(coord, Geo_Tools::GetLine(line));

			auto geom = Pln_CurveTools::MakeSegment(coord, pproj);
			auto curve = Marine_SectTools::CurveCreator(geom, Marine_SectionType::displacer);
			return std::move(curve);
		}
		else if (d1 > tol)
		{
			const auto& coord = n1->Vtx()->Coord();
			auto pproj = Geo_Tools::ProjectToLine_cgal(coord, Geo_Tools::GetLine(line));

			auto geom = Pln_CurveTools::MakeSegment(coord, pproj);
			auto curve = Marine_SectTools::CurveCreator(geom, Marine_SectionType::displacer);
			return std::move(curve);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected situation has been detected!" << endl
				<< abort(FatalError);
		}
		return std::shared_ptr<Pln_Curve>();
	}

	auto retrieveSectionEdges(const TopoDS_Shape& shape, double x, double tol)
	{
		const auto edges = Cad_Tools::RetrieveEdges(shape);
		const auto ax2 = gp_Ax2(gp_Pnt(x, 0, 0), gp::DX(), gp::DY());
		const auto paraCurves = Cad_Tools::RetrieveParaCurves(edges, ax2);

		auto plnCurves = Marine_SectTools::CurveCreator(paraCurves, Marine_SectionType::displacer);

		const auto compoundEdges = retrieveMergedEdges(plnCurves);

		checkBodyType(compoundEdges);

		switch (myBodyType)
		{
		case tnbLib::bodyType::full:
		{
			if (auto deck = repairFullSection(compoundEdges, tol))
			{
				plnCurves.push_back(std::move(deck));

				const auto allCompoundEdges = retrieveMergedEdges(plnCurves);
				return std::move(allCompoundEdges);
			}
			else
			{
				return std::move(compoundEdges);
			}
			break;
		}
		case tnbLib::bodyType::symm:
		{
			if (auto deck = repairSymmSection(compoundEdges, tol))
			{
				plnCurves.push_back(std::move(deck));
				auto allPlnCurves = retrieveSymmSectionCurves(plnCurves);

				const auto allCompoundEdges = retrieveMergedEdges(allPlnCurves);
				return std::move(allCompoundEdges);
			}
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unidentified type of body has been detected!" << endl
				<< abort(FatalError);
			break;
		}
		return std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>();
	}

	auto retrieveWires(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& segments)
	{
		std::vector<std::shared_ptr<Pln_Wire>> wires;
		wires.reserve(segments.size());
		for (const auto& x : segments)
		{
			Debug_Null_Pointer(x->Node0());
			Debug_Null_Pointer(x->Node0()->Vtx());
			auto ring = Pln_Tools::RetrieveWire(x->Node0()->Vtx());
			wires.push_back(std::move(ring));
		}
		return std::move(wires);
	}

	auto retrieveSection(const TopoDS_Shape& shape, const gp_Ax2& ax2, double x, double tol)
	{
		const auto cmpEdges = retrieveSectionEdges(shape, x, tol);

		for (const auto& x : cmpEdges)
		{
			if (NOT x->IsRing())
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid section has been detected!" << endl
					<< " - the valid section must be watertight" << endl
					<< abort(FatalError);
			}
		}

		const auto wires = retrieveWires(cmpEdges);

		const auto sections = Marine_SectTools::SectionCreator(wires, ax2, Marine_SectionType::displacer);
		const auto cmpSection = Marine_SectTools::CmpSectionCreator(sections);
		Marine_SectTools::SetLocation(cmpSection, x);

		return std::move(cmpSection);
	}

	auto getCorners(const Entity3d_Box& b)
	{
		std::vector<Pnt3d> pts;
		pts.reserve(2);

		pts.push_back(b.P0());
		pts.push_back(b.P1());

		return std::move(pts);
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT myHull)
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is empty!" << endl
				<< abort(FatalError);
		}

		if (myMinTol > myMaxTol)
		{
			FatalErrorIn(FunctionSIG)
				<< "the minTol is bigger than the maxTol!" << endl
				<< "- minTol: " << myMinTol << endl
				<< "- maxTol: " << myMaxTol << endl
				<< abort(FatalError);
		}

		const TopoDS_Shape& h = myHull->Shape();
		if (h.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is empty!" << endl
				<< abort(FatalError);
		}

		auto b = calcBoundingBox(h);

		if (NOT isValidSimulation(b))
		{
			FatalErrorIn(FunctionSIG)
				<< "it's not a valid simulation: please check the XZ-plane" << endl
				<< abort(FatalError);
		}

		if (NOT bodyTypeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no type of the body has been assigned!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the detected type of body: " << (myBodyType IS_EQUAL bodyType::full ? "Full Body" : "Symm Body") << endl;
			Info << endl;
		}

		if (myBodyType IS_EQUAL bodyType::symm)
		{
			auto corners = getCorners(b);

			auto p0 = b.P0();
			auto p1 = b.P1();

			p0.Y() *= (-1.0);
			p1.Y() *= (-1.0);
			corners.push_back(std::move(p0));
			corners.push_back(std::move(p1));

			b = Entity3d_Box::BoundingBoxOf(corners);
		}
	
		const auto d = b.Diameter();
		auto dist = calcDistrb(X0(b) + d * 1.0E-4, X1(b) - d * 1.0E-4, nbSections, myDistbAlg);

		if (verbose)
		{
			Info << endl;
			Info << " the spacing algorithm is set to : " << myDistbAlg << endl;
			Info << " - nb. of sections: " << nbSections << endl;
			Info << endl;
		}

		if (verbose)
		{
			Info << endl;
			Info << " retrieving the intersection curves..." << endl;
			Info << endl;
		}
		const auto edges = retrieveShapeSections(*dist, h);

		const auto Oxyz = MarineBase_Tools::CalcOxyz(b);
		const auto ax2 = gp_Ax2(Oxyz, gp::DZ());
		const auto baseLine = gp_Ax1(Oxyz, gp::DX());

		const auto tol = myTol * std::abs(Y0(b) - Y1(b));

		if (verbose)
		{
			Info << endl;
			Info << " creating the sections..." << endl;
			Info << endl;
		}

		size_t k = 0;
		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(edges.size());
		for (const auto& x : edges)
		{
			if (verbose)
			{
				//Info << endl;
				Info << " creating the section nb. " << k++ << endl;
				//Info << endl;
			}
			auto cmpSection = retrieveSection(x.first, ax2, x.second, tol);
			sections.push_back(std::move(cmpSection));
		}

		if (verbose)
		{
			Info << endl;
			Info << " the sections are created, successfully!" << endl;
			Info << endl;
		}

		if (verbose)
		{
			Info << endl;
			Info << " the body maker is set to: " << (makeShapeHull IS_EQUAL true ? "TRUE" : "FALSE") << endl;
			Info << endl;
		}

		if (makeShapeHull)
		{
			auto shape = std::make_shared<marineLib::Shape_Hull>(0, name, h);
			if (myBodyType IS_EQUAL bodyType::symm)
			{
				shape->SetSymmetric(Standard_True);
			}
			auto body = Marine_BodyTools::BodyCreator(sections, shape, Marine_BodyType::displacer);

			myBody = std::move(body);
		}
		else
		{
			auto body = Marine_BodyTools::BodyCreator(sections, Marine_BodyType::displacer);
			myBody = std::move(body);
		}
		myBody->SetName(name);
		myBody->SetCoordinateSystem(ax2);
		myBody->SetBaseLine(baseLine);

		if (verbose)
		{
			Info << endl;
			Info << " the body is created, successfully!" << endl;
			Info << " - body's name: " << myBody->Name() << endl;
			Info << endl;
		}
	}

}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFunctions(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](double x)-> void {myMinTol = x; }), "setMinTol");
		mod->add(chaiscript::fun([](double x)-> void {myMaxTol = x; }), "setMaxTol");
		mod->add(chaiscript::fun([](double x)-> void {myTol = x; }), "setTol");
		mod->add(chaiscript::fun([](int n)->void {nbSections = n; }), "setNbSections");
		mod->add(chaiscript::fun([](double x)->void {myAxis.SetLocation(gp_Pnt2d(x, 0)); }), "setXZPlane");
		mod->add(chaiscript::fun([](const std::string& name)->void {myDistbAlg = name; }), "setDistbAlg");
		mod->add(chaiscript::fun([](bool c)->void {makeShapeHull = c; }), "useCad");
		mod->add(chaiscript::fun([](unsigned short t)->void {verbose = t; /*Cad2d_RemoveNonManifold::verbose = t;*/ }), "setVerbose");

		mod->add(chaiscript::fun([](const std::string& name)->void {execute(name); }), "execute");
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
	//FatalError.throwExceptions();

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

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("hydstcHullReader");

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
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
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