#include <HydStatic_SolutionData_GZ.hxx>
#include <HydStatic_GZ.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_LightWeight.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_GZ> soluData_t;

	static const unsigned int DEFAULT_NB_DIVISIONS_LOW = 15;
	static const unsigned int DEFAULT_NB_DIVISIONS_MEDIUM = 25;
	static const unsigned int DEFAULT_NB_DIVISIONS_HIGH = 60;

	static const auto myGz = std::make_shared<HydStatic_GZ>();
	static unsigned short verbose(0);
	static auto nPnts = DEFAULT_NB_DIVISIONS_LOW;

	static soluData_t mySolutionData;
	static Marine_LightWeight lightWeight;

	void setTessellation(const word& t)
	{
		if (t IS_EQUAL "low")
		{
			nPnts = DEFAULT_NB_DIVISIONS_LOW;
		}
		else if (t IS_EQUAL "medium")
		{
			nPnts = DEFAULT_NB_DIVISIONS_MEDIUM;
		}
		else if (t IS_EQUAL "high")
		{
			nPnts = DEFAULT_NB_DIVISIONS_HIGH;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined tessellation type" << endl
				<< abort(FatalError);
		}
	}

	void LoadSoluData(const std::string& name)
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

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully!" << endl;
			Info << endl;
		}
	}

	void setVerbose(int v)
	{
		HydStatic_GZ::verbose = (bool)v;
		verbose = v;
	}

	void setVcg(double x)
	{
		const auto& body = mySolutionData->Body();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}
		lightWeight.Vcg().Value() = body->BaseLine().BaseLine().Location().Z() + x;
	}

	void setTcg(double x)
	{
		const auto& body = mySolutionData->Body();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "no body has been found!" << endl
				<< abort(FatalError);
		}
		lightWeight.Tcg().Value() = body->BaseLine().BaseLine().Location().Y() + x;
	}

	void setDispv(double x)
	{
		marineLib::DISPV d(x);
		myGz->SetDispv(std::move(d));
	}

	void execute()
	{
		if (NOT lightWeight.Vcg().IsSpecified())
		{
			FatalErrorIn(FunctionSIG)
				<< "no 'VCG' is specified for the model" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " - VCG: " << lightWeight.Vcg()() << endl;
			if (lightWeight.Tcg().IsSpecified()) Info << " - TCG: " << lightWeight.Tcg()() << endl;
		}
		const auto& body = mySolutionData->Body();
		const auto kg = lightWeight.Vcg()() - body->BaseLine().BaseLine().Location().Z();
		myGz->SetKG(marineLib::KG(kg));

		myGz->Perform();
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
		mod->add(chaiscript::fun([](unsigned int i)->void {setVerbose(i); }), "setVerbose");
		//mod->add(chaiscript::fun([](double x)->void {setKG(x); }), "setKG");
		mod->add(chaiscript::fun([](double x)->void {setDispv(x); }), "setDispv");
		mod->add(chaiscript::fun([](double x)->void {setVcg(x); }), "setVcg");
		mod->add(chaiscript::fun([](double x)->void {setTcg(x); }), "setTcg");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");

		mod->add(chaiscript::fun([](const std::string& t)-> void {setTessellation(t); }), "setTessellation");

		//- io functions

		//mod->add(chaiscript::fun([](const std::string& name)-> void {exportToPlt(name); }), "exportToPlt");
		//mod->add(chaiscript::fun([](const std::string& name)-> void {loadCrossCurves(name); }), "loadCrossCurves");

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

			std::string address = ".\\system\\tnbHydstcGz";
			fileName myFileName(address);

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