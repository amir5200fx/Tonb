#include <Marine_BodyModelType.hxx>
#include <Marine_SectTools.hxx>
#include <Marine_PlnCurves.hxx>
#include <Marine_ShapeIO.hxx>
#include <Marine_SectionsIO.hxx>
#include <Cad_Shape.hxx>
#include <Cad_ShapeSection.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_UniDistb.hxx>
#include <Geo_CosineDistb.hxx>
#include <Geo_Serialization.hxx>
#include <OpenCascade_Serialization.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
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
#include <Bnd_Box2d.hxx>
#include <Geom2d_Curve.hxx>
#include <ProjLib.hxx>

#include <memory>

namespace tnbLib
{

	static bool loadTag = false;
	static bool bodyTypeTag = false;
	static bool exeTag = false;

	static const unsigned int DEFAULT_NB_SECTIONS = 25;
	static const unsigned int DEFAULT_MIN_NB_SECTIONS = 10;
	static auto nbSections = DEFAULT_NB_SECTIONS;

	static std::string myDistbAlg = "uniform";
	//static std::string mySectionType = "displacer";

	static unsigned short verbose(0);

	static auto myClipPerc = 1.0e-3;

	//static std::vector<std::shared_ptr<std::vector<std::shared_ptr<Pln_Edge>>>> myEdges;

	static std::shared_ptr<marineLib::io::Shape> myShape;
	static auto mySections = std::make_shared<marineLib::io::Sections>();

	auto myIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	class IntegInfoRunTime
	{

	public:

		IntegInfoRunTime()
		{
			Config();
		}

		static void Config();
	};

	static IntegInfoRunTime myIntegInfoObj;

	void IntegInfoRunTime::Config()
	{
		myIntegInfo->SetMaxNbIterations(500);
		myIntegInfo->SetNbInitIterations(5);
	}

	void printSettings()
	{
		Info << endl
			<< " - clip Perc.: " << myClipPerc << endl
			<< " - nb. of sections: " << nbSections << endl
			<< " - distribution: " << myDistbAlg << endl
			/*<< " - section type: " << mySectionType << endl*/;
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	/*void setSectionType(const std::string& name)
	{
		mySectionType = name;
		if (verbose)
		{
			Info << endl
				<< " - section type is set to: " << mySectionType << endl;
		}
	}*/

	void setNbSections(unsigned int n)
	{
		nbSections = (n < DEFAULT_MIN_NB_SECTIONS ? DEFAULT_MIN_NB_SECTIONS : n);
		nbSections = (n > 120 ? 120 : n);
		if (verbose)
		{
			Info << endl
				<< " - nb. of sections is set to: " << nbSections << endl;
		}
	}

	void setDistribution(const std::string& name)
	{
		myDistbAlg = name;
		if (verbose)
		{
			Info << endl
				<< " - distribution alg. is set to: " << myDistbAlg << endl;
		}
	}

	void setClipPerc(double x)
	{
		myClipPerc = (x < 0.0 ? 0.0 : x);
		myClipPerc = (x > 0.3 ? 0.3 : x);
		if (verbose)
		{
			Info << endl
				<< " - clip perc. is set to: " << myClipPerc << endl;
		}
	}

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

			ar >> myShape;
		}

		if (NOT myShape)
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
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the algorithm has not been performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		ar << mySections;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	auto getCorners(const Entity3d_Box& b)
	{
		std::vector<Pnt3d> pts;
		pts.reserve(2);

		pts.push_back(b.P0());
		pts.push_back(b.P1());

		return std::move(pts);
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

	auto retrieveSymmSectionCurves(const std::vector<Handle(Geom2d_Curve)>& curves)
	{
		gp_Trsf2d tr;
		tr.SetMirror(gp::OY2d());
		std::vector<Handle(Geom2d_Curve)> gCurves;
		gCurves.reserve(curves.size());
		for (const auto& x : curves)
		{
			auto copy = Handle(Geom2d_Curve)::DownCast(x->Transformed(tr));
			Debug_Null_Pointer(copy);
			gCurves.push_back(std::move(copy));
		}

		std::vector<Handle(Geom2d_Curve)> allCurves;
		allCurves.reserve(2 * curves.size());
		for (const auto& x : curves)
		{
			allCurves.push_back(x);
		}
		for (const auto& x : gCurves)
		{
			allCurves.push_back(x);
		}
		return std::move(allCurves);
	}

	auto removeDegeneracies(const std::vector<Handle(Geom2d_Curve)>& curves, double tol)
	{
		std::vector<Handle(Geom2d_Curve)> feasibles;
		for (const auto& x : curves)
		{
			myIntegInfo->SetTolerance(Pln_Tools::BoundingBox(Pln_Tools::BoundingBox(x)).Diameter()*1.0E-8);
			auto len = Pln_Tools::Length(*x, myIntegInfo);

			if (len > tol)
			{
				feasibles.push_back(x);
			}
		}
		return std::move(feasibles);
	}

	auto retrieveCurves(const TopoDS_Shape& shape, double x, double tol)
	{
		const auto edges = Cad_Tools::RetrieveEdges(shape);
		const auto ax2 = gp_Ax2(gp_Pnt(x, 0, 0), gp::DX(), gp::DY());
		auto paraCurves = Cad_Tools::RetrieveParaCurves(edges, ax2);

		paraCurves = removeDegeneracies(paraCurves, tol);

		if (myShape->ShapeType() IS_EQUAL Marine_BodyModelType::symm)
		{
			paraCurves = retrieveSymmSectionCurves(paraCurves);
		}

		std::vector<std::shared_ptr<Pln_Curve>> plnCurves;
		plnCurves.reserve(paraCurves.size());
		size_t k = 0;
		for (const auto& x : paraCurves)
		{
			auto c = std::make_shared<Pln_Curve>(x);
			c->SetIndex(++k);

			plnCurves.push_back(std::move(c));
		}
		/*if (mySectionType IS_EQUAL "displacer")
		{
			plnCurves = Marine_SectTools::CurveCreator(paraCurves, Marine_SectionType::displacer);
		}
		else if (mySectionType IS_EQUAL "tank")
		{
			plnCurves = Marine_SectTools::CurveCreator(paraCurves, Marine_SectionType::tank);
		}
		else if (mySectionType IS_EQUAL "sail")
		{
			plnCurves = Marine_SectTools::CurveCreator(paraCurves, Marine_SectionType::sail);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid type of section has been detected!" << endl
				<< " valid sections: displacer, tank and sail" << endl
				<< abort(FatalError);
		}*/
		
		auto plnEdges = Pln_Tools::RetrieveEdges(plnCurves);
		return std::move(plnEdges);
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
		if (verbose)
		{
			Info << endl
				<< " Retrieving sections..." << endl
				<< endl;
		}
		gp_Dir dir(1, 0, 0);
		std::vector<std::pair<TopoDS_Shape, Standard_Real>> sections;
		sections.reserve(dist.Size());
		{// timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			size_t k = 0;
			for (auto x : dist.Values())
			{
				if (verbose)
				{
					Info << " - section nb. " << k++ << " , x = " << x << endl;
				}
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
		}
		if (verbose)
		{
			Info << endl;
			Info << " - sections are retrieved from the shape, successfully, in: " << global_time_duration << " seconds."
				<< endl
				<< endl;
		}
		return std::move(sections);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is empty!" << endl
				<< abort(FatalError);
		}

		/*if (NOT myHull->BoundingBox())
		{
			FatalErrorIn(FunctionSIG)
				<< "no bounding box has been detected!" << endl
				<< abort(FatalError);
		}*/
		auto b = *myShape->PreciseBndBox();
		auto tol = myShape->Tolerance();

		if (myShape->ShapeType() IS_EQUAL Marine_BodyModelType::symm)
		{
			auto corners = getCorners(b);

			auto p0 = b.P0();
			auto p1 = b.P1();

			p0.Y() *= (-1.0);
			p1.Y() *= (-1.0);
			corners.push_back(std::move(p0));
			corners.push_back(std::move(p1));

			b = Entity3d_Box::BoundingBoxOf(corners);

			myShape->LoadPreciseBndBox(std::make_shared<Entity3d_Box>(b));
		}

		const auto totLen = X1(b) - X0(b);
		auto dist = calcDistrb(X0(b) + totLen * myClipPerc, X1(b) - totLen * myClipPerc, nbSections, myDistbAlg);

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
		const auto shapes = retrieveShapeSections(*dist, myShape->GetShape()->Shape());

		auto& myEdges = mySections->GetSectionsRef();
		myEdges.reserve(shapes.size());
		for (const auto& x : shapes)
		{
			auto section = std::make_shared<marineLib::io::Sections::Section>();
			section->EdgesRef() = retrieveCurves(x.first, x.second, tol*(std::abs(Y1(b) - Y0(b))));
			section->SetX(x.second);

			myEdges.push_back(std::move(section));
		}

		mySections->LoadShape(myShape);

		exeTag = true;
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
		mod->add(chaiscript::fun([]()-> void {printSettings(); }), "printSettings");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name)->void {setDistribution(name); }), "setSpacing");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {setSectionType(name); }), "setSectionType");
		mod->add(chaiscript::fun([](int n)->void {setNbSections(n); }), "setNbSections");
		mod->add(chaiscript::fun([](double x)-> void {setClipPerc(x); }), "setClipPerc");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
			Info << endl;
			Info << " This application is aimed to retrieve the sections from the shape." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setClipPerc(double);         - the value of the clip must be between 0 and 0.3" << endl
				<< " - setNbSections(int);          - the allowed min. nb. of sections is " << DEFAULT_MIN_NB_SECTIONS << endl
				<< "                                - the allowed max. nb. of sections is 120" << endl << endl

				<< " - setSpacing(string);          - two methods are defined: uniform and cosine" << endl
				/*<< " - setSectionType(string);      - three section types are defined: displacer, tank and sail" << endl*/
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - printSettings()" << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\hydstcShapeSections";
			fileName myFileName(address);

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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}