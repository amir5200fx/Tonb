#include <HydStatic_SolutionData.hxx>
#include <HydStatic_FormDims.hxx>
#include <HydStatic_Model.hxx>
#include <HydStatic_FloatBody.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<HydStatic_SolutionData> soluData_t;

	static soluData_t mySolutionData;

	static unsigned short verbose = 0;

	void loadSoluData(const std::string& name)
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
				<< " the solution data is null" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData->IsUpdated(HydStatic_SolutionData::analysisCode::hydrostaticModel))
		{
			FatalErrorIn(FunctionSIG)
				<< "the solution data is not updated!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is loaded, successfully!" << endl;
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
				<< " no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& model = mySolutionData->HydstaticModel();
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT model->FloatBody())
		{
			FatalErrorIn(FunctionSIG)
				<< "No floating body information has been detected" << endl
				<< abort(FatalError);
		}

		if (NOT model->StbModel())
		{
			FatalErrorIn(FunctionSIG)
				<< "No Stability Model has been detected" << endl
				<< abort(FatalError);
		}

		if (NOT model->Wave())
		{
			FatalErrorIn(FunctionSIG)
				<< "No Wave has been detected" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " calculating the form dimensional..." << endl;
			Info << endl;
		}

		auto displacerCalculator = std::make_shared<formDim::Displacer>();

		const auto& displacer = model->StbModel()->Hull();
		const auto& body = displacer->Body();

		displacerCalculator->LoadBody(body);
		displacerCalculator->Perform();

		if (verbose)
		{
			Info << endl;
			Info << " calculating the wetted form dimensional..." << endl;
			Info << endl;
		}

		auto wettedCalculator = std::make_shared<formDim::Wetted>();

		const auto& wettedBody = model->FloatBody()->Wetted();

		wettedCalculator->LoadBody(wettedBody);
		wettedCalculator->LoadWave(model->Wave());
		wettedCalculator->Perform();

		mySolutionData->SetDimDiaplacerAnalysis(std::move(displacerCalculator));
		mySolutionData->SetDimWettedAnalysis(std::move(wettedCalculator));

		if (verbose)
		{
			Info << endl;
			Info << " all calculations are performed, successfully!" << endl;
			Info << endl;
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

	void formDimensions(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)->void {loadSoluData(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](unsigned short i)-> void {formDim::Wetted::verbose = i; verbose = i; }), "setVerbose");
	}

	std::string getstring(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getstring(argv);
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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();
			formDimensions(mod);
			chai.add(mod);

			fileName myFileName("formDim");

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