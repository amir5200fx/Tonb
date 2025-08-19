#include <PtdShapeFit2d_SingleScatterMap.hxx>
#include <Geo_AirfoilOffsets_S833.hxx>
#include <Geo_AirfoilOffsets_MH102.hxx>
#include <Geo_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit2d_ScatterMap> myScatterMap;
	static std::string mySelected = "MH102";

	static std::map<word, std::vector<Pnt2d>> ptsMap;

	class ScatterMapRunTime
	{

	public:

		ScatterMapRunTime()
		{
			SetConfigs();
		}

		void SetConfigs();
	};


	static unsigned short verbose = 0;
	static auto exeTag = false;

	static ScatterMapRunTime myScatterMapRunTimeObj;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setType(const std::string& name)
	{
		mySelected = name;
		if (verbose)
		{
			Info << endl
				<< " - the type is set to: " << mySelected << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myScatterMap, name + PtdShapeFit2d_ScatterMap::extension, verbose);
	}

	void printTypes()
	{
		for (const auto& x : ptsMap)
		{
			Info << " - " << x.first << endl;
		}
	}

	void execute()
	{
		if (ptsMap.find(mySelected) IS_EQUAL ptsMap.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "couldn't find the type: " << mySelected << endl
				<< "Please use the help to print the types. " << endl
				<< abort(FatalError);
		}
		myScatterMap = std::make_shared<PtdShapeFit2d_SingleScatterMap>(std::make_shared<std::vector<Pnt2d>>(ptsMap.at(mySelected)));

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}

		exeTag = true;
	}
}

void tnbLib::ScatterMapRunTime::SetConfigs()
{
	ptsMap.insert({ "MH102", geoLib::airfoilOffsetsLib::coords });
	ptsMap.insert({ "S833", geoLib::airfoilOffsetsLib::S833::coords });
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {printTypes(); }), "printTypes");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const std::string& name) -> void {setType(name); }), "setType");

		// Operators [2/11/2023 Payvand]
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
	//sysLib::init_gl_marine_integration_info();
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
			Info << " This application is aimed to create a specific scatter map for shape fitting." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name)" << endl
				<< " - printTypes()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setType(name)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

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

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitAirfoilTypedScatterMap"));
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}