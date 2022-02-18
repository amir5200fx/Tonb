#include <Cad2d_SubdivideCrvs.hxx>
#include <Cad2d_CrvsIntsct.hxx>
#include <Cad2d_BruteForceSearchCrv.hxx>
#include <Pln_Edge.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Pln_Edge::extension + "list";
	static std::string saveExt = Pln_Edge::extension + "list";

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;
	static std::vector<std::shared_ptr<Pln_Edge>> mySubCurves;

	static bool loadTag = false;
	static bool exeTag = false;

	static double myTol = 1.0E-6;

	static std::string myFileName;

	static unsigned short verbose = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
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

		file::SaveTo(mySubCurves, name + saveExt, verbose);
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

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		if (myCurves.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been found." << endl
				<< abort(FatalError);
		}

		if (myCurves.size() < 2)
		{
			exeTag = true;
			return;
		}

		{
			auto engine = std::make_shared<Cad2d_BruteForceSearchCrv>();
			for (auto& x : myCurves)
			{
				engine->Insert(std::move(x));
			}

			auto intscAlg = std::make_shared<Cad2d_CrvsIntsct>(engine, myTol);
			intscAlg->Perform();
			Debug_If_Condition_Message(NOT intscAlg->IsDone(), "the application is not performed!");

			const auto& pairs = intscAlg->Entities();

			if (verbose)
			{
				Info << endl
					<< " - the detected number of entities: " << pairs.size() << endl;
			}
		
			auto subAlg = std::make_shared<Cad2d_SubdivideCrvs>(intscAlg->Entities(), myTol);
			Debug_Null_Pointer(subAlg);

			subAlg->Perform();
			
			mySubCurves.reserve(subAlg->SubEdges().size());
			for (const auto& x : subAlg->SubEdges())
			{
				const auto& subs = x.second;
				for (const auto& c : subs)
				{
					mySubCurves.push_back(c);
				}
			}

			if (verbose)
			{
				Info << endl
					<< " - the number of sub curves: " << mySubCurves.size() << endl;
			}
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setTolerance(x); }), "setTolerance");

		//- operators
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
			Info << " This application is aimed to subdivide the curves that have an intersection with each other." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< " - setTolerance(double)" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneSubdivideIntsctCrvs"));

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