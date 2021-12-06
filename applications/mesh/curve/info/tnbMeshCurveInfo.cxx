#include <Mesh_Curve_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string extension = Mesh_Curve_Info::extension;

	static unsigned short verbose = 0;
	static bool exeTag = false;

	static std::shared_ptr<Mesh_Curve_Info> myInfo;

	static const auto myOverallLenIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static const auto myIterIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static const auto myNewtonIterInfo = std::make_shared<NumAlg_NewtonSolver_Info>();
	static const auto myOptPointCorrInfo = std::make_shared<Mesh_CurveOptmPoint_Correction_Info>();

	class OverallLenIntegInfoRunTime
	{

	public:

		OverallLenIntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};

	class IterIntegInfoRunTime
	{

	public:

		IterIntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};

	class NewtonIterInfoRunTime
	{

	public:

		NewtonIterInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};

	class OptPointCorrInfoRunTime
	{

	public:

		OptPointCorrInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::OverallLenIntegInfoRunTime::SetInfo()
{
	myOverallLenIntegInfo->SetMaxNbIterations(500);
	myOverallLenIntegInfo->SetNbInitIterations(6);
	myOverallLenIntegInfo->SetTolerance(1.0E-8);
}

namespace tnbLib
{

	void setMaxNbIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)
	{
		info->SetMaxNbIterations(n);
	}

	void setNbInitIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)
	{
		info->SetNbInitIterations(n);
	}

	void setTolerance(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, double x)
	{
		info->SetTolerance(x);
	}
}

void tnbLib::IterIntegInfoRunTime::SetInfo()
{
	myIterIntegInfo->SetMaxNbIterations(50);
	myIterIntegInfo->SetNbInitIterations(3);
	myIterIntegInfo->SetTolerance(1.0E-4);
}

void tnbLib::NewtonIterInfoRunTime::SetInfo()
{
	myNewtonIterInfo->SetMaxIterations(50);
	myNewtonIterInfo->SetSmall(1.0E-6);
	myNewtonIterInfo->SetZero(1.0E-6);
	myNewtonIterInfo->SetTolerance(1.0E-6);
	myNewtonIterInfo->SetUnderRelaxation(0.9);
}

namespace tnbLib
{

	void setMaxNbIterations(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, int n)
	{
		info->SetMaxIterations(n);
	}

	void setSmall(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetSmall(x);
	}

	void setZero(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetZero(x);
	}

	void setTolerance(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetTolerance(x);
	}

	void setUnderRelaxation(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetUnderRelaxation(x);
	}
}

void tnbLib::OptPointCorrInfoRunTime::SetInfo()
{
	myOptPointCorrInfo->SetMaxLevel(10);
	myOptPointCorrInfo->SetTolerance(1.0E-6);
	myOptPointCorrInfo->SetUnderRelaxation(0.9);
}

namespace tnbLib
{

	void setMaxLevel(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, int n)
	{
		info->SetMaxLevel(n);
	}

	void setTolerance(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, double x)
	{
		info->SetTolerance(x);
	}

	void setUnderRelaxation(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, double x)
	{
		info->SetUnderRelaxation(x);
	}
}

static tnbLib::OverallLenIntegInfoRunTime myOverallLenIntegInfoRunTimeObj;
static tnbLib::IterIntegInfoRunTime myIterIntegInfoRunTimeObj;
static tnbLib::NewtonIterInfoRunTime myNewtonIterInfoRunTimeObj;
static tnbLib::OptPointCorrInfoRunTime myOptPointCorrInfoRunTimeObj;

namespace tnbLib
{

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myInfo, name + extension, verbose);
	}

	void saveTo()
	{
		saveTo("curveInfo");
	}

	void execute()
	{
		myInfo = std::make_shared<Mesh_Curve_Info>();

		myInfo->OverrideCorrAlgInfo(myOptPointCorrInfo);
		myInfo->OverrideNewtonIntgInfo(myIterIntegInfo);
		myInfo->OverrideNewtonIterInfo(myNewtonIterInfo);
		myInfo->OverrideOverallLengthIntgInfo(myOverallLenIntegInfo);

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
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
		//- io functions
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)-> void {setMaxNbIterations(info, n); }), "setMaxNbIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)-> void {setNbInitIterations(info, n); }), "setNbInitIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");

		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, int n)-> void {setMaxNbIterations(info, n); }), "setMaxNbIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)-> void {setSmall(info, x); }), "setSmall");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)-> void {setZero(info, x); }), "setZero");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)-> void {setUnderRelaxation(info, x); }), "setUnderRelaxation");

		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, int n)-> void {setMaxLevel(info, n); }), "setMaxLev");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");
		mod->add(chaiscript::fun([](const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, double x)-> void {setUnderRelaxation(info, x); }), "setUnderRelaxation");

		mod->add(chaiscript::fun([](int n) -> void {myInfo->SetLengthCalcMaxLevel(n); }), "setOverallLenMaxLevel");
		mod->add(chaiscript::fun([](double x) -> void {myInfo->SetUnderRelaxation(x); }), "setUnderRelaxation");
		mod->add(chaiscript::fun([](bool x) -> void {myInfo->SetIgnoreNonConvergency(x); }), "setIgnoreNonConvergency");

		//- operators

		mod->add(chaiscript::fun([]() -> const auto& {return myIterIntegInfo; }), "getIntegInfo");
		mod->add(chaiscript::fun([]() -> const auto& {return myOverallLenIntegInfo; }), "getOverallLenIntegInfo");
		mod->add(chaiscript::fun([]() -> const auto& {return myNewtonIterInfo; }), "getIterInfo");
		mod->add(chaiscript::fun([]() -> const auto& {return myOptPointCorrInfo; }), "getCorrInfo");

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
		tnbLib::Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << " This application is aimed to discretize a curve." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setOverallLenMaxLevel(n)" << endl
				<< " - setUnderRelaxation(double)" << endl
				<< " - setIgnoreNonConvergency(bool)" << endl << endl

				<< " - [IntegInfo].setMaxNbIterations(n)" << endl
				<< " - [IntegInfo].setNbInitIterations(n)" << endl
				<< " - [IntegInfo].setTolerance(double)" << endl << endl

				<< " - [NewtonInfo].setMaxNbIterations(n)" << endl
				<< " - [NewtonInfo].setSmall(double)" << endl
				<< " - [NewtonInfo].setZero(double)" << endl
				<< " - [NewtonInfo].setTolerance(double)" << endl
				<< " - [NewtonInfo].setUnderRelaxation(double)" << endl << endl

				<< " - [CorrInfo].setMaxLev(n)" << endl
				<< " - [CorrInfo].setTolerance(double)" << endl
				<< " - [CorrInfo].setUnderRelaxation(double)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [IntegInfo] getIntegInfo()" << endl
				<< " - [IntegInfo] getOverallLenIntegInfo()" << endl
				<< " - [NewtonInfo] getIterInfo()" << endl
				<< " - [CorrInfo] getCorrInfo()" << endl << endl
				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);


			try
			{
				fileName theFileName(file::GetSystemFile("tnbMeshCurveInfo"));

				chai.eval_file(theFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				tnbLib::Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				tnbLib::Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				tnbLib::Info << x.what() << endl;
			}
		}
		else
		{
			tnbLib::Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		tnbLib::Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}