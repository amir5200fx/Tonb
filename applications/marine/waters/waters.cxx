#include <Entity3d_Box.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_FlatWave.hxx>
#include <Marine_Domain.hxx>
#include <Marine_WaterLib.hxx>
#include <Marine_Models.hxx>
#include <Marine_BodyTools.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <HydStatic_CrossCurves.hxx>
#include <StbGMaker_Model.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<StbGMaker_Model> stbModel_t;
	typedef std::shared_ptr<Marine_MultLevWaterDomain> domains_t;

	static stbModel_t myModel;
	static domains_t myDomains;

	static size_t verbose = 0;
	static size_t nbWaters = 20;

	auto getDisplacer()
	{
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no stability model has been loaded" << endl
				<< abort(FatalError);
		}

		const auto& hull = myModel->Hull();
		if (NOT hull)
		{
			FatalErrorIn(FunctionSIG)
				<< "the model has no hull!" << endl
				<< abort(FatalError);
		}

		const auto& body = hull->Body();
		if (NOT body)
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no body in the hull!" << endl
				<< abort(FatalError);
		}

		auto displacer =
			std::dynamic_pointer_cast<marineLib::Body_Displacer>(body);
		return std::move(displacer);
	}

	void loadStbModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);
		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to open the file: " << fn << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ia(f);
		ia >> myModel;

		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< " the stability model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " the model is loaded from: " << fn << ",successfully!" << endl;
		}

		if (NOT myModel->Domain())
		{
			FatalErrorIn(FunctionSIG)
				<< " no domain is found in the model" << endl
				<< abort(FatalError);
		}
	}

	void execute()
	{
		const auto& dim = myModel->Domain();
		const auto& b = *dim->Dim();

		auto Z = HydStatic_CrossCurves::Z(b.P0().Z(), b.P1().Z(), (int)nbWaters);
		myDomains = Marine_WaterLib::MultiLevelsStillWaterDomain(*getDisplacer(), dim, *Z);
	}

	void saveTo(const std::string& name)
	{
		if (NOT myDomains)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);
		boost::archive::polymorphic_text_oarchive oa(f);

		oa << myDomains;
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>
#include <algorithm>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](size_t n)->void {nbWaters = std::max(5, std::min((int)n, 40)); }), "setNbWaters");

		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {loadStbModel(name); }), "loadStbModel");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		mod->add(chaiscript::fun([](size_t t)->void {verbose = t; }), "setVerbose");
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

			fileName myFileName("TnbMarineWaters");

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