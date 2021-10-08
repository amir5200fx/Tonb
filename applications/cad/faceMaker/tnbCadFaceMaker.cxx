#include <Cad_GeomSurface.hxx>
#include <Cad_Shape.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Face.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	static double degTol = 1.0E-6;

	static std::shared_ptr<Cad_GeomSurface> mySurf;
	static std::shared_ptr<Cad_Shape> myShape;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setDegTol(double x)
	{
		degTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the DegTol is set to: " << degTol << endl;
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
			ar >> mySurf;
		}

		if (NOT mySurf)
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
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myShape;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		auto face = BRepBuilderAPI_MakeFace(mySurf->Geometry(), degTol);
		myShape = std::make_shared<Cad_Shape>(0, name, std::move(face));

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		execute("");
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

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setDegTol(x); }), "setDegTol");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {execute(name); }), "execute");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to create a face." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setDegTol(double)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

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

			std::string address = ".\\system\\tnbCadFaceMaker";
			fileName myFileName(address);

			try
			{
				chai.eval_file(myFileName);
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