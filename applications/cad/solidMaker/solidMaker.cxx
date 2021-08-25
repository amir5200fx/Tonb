#include <Cad_SolidMaker.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;

	static unsigned short verbose(0);

	static auto myMinTol = 1.0E-6;
	static auto myMaxTol = 1.0E-3;

	static std::shared_ptr<Cad_Shape> myShape;
	static std::shared_ptr<Cad_TModel> mySolid;

	void setMinTolerance(double x)
	{
		myMinTol = x;
		if (verbose)
		{
			Info << " - the min. tolerance is set to: " << x << endl;
			Info << endl;
		}
	}

	void setMaxTolerance(double x)
	{
		myMaxTol = x;
		if (verbose)
		{
			Info << " - the max. tolerance is set to: " << x << endl;
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
				<< "the application is not performed" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolid;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solid is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}


	void execute(const std::string& name)
	{
		const auto d = myShape->BoundingBox()->Diameter();

		auto maker = std::make_shared<Cad_SolidMaker>(myShape->Shape(), myMinTol*d, myMaxTol*d);
		maker->Perform();
		Debug_If_Condition_Message(NOT maker->IsDone(), "the application is not performed!");

		mySolid = maker->Solid();

		mySolid->SetName(name);

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}

		exeTag = true;
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
		mod->add(chaiscript::fun([](double x)-> void {setMinTolerance(x); }), "setMinTol");
		mod->add(chaiscript::fun([](double x)-> void {setMaxTolerance(x); }), "setMaxTol");
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {execute(name); }), "execute(string)");
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
			Info << " This application is aimed to create a solid from a shape." << endl;
			Info << endl
				<< " Function list:" << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " - setMinTol(double)" << endl
				<< " - setMaxTol(double)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - execute()" << endl
				<< " - execute(string)" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("solidMaker");

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