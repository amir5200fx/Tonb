#include <Cad2d_IdentRings_Petal.hxx>
#include <Cad2d_IdentRings.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::string loadExt = Pln_Edge::extension + "list";
	static std::string saveExt = Pln_Wire::extension + "list";

	static std::vector<std::shared_ptr<Pln_Edge>> myCurves;
	static std::vector<std::shared_ptr<Pln_Wire>> myWires;

	static bool loadTag = false;
	static bool exeTag = false;

	static std::string myFileName;

	static unsigned short verbose = 0;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myCurves = file::LoadFile<std::vector<std::shared_ptr<Pln_Edge>>>(name + loadExt, verbose);
		for (const auto& x : myCurves)
		{
			if (NOT x)
			{
				FatalErrorIn(FunctionSIG)
					<< "null pointer has been detected." << endl
					<< abort(FatalError);
			}
			Pln_Tools::Connect(x);
		}

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

		file::SaveTo(myWires, name + saveExt, verbose);
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

		auto alg = std::make_shared<Cad2d_IdentRings>(myCurves);
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed!");

		const auto& petals = alg->Petals();
		myWires.reserve(petals.size());

		for (const auto& x : petals)
		{
			Debug_Null_Pointer(x);

			auto wire = cad2dLib::IdentRings_Petal::MakeWire(x);
			Debug_Null_Pointer(wire);

			myWires.push_back(std::move(wire));
		}
		
		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " - nb. of rings: " << petals.size() << endl;
		}

		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
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
		// io functions [2/13/2022 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		// settings [2/13/2022 Amir]
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
			Info << " This application is aimed to identify the rings." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl

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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneRetrvRings"));

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