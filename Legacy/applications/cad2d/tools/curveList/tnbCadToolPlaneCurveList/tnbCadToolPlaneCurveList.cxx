#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{
	static std::string loadExt = Pln_Edge::extension;
	static std::string saveExt = Pln_Edge::extension + "list";

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;

	static bool verbose = false;
	static bool loadTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	auto loadFile(const std::string& name)
	{
		//file::CheckExtension(name);

		auto myCurve = file::LoadFile<std::shared_ptr<Pln_Edge>>(name + loadExt, verbose);
		return std::move(myCurve);
	}

	void loadFiles()
	{

		auto currentPath = boost::filesystem::current_path().string();

		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(currentPath + R"(\)" + std::to_string(i))))
			{
				boost::filesystem::current_path(boost::filesystem::path(currentPath + R"(\)" + std::to_string(i)));

				// for some reason, a file must be loaded in the current path! [2/13/2022 Amir]
				auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
				file::CheckExtension(name);

				auto curve = loadFile(name);
				//auto curve = file::LoadFile<std::shared_ptr<Pln_Edge>>(name + loadExt, verbose);
				if (NOT curve)
				{
					FatalErrorIn(FunctionSIG)
						<< "the curve is a null pointer." << endl
						<< abort(FatalError);
				}
				curve->SetIndex(i + 1);
				myCurves.push_back(std::move(curve));

				i++;
			}
		}

		boost::filesystem::current_path(boost::filesystem::path(currentPath));

		if (verbose)
		{
			Info << endl
				<< " - " << myCurves.size() 
				<< " curves are loaded successfully in " 
				<< global_time_duration 
				<< " ms." 
				<< endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve has been loaded." << endl
				<< abort(FatalError);
		}
		file::SaveTo(myCurves, name + saveExt, verbose);
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
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
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
			Info << " This application is aimed to load curves and putting them into a list." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneCurveList"));

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