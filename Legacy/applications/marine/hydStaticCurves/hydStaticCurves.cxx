#include <Geo_Tools.hxx>
//#include <Marine_System.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_CmptLib2.hxx>
#include <Marine_Models.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <HydStatic_HydCurves.hxx>
#include <HydStatic_HydCurvesGraph.hxx>
#include <StbGMaker_Model.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <algorithm>
#include <vector>

namespace tnbLib
{

	typedef std::shared_ptr<Marine_MultLevWaterDomain> domains_t;
	
	static auto hydCurves = std::make_shared<HydStatic_HydCurves>();

	static domains_t myDomains;
	static size_t verbose;
	static bool loadTag = false;
	static bool exeTag = false;

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

	void setDisplFactor(double x)
	{
		hydCurves->SetDisplFactor(x);
	}

	void loadWaters(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myDomains;

		if (NOT myDomains)
		{
			FatalErrorIn(FunctionSIG)
				<< " domains is null" << endl
				<< abort(FatalError);
		}

		const auto& body = myDomains->Body();

		if (body->NbSections() < 3)
		{
			FatalErrorIn(FunctionSIG)
				<< " the body has not enough sections" << endl
				<< abort(FatalError);
		}

		hydCurves->LoadWaters(myDomains);

		loadTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the waters have been loaded from: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no water domain has been loaded!" << endl
				<< abort(FatalError);
		}

		hydCurves->Perform();
		exeTag = true;

		if (verbose)
		{
			Info << endl;
			Info << " the hydrostatic curves are created, successfully!" << endl;
			Info << endl;
		}
	}

	void saveGraphTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no hydrostatic-curves diagram has been created" << endl
				<< abort(FatalError);
		}
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << hydCurves->Graph();

		if (verbose)
		{
			Info << endl;
			Info << " the hydrostatic-curves graph has been saved at : " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no hydrostatic-curves diagram has been created" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);

		oa << hydCurves;

		if (verbose)
		{
			Info << endl;
			Info << " the hydrostatic-curves has been saved at : " << fn << ", successfully!" << endl;
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
		mod->add(chaiscript::fun([](double x)-> void {setDisplFactor(x); }), "setDisplFactor");
		mod->add(chaiscript::fun([](double x)-> void {setRudder(x); }), "setRudderLoc");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		
		mod->add(chaiscript::fun([](unsigned short i)->void {HydStatic_HydCurves::verbose = i; verbose = i; }), "setVerbose");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadWaters(name); }), "loadWaters");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveGraphTo(name); }), "saveGraphTo");
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

			fileName myFileName("hydStaticCurves");

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