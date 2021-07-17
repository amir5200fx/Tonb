#include <HydStatic_SolutionData_HydCurves.hxx>
#include <HydStatic_HydCurves.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterLib.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	typedef std::shared_ptr<hydStcLib::SolutionData_HydCurves> soluData_t;

	static soluData_t mySolutionData;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);
	auto hydCurves = std::make_shared<HydStatic_HydCurves>();

	static unsigned int DEFAULT_NB_WATERS = 20;
	static unsigned int MIN_MN_WATERS = 10;

	static unsigned int nbWatres = DEFAULT_NB_WATERS;

	void loadSolutionData(const std::string& name)
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

		loadTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed" << endl
				<< abort(FatalError);
		}

		mySolutionData->SetCurves(hydCurves);

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

	void setRhoSW(double x)
	{
		hydCurves->SetRhoSW(x);
	}

	void setRhoFW(double x)
	{
		hydCurves->SetRhoFW(x);
	}

	void setRudder(double x)
	{
		hydCurves->SetRudderLocation(x);
	}

	/*void setDisplFactor(double x)
	{
		hydCurves->AlgInfo().DisplFactor = x;
	}*/

	void setInterpolation(bool c)
	{
		hydCurves->SetInterpolation(c);
	}

	void setNbWaters(unsigned int n)
	{
		if (n <= MIN_MN_WATERS)
			n = MIN_MN_WATERS;
		nbWatres = n;
	}

	void useSteffen(bool c)
	{
		hydCurves->SetSteffenTessellation(c);
	}

	auto createWaters()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data is found!" << endl
				<< abort(FatalError);
		}
		const auto& dim = mySolutionData->Domain();
		const auto& body = mySolutionData->Body();

		if (NOT dim)
		{
			FatalErrorIn(FunctionSIG)
				<< "no dim has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}

		auto b = Marine_BodyTools::BoundingBox(*body);
		
		const auto z0 = b.P0().Z();
		const auto z1 = b.P1().Z();

		auto Z = HydStatic_CrossCurves::Z(z0, z1, nbWatres);
		auto domains = Marine_WaterLib::MultiLevelsStillWaterDomain(*body, dim, *Z);
		return std::move(domains);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been loaded!" << endl
				<< abort(FatalError);
		}

		auto waters = createWaters();

		hydCurves->LoadWaters(waters);
		hydCurves->Perform();

		exeTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the hydrostatic curves are created, successfully!" << endl;
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
		mod->add(chaiscript::fun([](double x)-> void {setRhoFW(x); }), "setRhoFW");
		mod->add(chaiscript::fun([](double x)-> void {setRhoSW(x); }), "setRhoSW");
		//mod->add(chaiscript::fun([](double x)-> void {setDisplFactor(x); }), "setDisplFactor");
		mod->add(chaiscript::fun([](double x)-> void {setRudder(x); }), "setRudderLoc");
		mod->add(chaiscript::fun([](bool c)-> void {useSteffen(c); }), "useSteffenTessellation");
		mod->add(chaiscript::fun([](bool c)-> void {setInterpolation(c); }), "setInterpolation");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; if (i > 1) { HydStatic_HydCurves::verbose = i - 1; } }), "setVerbose");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadSolutionData(name); }), "loadSoluData");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
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
	//sysLib::init_gl_marine_integration_info();
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

			fileName myFileName("hullDataHydstcCurves");

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
			Info << " - Unspecified command has been detected!" << endl
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