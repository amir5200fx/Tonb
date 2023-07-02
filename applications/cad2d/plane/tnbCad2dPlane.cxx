#include <Cad2d_Modeler.hxx>
#include <Cad2d_Plane.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_GLOBAL_PATH;

	TNB_SET_VERBOSE_FUN;

	static std::vector<std::shared_ptr<Pln_Edge>> myEdges;
	static std::shared_ptr<Cad2d_Plane> myPlane;

	void loadFiles()
	{
		if (verbose)
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
		}
		myEdges = file::LoadFiles<std::shared_ptr<Pln_Edge>>(verbose);
		for (const auto& x : myEdges)
		{
			TNB_CHECK_LOADED_FILE(x);
		}
		if (verbose)
		{
			Info << endl
				<< " - all files of the list have been successfully loaded, in "
				<< global_time_duration << " ms." << endl;
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		TNB_CHECK_EXE_TAG;
		file::CheckExtension(name);
		file::SaveTo(myPlane, name + Cad2d_Plane::extension, verbose);
	}

	void saveTo()
	{
		TNB_CHECK_EXE_TAG;
		saveTo(myPlane->Name());
	}

	void execute(const std::string& name)
	{
		TNB_CHECK_LOAD_TAG;
		if (myEdges.empty())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "the edge list is empty." << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);
		}
		if (verbose > 1)
		{
			Cad2d_Modeler::verbose = 1;
		}
		auto modeler = std::make_shared<Cad2d_Modeler>();
		modeler->Import(myEdges);

		Cad2d_Modeler::selctList l;
		modeler->SelectAll(l);
		modeler->MakePlanes(l);

		if (modeler->NbPlanes() > 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "no multiple planes construction is permitted" << endl
				<< abort(FatalError);
		}
		if (NOT modeler->NbPlanes())
		{
			FatalErrorIn(FunctionSIG)
				<< "no plane has been created" << endl
				<< abort(FatalError);
		}
		auto iter = modeler->Planes().begin();
		myPlane = std::move(iter->second);
		myPlane->SetName(name);
		if (verbose)
		{
			Info << endl
				<< "- the application is successfully performed, in " << global_time_duration << " ms" << endl;
		}
		TNB_EXECUTE_TAG;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a planar solid." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1, 2" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute(name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbCad2dPlane"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}