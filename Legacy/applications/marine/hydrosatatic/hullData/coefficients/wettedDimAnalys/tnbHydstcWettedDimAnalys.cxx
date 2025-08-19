#include <HydStatic_SolutionData_Coeffs.hxx>
#include <HydStatic_FormDim_Wetted.hxx>
#include <HydStatic_FloatBody.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_Models.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;
	typedef std::shared_ptr<formDim::Wetted> wettedForm_t;

	static soluData_t mySolutionData;
	static wettedForm_t myWettedForm;

	static double rudderAxis = 0;
	static formDim::Wetted::appMode myAppMode;

	TNB_STANDARD_LOAD_SAVE_OBJECTS("solution");
	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(mySolutionData, model_directory, mySolutionData);

	void selectAppMode(const std::string& name)
	{
		if (name IS_EQUAL "auto")
		{
			myAppMode = formDim::Wetted::appMode::Auto;
		}
		else if (name IS_EQUAL "rudderAxis")
		{
			myAppMode = formDim::Wetted::appMode::rudderAxis;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid App. mode has been detected!" << endl
				<< " - modes: 'auto', 'rudderAxis'" << endl
				<< abort(FatalError);
		}
	}

	void execute()
	{
		TNB_CHECK_LOAD_TAG;
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData->IsUpdated(hydStcLib::SolutionData_Coeffs::solutionOrder::floatBody))
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is not updated" << endl
				<< abort(FatalError);
		}

		const auto& floatBody = mySolutionData->FloatBody();
		if (NOT floatBody)
		{
			FatalErrorIn(FunctionSIG)
				<< " no float body has been found!" << endl
				<< abort(FatalError);
		}

		const auto& wave = mySolutionData->Wave();
		if (NOT wave)
		{
			FatalErrorIn(FunctionSIG)
				<< "no wave has been found!" << endl
				<< abort(FatalError);
		}

		myWettedForm = std::make_shared<formDim::Wetted>(floatBody->Wetted(), wave);
		myWettedForm->SetAppMode(myAppMode);
		myWettedForm->Perform(rudderAxis);

		mySolutionData->SetWettedAnalysis(myWettedForm);
		mySolutionData->SetCurrentSolution(hydStcLib::SolutionData_Coeffs::solutionOrder::wettedDim);
		TNB_PERFORMED_TAG;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");

		mod->add(chaiscript::fun([](const std::string& name)-> auto {selectAppMode(name); }), "setAppMode");
		mod->add(chaiscript::fun([](double x)->void {rudderAxis = x; }), "setRudderAxis");

		mod->add(chaiscript::fun([](unsigned int t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short i)-> void {formDim::Wetted::verbose = i; }), "setAnalysVerbose");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
			Info << " This application is aimed to do the wetted dimensional analysis." << endl << endl;

			Info << " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " - setAppMode(name); name = 'auto', 'rudderAxis'" << endl
				<< " - setRudderAxis(x);" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbHydstcWettedDimAnalys"));

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
	return 1;
}