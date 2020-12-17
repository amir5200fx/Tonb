#include <HydStatic_GZ.hxx>
#include <HydStatic_CrossCurves.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

#include <algorithm>
#include <vector>

namespace tnbLib
{

	static const auto myGz = std::make_shared<HydStatic_GZ>();

	void loadCrossCurves(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		std::shared_ptr<HydStatic_CrossCurves> curves;
		ar >> curves;
		myGz->LoadCrossCurves(curves);
	}

	void setKG(double x)
	{
		marineLib::KG kg(x);
		myGz->SetKG(std::move(kg));
	}

	void setDispv(double x)
	{
		marineLib::DISPV d(x);
		myGz->SetDispv(std::move(d));
	}

	void execute()
	{
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

		mod->add(chaiscript::fun([](double x)->void {setKG(x); }), "setKG");
		mod->add(chaiscript::fun([](double x)->void {setDispv(x); }), "setDispv");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCrossCurves(name); }), "loadCrossCurves");

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



			chai.add(mod);

			fileName myFileName("crossCurves");

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
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

}