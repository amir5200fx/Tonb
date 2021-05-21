#include <HydStatic_SolutionData_Coeffs.hxx>
#include <Marine_Domain.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_WaterDomain.hxx>
#include <Marine_Wave.hxx>
#include <HydStatic_FloatBody.hxx>
#include <HydStatic_ModelShape.hxx>
#include <HydStatic_Shapes.hxx>
#include <StbGMaker_Model.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Coeffs> soluData_t;
	typedef std::shared_ptr<Marine_WaterDomain> waterDomain_t;

	static unsigned short verbose(0);

	static soluData_t mySolutionData;
	static waterDomain_t myWaterDomain;

	static const double DEFAULT_MIN_TOL = 1.0E-6;
	static const double DEFAULT_MAX_TOL = 1.0E-4;

	static auto minTol = DEFAULT_MIN_TOL;
	static auto maxTol = DEFAULT_MAX_TOL;

	void calcWater()
	{
		const auto& body = mySolutionData->Hull();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		const auto& wave = mySolutionData->Wave();
		if (NOT wave)
		{
			FatalErrorIn(FunctionSIG)
				<< "no wave has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT wave->Domain())
		{
			FatalErrorIn(FunctionSIG)
				<< "no domain has been found!" << endl
				<< abort(FatalError);
		}

		myWaterDomain = Marine_WaterLib::WaterDomain(*body, wave, wave->Domain(), minTol, maxTol);
		mySolutionData->SetWater(myWaterDomain->Water());
	}

	void calcFloatBody()
	{
		const auto& displacer = mySolutionData->Hull();
		if (NOT displacer)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " calculating the wetted body..." << endl;
			Info << endl;
		}
		auto wettedBody =
			Marine_BodyTools::WettedBody
			(
				Marine_BodyTools::WettedBody(displacer, myWaterDomain)
			);

		if (verbose)
		{
			Info << endl;
			Info << " calculating the dry body..." << endl;
			Info << endl;
		}

		auto dryBody =
			Marine_BodyTools::DryBody
			(
				Marine_BodyTools::DryBody(displacer, myWaterDomain)
			);

		auto floatBody =
			std::make_shared<HydStatic_FloatBody>
			(
				0, "float body",
				std::move(dryBody),
				std::move(wettedBody)
				);

		mySolutionData->SetFloatBody(floatBody);
	}

	void execute()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		calcWater();
		calcFloatBody();

		mySolutionData->SetCurrentSolution(hydStcLib::SolutionData_Coeffs::solutionOrder::floatBody);
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

		if (NOT mySolutionData->IsUpdated(hydStcLib::SolutionData_Coeffs::solutionOrder::wave))
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

			fileName myFileName("hullDataFloatBody");

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