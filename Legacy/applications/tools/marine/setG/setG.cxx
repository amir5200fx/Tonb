#include <StbGMaker_Model.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<StbGMaker_Model> model_t;

	static model_t myModel;

	static size_t verbose;

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream f(fn);
		if (f.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file has been found!" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive ar(f);
		ar >> myModel;

		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " model has been loaded from: " << fn << ", successfully!" << endl;
		}
	}

	void checkModel()
	{
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}
	}

	void setLcg(double x)
	{
		checkModel();
		myModel->LightWeight().Lcg().Value() = x;
	}

	void setVcg(double x)
	{
		checkModel();
		myModel->LightWeight().Vcg().Value() = x;
	}

	void setTcg(double x)
	{
		checkModel();
		myModel->LightWeight().Tcg().Value() = x;
	}

	void saveTo(const std::string& name)
	{
		checkModel();
		fileName fn(name);
		std::ofstream f(fn);

		boost::archive::polymorphic_text_oarchive oa(f);
		oa << myModel;
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](double x)->void {setLcg(x); }), "setLcg");
		mod->add(chaiscript::fun([](double x)->void {setVcg(x); }), "setVcg");
		mod->add(chaiscript::fun([](double x)->void {setTcg(x); }), "setTcg");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
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

			setGlobals(mod);

			chai.add(mod);

			fileName myFileName("TnbToolsSetG");

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