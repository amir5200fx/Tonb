#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>
#include <HydStatic_FillCurve.hxx>
#include <HydStatic_SolutionData_GzEff.hxx>
#include <HydStatic_Shapes.hxx>
#include <HydStatic_FillTank.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	typedef std::shared_ptr<hydStcLib::SolutionData_GzEff> soluData_t;
	typedef std::shared_ptr<HydStatic_TankShape> tankShape_t;
	typedef std::shared_ptr<marineLib::Body_Tank> body_t;
	typedef std::shared_ptr<Marine_Domain> domain_t;

	static const unsigned int DEFAULT_NB_WATERS = 10;
	static const unsigned int MIN_NB_WATERS = 3;

	static soluData_t mySolutionData;
	static unsigned int nbWaters = DEFAULT_NB_WATERS;

	static unsigned short verbose = 0;

	void checkData()
	{
		if (NOT mySolutionData)
		{
			FatalErrorIn(FunctionSIG)
				<< "no solution data has been found!" << endl
				<< abort(FatalError);
		}
	}

	void loadSoluData(const std::string& name)
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
				<< " the solution data is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the solution data is loaded, successfully!" << endl;
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

	auto calcFillCurve(const domain_t& d, const body_t& tank)
	{
		auto alg = std::make_shared<HydStatic_FillTank>(d, tank, nbWaters);
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

		return alg->Curve();
	}

	void setNbWaters(unsigned int n)
	{
		nbWaters = std::max(MIN_NB_WATERS, n);
	}

	void execute()
	{
		checkData();

		for (const auto& iter : mySolutionData->Tanks())
		{
			const auto& x = iter.second;
			const auto& model = x->Model();

			auto curve = calcFillCurve(x->Domain(), model->Body());

			x->SetFillCurve(std::move(curve));
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

	 void setFunctions(const module_t& mod)
	 {
		 mod->add(chaiscript::fun([](const std::string& name)-> void {loadSoluData(name); }), "loadSoluData");
		 mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		 mod->add(chaiscript::fun([](unsigned int n)->void {setNbWaters(n); }), "setNbWaters");
		 mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");

		 mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");
		 mod->add(chaiscript::fun([](unsigned short i)-> void {HydStatic_FillTank::verbose = i; }), "setAlgVerbose");
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
			 setFunctions(mod);
			 chai.add(mod);

			 fileName myFileName("fillCurve");

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