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
	static std::shared_ptr<Cad_Shape> myShape;
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
				<< "the application has not been performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);

		if (myBodyType IS_EQUAL Marine_BodyModelType::symm)
		{
			FatalErrorIn(FunctionSIG)
				<< "no symmetry type of the shape is acceptable!" << endl
				<< abort(FatalError);
		}

		auto shape = std::make_shared<marineLib::io::Shape>();
		shape->LoadShape(myShape);
		shape->LoadPreciseBndBox(std::make_shared<Entity3d_Box>(myBoundingBox));
		shape->SetAx(myAxis);
		shape->SetTol(myTol);
		shape->SetType(myBodyType);

		ar << shape;

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

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		myBoundingBox = *myShape->BoundingBox();

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
			Info << " This application is aimed to read a hydrostatic shape from a shape file." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setTol(double)" << endl
				<< " - setXZPlane(double)" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl
				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbHydstcShapeReader";
			fileName myFileName(address);

			try
			{
				chai.eval_file(myFileName);
				return 0;
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
	return 1;
}