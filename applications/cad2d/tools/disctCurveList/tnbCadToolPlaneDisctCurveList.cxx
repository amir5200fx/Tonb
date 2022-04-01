#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Geo_ApprxCurve_System.hxx>
#include <Geo2d_ApprxCurve.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	auto& appxInfo = sysLib::gl_approx_curve2d_info;

	void setTarget(double x)
	{
		appxInfo->SetApprox(x);
	}

	void setAngle(double x)
	{
		appxInfo->SetAngle(x);
	}

	void setMinSize(double x)
	{
		appxInfo->SetMinSize(x);
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
	}

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;

	static std::string myFileName;
	static auto loadExt = Pln_Edge::extension + "list";
	static auto saveExt = Pln_Edge::extension + "list";

	static bool loadTag = false;
	static bool exeTag = false;
	static bool randPnt = true;
	static unsigned short verbose = 0;

	typedef std::shared_ptr<Geo_ApprxCurve<Handle(Geom2d_Curve), true>> randAppx_t;
	typedef std::shared_ptr<Geo_ApprxCurve<Handle(Geom2d_Curve), false>> uniAppx_t;

	static randAppx_t myRandAppx;
	static uniAppx_t myUniAppx;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	auto estimateD()
	{
		auto iter = myCurves.begin();
		auto box = (*iter)->BoundingBox(0);
		iter++;
		while (iter NOT_EQUAL myCurves.end())
		{
			box = Entity2d_Box::Union(box, (*iter)->BoundingBox(0));
			iter++;
		}
		return box.Diameter();
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myCurves = file::LoadFile<std::vector<std::shared_ptr<Pln_Edge>>>(name + loadExt, verbose);

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
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

		file::SaveTo(myCurves, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	void execute(const std::shared_ptr<Pln_Edge>& edge, const std::shared_ptr<Geo_ApprxCurve_Info>& myInfo)
	{
		const auto& curve = edge->Curve();
		if (NOT curve)
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry is defined in the edge!" << endl
				<< abort(FatalError);
		}

		if (randPnt)
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			myRandAppx = std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), true>>
				(
					curve->Geometry(),
					curve->FirstParameter(),
					curve->LastParameter(),
					myInfo
					);
			myRandAppx->Perform();
			myUniAppx = nullptr;
		}
		else
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			myUniAppx = std::make_shared<Geo_ApprxCurve<Handle(Geom2d_Curve), false>>
				(
					curve->Geometry(),
					curve->FirstParameter(),
					curve->LastParameter(),
					myInfo
					);
			myUniAppx->Perform();
			myRandAppx = nullptr;
		}
		if (verbose)
		{
			Info << endl;
			Info << " - time estimation: " << global_time_duration << " ms" << endl;
			Info << endl;

			if (myRandAppx)
			{
				Info << " - nb. of points: " << myRandAppx->Chain()->NbPoints() << endl;
			}
			if (myUniAppx)
			{
				Info << " - nb. of points: " << myUniAppx->Chain()->NbPoints() << endl;
			}
		}

		if (myRandAppx)
		{
			edge->Mesh() = myRandAppx->Chain();
		}

		if (myUniAppx)
		{
			edge->Mesh() = myUniAppx->Chain();
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			printInfo();
		}

		auto myInfo = appxInfo;
		const auto d = estimateD();

		myInfo->SetApprox(appxInfo->Approx()*d);
		myInfo->SetMinSize(appxInfo->MinSize()*d);

		{// time scope [2/13/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
			for (const auto& x : myCurves)
			{
				if (NOT x)
				{
					FatalErrorIn(FunctionSIG)
						<< "the edge is a null pointer." << endl
						<< abort(FatalError);
				}
				execute(x, myInfo);
			}
		}

		if (verbose)
		{
			Info << endl;
			Info << " - total time estimation: " << global_time_duration << " ms" << endl;
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
			Info << " This application is aimed to discretize a planar curve." << endl;
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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneDisctCurveList"));

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