#include <PtdModel_SolidMaker_PropBlade.hxx>
#include <PtdModel_Shape_PropBladeParent.hxx>
#include <PtdModel_PropBlade.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);
	static bool loadTag = false;
	static bool exeTag = false;


	static bool makeLeadPatch = false;
	static bool makeTrailPatch = false;

	static double myTol = 1.0E-6;

	static std::shared_ptr<PtdModel_PropBlade> myBlade;
	static std::shared_ptr<PtdModel_Shape> myShape;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMakeLeadPatch(bool c)
	{
		makeLeadPatch = c;
		if (verbose)
		{
			Info << endl
				<< " - the leading patch making condition is set to: " << (makeLeadPatch ? "True" : "False") << endl;
		}
	}

	void setMakeTrailPatch(bool c)
	{
		makeTrailPatch = c;
		if (verbose)
		{
			Info << endl
				<< " - the trailing patch making condition is set to: " << (makeTrailPatch ? "True" : "False") << endl;
		}
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
			ar >> myBlade;
		}

		if (NOT myBlade)
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
				<< "the algorithm has not been performed" << endl
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
			Info << " the body is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		auto myMaker = std::make_shared<ptdModel::SolidMaker_PropBlade>(myBlade);

		myMaker->SetToCreateLeadingPatch(makeLeadPatch);
		myMaker->SetToCreateTrailingPatch(makeTrailPatch);

		myMaker->SetTolerance(myTol);

		myMaker->Perform();
		Debug_If_Condition_Message(NOT myMaker->IsDone(), "the application is not performed!");

		myShape = myMaker->Shape();
		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
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
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		mod->add(chaiscript::fun([](unsigned short i)->void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setTolerance(x); }), "setTolerance");
		mod->add(chaiscript::fun([](bool c) -> void {setMakeLeadPatch(c); }), "setMakeLeadPatch");
		mod->add(chaiscript::fun([](bool c) -> void {setMakeTrailPatch(c); }), "setMakeTrailPatch");

		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
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

	//PtdModel_PropSection::verbose = 2;
	//PtdModel_PropBlade::verbose = 2;

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
			Info << " Function list:" << endl << endl
				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl
				<< " - execute()" << endl
				<< endl
				<< " Settings: " << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl
				<< " - setTolerance(double)" << endl
				<< " - setMakeLeadPatch(bool);    default value: false" << endl
				<< " - setMakeTrailPatch(bool)    default value: false" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			fileName myFileName("propBladeMaker");

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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
}