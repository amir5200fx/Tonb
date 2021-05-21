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
#include <Cad_ShapeSection.hxx>
#include <Cad_Tools.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <Bnd_Box.hxx>
#include <Geom2d_Curve.hxx>

#include <memory>

namespace tnbLib
{
	static bool loadTag = false;
	static bool bodyTypeTag = false;
	static bool makeShapeHull = true;

	static TopoDS_Shape myHull;
	static unsigned short verbose(0);

	static const unsigned int DEFAULT_NB_SECTIONS = 25;
	static const unsigned int DEFAULT_MIN_NB_SECTIONS = 10;
	static auto nbSections = DEFAULT_NB_SECTIONS;

	static std::string myDistbAlg = "uniform";

	static const double DEFAULT_MIN_TOL = 1.0E-4;
	static const double DEFAULT_MAX_TOL = 1.0E-3;

	static auto myMinTol = DEFAULT_MIN_TOL;
	static auto myMaxTol = DEFAULT_MAX_TOL;

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

		if (myHull.IsNull())
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

	auto calcBoundingBox(const TopoDS_Shape& shape)
	{
		auto b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(shape));
		return std::move(b);
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

	auto X0(const Entity3d_Box& b)
	{
		return b.P0().X();
	}

	auto X1(const Entity3d_Box& b)
	{
		return b.P1().X();
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

	auto retrieveSectionEdges(const TopoDS_Shape& shape, double x)
	{
		const auto edges = Cad_Tools::RetrieveEdges(shape);
		const auto ax2 = gp_Ax2(gp_Pnt(x, 0, 0), gp::DX(), gp::DY());
		const auto paraCurves = Cad_Tools::RetrieveParaCurves(edges, ax2);

		const auto plnCurves = Marine_SectTools::CurveCreator(paraCurves, Marine_SectionType::displacer);
	
		const auto compoundEdges = retrieveMergedEdges(plnCurves);

		checkBodyType(compoundEdges);

		switch (myBodyType)
		{
		case tnbLib::bodyType::full:
			return std::move(compoundEdges);
			break;
		case tnbLib::bodyType::symm:
		{
			const auto allPlnCurves = retrieveSymmSectionCurves(plnCurves);
			const auto allCompoundEdges = retrieveMergedEdges(allPlnCurves);
			return std::move(allCompoundEdges);
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

	auto retrieveSection(const TopoDS_Shape& shape, const gp_Ax2& ax2, double x)
	{
		const auto cmpEdges = retrieveSectionEdges(shape, x);
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

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT bodyTypeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no type of the body has been assigned!" << endl
				<< abort(FatalError);
		}

		if (myHull.IsNull())
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

		const auto b = calcBoundingBox(myHull);
		const auto d = b.Diameter();
		auto dist = calcDistrb(X0(b) + d * 1.0E-4, X1(b) - d * 1.0E-4, nbSections, myDistbAlg);

		const auto edges = retrieveShapeSections(*dist, myHull);

		const auto Oxyz = MarineBase_Tools::CalcOxyz(b);
		const auto ax2 = gp_Ax2(Oxyz, gp::DX());

		std::vector<std::shared_ptr<Marine_CmpSection>> sections;
		sections.reserve(edges.size());
		for (const auto& x : edges)
		{
			auto cmpSection = retrieveSection(x.first, ax2, x.second);
			sections.push_back(std::move(cmpSection));
		}

		if (makeShapeHull)
		{
			auto shape = std::make_shared<marineLib::Shape_Hull>(0, name, myHull);
			auto body = Marine_BodyTools::BodyCreator(sections, shape, Marine_BodyType::displacer);

			myBody = std::move(body);
		}
		else
		{
			auto body = Marine_BodyTools::BodyCreator(sections, Marine_BodyType::displacer);
			myBody = std::move(body);
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
		mod->add(chaiscript::fun([](int n)->void {nbSections = n; }), "setNbSections");
		mod->add(chaiscript::fun([](const std::string& name)->void {myDistbAlg = name; }), "setDistbAlg");
		mod->add(chaiscript::fun([](size_t t)->void {verbose = t; }), "setVerbose");

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

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("hullReader");

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