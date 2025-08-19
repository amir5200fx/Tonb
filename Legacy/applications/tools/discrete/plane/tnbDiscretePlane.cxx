#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Edge.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Geo_ApprxCurve_System.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string extension = Cad2d_Plane::extension;

	typedef std::shared_ptr<Pln_Curve> curve_t;
	typedef std::shared_ptr<Pln_Edge> edge_t;
	typedef std::shared_ptr<Geo_ApprxCurve<Handle(Geom2d_Curve), true>> randAppx_t;
	typedef std::shared_ptr<Geo_ApprxCurve<Handle(Geom2d_Curve), false>> uniAppx_t;

	static randAppx_t myRandAppx;
	static uniAppx_t myUniAppx;

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Cad2d_Plane> myPln;
	static std::string myFileName;

	auto appxInfo = sysLib::gl_approx_curve2d_info;

	static double d;
	static bool randPnt = true;

	static double myTargetSize = 1.0E-2;
	static double myMinSize = 1.0E-4;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTarget(double x)
	{
		myTargetSize = x;
	}

	void setAngle(double x)
	{
		appxInfo->SetAngle(x);
	}

	void setMinSize(double x)
	{
		myMinSize = x;
	}

	void setMaxNbSubdivision(int n0)
	{
		auto n = std::max(1, n0);
		appxInfo->SetMaxNbSubdivision(n);
	}

	void setInitNbSubdivision(int n0)
	{
		auto n = std::max(1, n0);
		appxInfo->SetInitNbSubdivision(n);
	}

	void setNbSamples(int n0)
	{
		auto n = std::max(1, n0);
		appxInfo->SetNbSamples(n);
	}

	void printInfo()
	{
		Info << " - nb. of samples: " << appxInfo->NbSamples() << endl;
		Info << " - nb. of initial subdivisions: " << appxInfo->InitNbSubdivision() << endl;
		Info << " - max. nb. of subdivisions: " << appxInfo->MaxNbSubdivision() << endl;
		Info << " - target size: " << appxInfo->Approx() << endl;
		Info << " - min. size: " << appxInfo->MinSize() << endl;
		Info << " - angle: " << appxInfo->Angle() << endl;

		Info << " - diameter: " << d << endl;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myFileName = name;
		myPln = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name + extension, verbose);

		auto b = myPln->OuterWire()->BoundingBox(0);
		d = b.Diameter();

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}

		file::SaveTo(myPln, name + extension, verbose);
	}

	void saveTo()
	{
		saveTo(myFileName);
	}

	auto mesh(const curve_t& myCurve)
	{
		if (randPnt)
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			myRandAppx = std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), true>>
				(
					myCurve->Geometry(),
					myCurve->FirstParameter(),
					myCurve->LastParameter(),
					appxInfo
					);
			myRandAppx->Perform();
			myUniAppx = nullptr;
			return myRandAppx->Chain();
			//myPolygons.push_back(myRandAppx->Chain());
		}
		else
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			myUniAppx = std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), false>>
				(
					myCurve->Geometry(),
					myCurve->FirstParameter(),
					myCurve->LastParameter(),
					appxInfo
					);
			myUniAppx->Perform();
			myRandAppx = nullptr;
			return myUniAppx->Chain();
			//myPolygons.push_back(myUniAppx->Chain());
		}
		
	}

	void mesh(const edge_t& e)
	{
		auto m = mesh(e->Curve());
		e->Mesh() = m;
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		appxInfo->SetApprox(myTargetSize * d);
		appxInfo->SetMinSize(myMinSize * d);

		if (verbose)
		{
			printInfo();
		}

		{	
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			std::vector<std::shared_ptr<Pln_Entity>> entities;
			myPln->RetrieveSegmentsTo(entities);

			for (const auto& x : entities)
			{
				if (auto e = std::dynamic_pointer_cast<Pln_Edge>(x))
				{
					mesh(e);
				}
			}
		}
		if (verbose)
		{
			Info << endl;
			Info << " - total time estimation: " << global_time_duration << " ms" << endl;
			Info << endl;
		}
		if (verbose)
		{
			Info << endl
				<< "- the application is performed, successfully!" << endl;
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
		// io functions [2/13/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// settings [2/13/2022 Amir]
		mod->add(chaiscript::fun([](double x)-> void {setAngle(x); }), "setAngle");
		mod->add(chaiscript::fun([](double x)-> void {setTarget(x); }), "setTargetSize");
		mod->add(chaiscript::fun([](double x)-> void {setMinSize(x); }), "setMinSize");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbSubdivision(n); }), "setMaxNbSubdivisions");
		mod->add(chaiscript::fun([](int n)-> void {setInitNbSubdivision(n); }), "setInitNbSubdivisions");
		mod->add(chaiscript::fun([](int n)-> void {setNbSamples(n); }), "setNbSamples");

		mod->add(chaiscript::fun([](unsigned short v)-> void {setVerbose(v); }), "setVerbose");

		// operators [2/13/2022 Amir]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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

int main(int argc, char* argv[])
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
			Info << endl;
			Info << " This application is aimed to discretize a Cad2d_Plane object." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - setAngle(double)" << endl
				<< " - setTargetSize(double)" << endl
				<< " - setMinSize(double)" << endl
				<< " - setMaxNbSubdivision(n)" << endl
				<< " - setInitNbSubdivision(n)" << endl
				<< " - setNbSamples(n)" << endl

				<< " # functions: " << endl << endl

				<< " - execute()" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbDiscretePlane"));

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