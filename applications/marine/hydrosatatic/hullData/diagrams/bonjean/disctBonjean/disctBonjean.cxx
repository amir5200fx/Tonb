#include <HydStatic_SolutionData_Bonjean.hxx>
#include <HydStatic_DisContinuBonjean.hxx>
#include <HydStatic_BonjeanGraph.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_WaterLib.hxx>
#include <Geo_CosineDistb.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_Bonjean> soluData_t;
	typedef std::shared_ptr<Marine_MultLevWaterDomain> domains_t;

	static unsigned short verbose(0);

	static size_t nbWaters = 20;
	static bool loadTag = false;
	static bool exeTag = false;

	soluData_t mySolutionData;

	static std::string myInterplScheme = "global";

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setInterplScheme(const std::string& name)
	{
		myInterplScheme = name;
		if (verbose)
		{
			Info << endl
				<< " - the interpolation scheme is set to: " << myInterplScheme << endl;
		}
	}

	void loadSolutionDate(const std::string& name)
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
			ar >> mySolutionData;
		}

		if (NOT mySolutionData)
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
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been found!" << endl
				<< abort(FatalError);
		}

		const auto& domain = mySolutionData->Domain();
		if (NOT domain)
		{
			FatalErrorIn(FunctionSIG)
				<< "no domain is found!" << endl
				<< abort(FatalError);
		}

		const auto& body = mySolutionData->Body();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		auto alg = std::make_shared<HydStatic_DisContinuBonjean>(domain, body, nbWaters);

		if (myInterplScheme IS_EQUAL "local")
		{
			alg->SetInterplScheme(HydStatic_DisContinuBonjean::interplScheme::Local);
		}
		else if (myInterplScheme IS_EQUAL "global")
		{
			alg->SetInterplScheme(HydStatic_DisContinuBonjean::interplScheme::Global);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid interpolation scheme has been detected!" << endl
				<< " - valid interpolation schemes are: local, global" << endl
				<< abort(FatalError);
		}
		alg->Perform();

		auto g = HydStatic_DisContinuBonjean::RetrieveGraph(alg->Sections());
		mySolutionData->SetGraph(std::move(g));

		exeTag = true;
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
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](int n)-> void {nbWaters = n; }), "setNbWaters");

		mod->add(chaiscript::fun([](const std::string& name)-> void {myInterplScheme = name; }), "setInterplScheme");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSolutionDate(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](unsigned short c)-> void {verbose = c; }), "setVerbose");
		mod->add(chaiscript::fun([](unsigned short c)-> void {HydStatic_DisContinuBonjean::verbose = c; }), "setBonjeanVerbose");

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("hullDataDisctBonjean");

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