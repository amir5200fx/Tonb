#include <Marine_BodyModelType.hxx>
#include <Marine_ShapeIO.hxx>
#include <OpenCascade_Serialization.hxx>
#include <Geo_Serialization.hxx>
#include <Cad2d_RemoveNonManifold.hxx>
#include <Cad_Tools.hxx>
#include <Cad_Shape.hxx>
#include <Entity3d_Box.hxx>
#include <Geo_BoxTools.hxx>
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
#include <Poly_Triangulation.hxx>

#include <memory>

namespace tnbLib
{

	static bool loadTag = false;
	static bool bodyTypeTag = false;
	static bool exeTag = false;

	static Marine_BodyModelType myBodyType;
	static std::shared_ptr<Cad_Shape> myHull;
	static Entity3d_Box myBoundingBox;

	static unsigned short verbose(0);
	static const double DEFAULT_TOL = 1.0E-6;

	static auto myTol = DEFAULT_TOL;

	static gp_Ax2d myAxis = gp::OY2d();

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << " - the tolerance is set to: " << x << endl;
			Info << endl;
		}
	}

	void setLoc(double x)
	{
		myAxis.SetLocation(gp_Pnt2d(x, 0));
		if (verbose)
		{
			Info << " - the XZ-Plane location is set to: " << x << endl;
			Info << endl;
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
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

	//void loadModel1(const std::string& name)
	//{
	//	fileName fn(name);
	//	if (verbose)
	//	{
	//		Info << endl;
	//		Info << " loading the model from, " << fn << endl;
	//		Info << endl;
	//	}
	//	std::ifstream myFile(fn);

	//	{//- timer scope
	//		Global_Timer timer;
	//		timer.SetInfo(Global_TimerInfo_ms);

	//		TNB_iARCH_FILE_TYPE ar(myFile);
	//		ar >> myHull;
	//		std::cout << "1" << std::endl;
	//		ar >> myBoundingBox;
	//		std::cout << "2" << std::endl;
	//		ar >> myBodyType;
	//		std::cout << "3" << std::endl;
	//		ar >> myAxis;
	//		std::cout << "4" << std::endl;
	//		ar >> myTol;
	//		std::cout << "5" << std::endl;
	//	}

	//	if (NOT myHull)
	//	{
	//		FatalErrorIn(FunctionSIG)
	//			<< " the loaded model is null" << endl
	//			<< abort(FatalError);
	//	}

	//	if (verbose)
	//	{
	//		Info << endl;
	//		Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
	//		Info << endl;
	//	}

	//	loadTag = true;
	//}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the algorithm has not been performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		auto myShape = std::make_shared<marineLib::io::Shape>();
		myShape->LoadShape(myHull);
		myShape->LoadPreciseBndBox(std::make_shared<Entity3d_Box>(myBoundingBox));
		myShape->SetAx(myAxis);
		myShape->SetTol(myTol);
		myShape->SetType(myBodyType);

		ar << myShape;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
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
		myBodyType = Marine_BodyModelType::symm;
		if (std::abs(xo - Y0(b)) <= myTol * std::abs(Y0(b) - Y1(b))) return true;
		//if (xo > Y1(b)) return true;
		auto ym = MEAN(Y0(b), Y1(b));
		myBodyType = Marine_BodyModelType::full;
		return (std::abs(ym - xo) <= myTol * std::abs(Y0(b) - Y1(b)));
	}

	auto retrievePoints(const Poly_Triangulation& p)
	{
		const auto& nodes = p.Nodes();
		std::vector<Pnt3d> pts;
		pts.reserve(nodes.Size());
		for (const auto& x : nodes)
		{
			auto pt = Pnt3d(x);
			pts.push_back(std::move(pt));
		}
		return std::move(pts);
	}
	auto calcBoundingBox(const TopoDS_Shape& s)
	{
		auto surfaces = Cad_Tools::RetrieveTriangulation(s);
		if (surfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no triangulated surface has been found!" << endl
				<< abort(FatalError);
		}

		auto iter = surfaces.begin();
		auto points = retrievePoints(*iter);
		/*double yMin = RealLast();
		for (const auto& x : points)
		{
			if (x.Y() < yMin) yMin = x.Y();
		}*/
		auto b = Geo_BoxTools::GetBox(points, 0);
		iter++;
		while (iter NOT_EQUAL surfaces.end())
		{
			auto points = retrievePoints(*iter);
			/*for (const auto& x : points)
			{
				if (x.Y() < yMin) yMin = x.Y();
			}*/
			b = Geo_BoxTools::Union(b, Geo_BoxTools::GetBox(points, 0));
			iter++;
		}
		//std::cout << "yMin= " << yMin << std::endl;
		return std::move(b);
	}

	void execute()
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

		const TopoDS_Shape& h = myHull->Shape();
		if (h.IsNull())
		{
			FatalErrorIn(FunctionSIG)
				<< "the model is empty!" << endl
				<< abort(FatalError);
		}

		myBoundingBox = calcBoundingBox(h);

		if (verbose > 1)
		{
			Info << " - bounding box of the body: " << myBoundingBox << endl;
			Info << endl;
		}

		if (NOT isValidSimulation(myBoundingBox))
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
			Info << " the detected type of body: " << (myBodyType IS_EQUAL Marine_BodyModelType::full ? "Full Body" : "Symm Body") << endl;
			Info << endl;
		}

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
		//mod->add(chaiscript::fun([](const std::string& name)->void {loadModel1(name); }), "loadModel1");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](double x)-> void {setTolerance(x); }), "setTol");
		mod->add(chaiscript::fun([](double x)->void {setLoc(x); }), "setXZPlane");
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");

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
			Info << " Function list:" << endl;
			Info << " - loadModel(string)" << endl;
			Info << " - saveTo(string)" << endl << endl;
			Info << " - setTol(double)" << endl;
			Info << " - setXZPlane(double)" << endl;
			Info << " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl;
			Info << " - execute()" << endl;
			Info << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("hydstcShapeReader");

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