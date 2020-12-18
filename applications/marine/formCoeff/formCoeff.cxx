#include <HydStatic_Model.hxx>
#include <HydStatic_FormCoeff.hxx>

#include <HydStatic_FloatBody.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<HydStatic_Model> hModel_t;

	static hModel_t myModel;
	static std::shared_ptr<formCoeff::Wetted> formCoeffCalculator;

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myModel;
		if (NOT myModel->FloatBody())
		{
			FatalErrorIn(FunctionSIG)
				<< "NNo floating body information has been detected" << endl
				<< abort(FatalError);
		}
	}

	void calcFormCoeff()
	{
		const auto& wettedBody = myModel->FloatBody()->Wetted();
		formCoeffCalculator = std::make_shared<formCoeff::Wetted>(wettedBody);
		formCoeffCalculator->Perform();
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<chaiscript::Module> module_t;
	
	void formCoefficient(const module_t& mod)
	{

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([]()->void {calcFormCoeff(); }), "execute");
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



			chai.add(mod);

			fileName myFileName("FormCoefficients");

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