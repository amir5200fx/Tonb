#include <HydStatic_Model.hxx>
#include <HydStatic_FormDim_Displacer.hxx>
#include <HydStatic_FormDim_Wetted.hxx>

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
	static const auto displacerCalculator = std::make_shared<formDim::Displacer>();
	static const auto wettedCalculator = std::make_shared<formDim::Wetted>();

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myModel;

		if (NOT myModel->FloatBody())
		{
			FatalErrorIn(FunctionSIG)
				<< "No floating body information has been detected" << endl
				<< abort(FatalError);
		}

		if (NOT myModel->StbModel())
		{
			FatalErrorIn(FunctionSIG)
				<< "No Stability Model has been detected" << endl
				<< abort(FatalError);
		}
	}

	void calcDisplacer()
	{
		const auto& displacer = myModel->StbModel()->Hull();
		const auto& body = displacer->Body();
		
		displacerCalculator->LoadBody(body);
		displacerCalculator->Perform();
	}

	void calcWetted()
	{
		const auto& wettedBody = myModel->FloatBody()->Wetted();
		
		wettedCalculator->LoadBody(wettedBody);
		wettedCalculator->Perform();
	}

	void printParameters()
	{
		const auto& p1 = displacerCalculator->Parameters();

		Info << "LOA= " << p1->Loa() << endl;
		Info << "B= " << p1->B() << endl;
		Info << "D= " << p1->D() << endl;

		const auto& p2 = wettedCalculator->Parameters();

		Info << "APP= " << p2->App() << endl;
		Info << "AUW= " << p2->Auw() << endl;
		Info << "AWL= " << p2->Awl() << endl;
		Info << "BWL= " << p2->Bwl() << endl;
		Info << "FPP= " << p2->Fpp() << endl;
		Info << "FUW= " << p2->Fuw() << endl;
		Info << "FWL= " << p2->Fwl() << endl;
		Info << "LOS= " << p2->Los() << endl;
		Info << "LPP= " << p2->Lpp() << endl;
		Info << "LWL= " << p2->Lwl() << endl;
		Info << "MPP= " << p2->Mpp() << endl;
		Info << "TM= " << p2->Tm() << endl;
	
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([]()->void {calcDisplacer(); /*calcWetted();*/ }), "execute");
		mod->add(chaiscript::fun([]()->void {printParameters(); }), "printParameters");
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

			chai.add(mod);

			fileName myFileName("FormDimensions");

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

