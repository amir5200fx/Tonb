#include <HydStatic_SolutionData_Coeffs.hxx>
#include <HydStatic_FormDim_Wetted.hxx>
#include <HydStatic_FloatBody.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_Models.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;
	typedef std::shared_ptr<formDim::Wetted> wettedForm_t;

	static unsigned short verbose(0);

	static soluData_t mySolutionData;
	static wettedForm_t myWettedForm;

	static double rudderAxis = 0;
	static formDim::Wetted::appMode myAppMode;

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

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the solution data from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);

		TNB_iARCH_FILE_TYPE ar(myFile);

		ar >> mySolutionData;
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData->IsUpdated(hydStcLib::SolutionData_Coeffs::solutionOrder::floatBody))
		{
			FatalErrorIn(FunctionSIG)
				<< " the solution data is not updated" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}

	}

	void saveTo(const std::string& name)
	{
		fileName fn(name);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << mySolutionData;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](const std::string& name)-> auto {selectAppMode(name); }), "setAppMode");
		mod->add(chaiscript::fun([](double x)->void {rudderAxis = x; }), "setRudderAxis");

		mod->add(chaiscript::fun([](size_t t)->void {verbose = t; }), "setVerbose");

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("hullDataWettedDimAnalys");

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