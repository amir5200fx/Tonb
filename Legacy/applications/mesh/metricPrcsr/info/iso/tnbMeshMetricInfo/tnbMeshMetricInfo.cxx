#include <Aft_MetricPrcsr_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string extension = Aft_MetricPrcsr_Info::extension;

	static bool exeTag = false;
	static unsigned short verbose = 0;
	
	static const auto myIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static std::shared_ptr<Aft_MetricPrcsr_Info> myInfo;

	class NumIntegInfoRunTime
	{

	public:

		NumIntegInfoRunTime()
		{
			SetConfig();
		}

		static void SetConfig();
	};

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}
}

void tnbLib::NumIntegInfoRunTime::SetConfig()
{
	myIntegInfo->SetMaxNbIterations(50);
	myIntegInfo->SetNbInitIterations(4);
	myIntegInfo->SetTolerance(1.0E-4);
}

const tnbLib::NumIntegInfoRunTime NumIntegInfoRunTimeObj;

namespace tnbLib
{

	void setMaxNbIterations(int n)
	{
		myIntegInfo->SetMaxNbIterations(n);
		if (verbose)
		{
			Info << " - the mx. nb. of iterations is set to: " << n << endl;
		}
	}

	void setNbInitIterations(int n)
	{
		myIntegInfo->SetNbInitIterations(n);

		if (verbose)
		{
			Info << " - the nb. of initial iterations is set to: " << n << endl;
		}
	}

	void setTolerance(double x)
	{
		myIntegInfo->SetTolerance(x);

		if (verbose)
		{
			Info << " - the tolerance is set to: " << x << endl;
		}
	}

	void execute()
	{
		myInfo = std::make_shared<Aft_MetricPrcsr_Info>(myIntegInfo);

		if (verbose)
		{
			Info << " the application is performed, successfully!" << endl;
		}

		exeTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl;
		}

		file::CheckExtension(name);

		file::SaveTo(myInfo, name + extension, verbose);
	}

	void saveTo()
	{
		saveTo("metricInfo");
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
		// io functions 
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/3/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](int n)-> void {setMaxNbIterations(n); }), "setMaxNbIterations");
		mod->add(chaiscript::fun([](int n)-> void {setNbInitIterations(n); }), "setNbInitIterations");
		mod->add(chaiscript::fun([](double x)-> void {setTolerance(x); }), "setTolerance");

		// Operators [12/4/2021 Amir]
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
			Info << " This application is aimed to create an iso-metric info file." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " - setMaxNbIterations(int)" << endl
				<< " - setNbInitIterations(int)" << endl
				<< " - setTolerance(double)" << endl << endl

				<< " # operators: " << endl << endl

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
				fileName theFileName(file::GetSystemFile("tnbMeshMetricInfo"));

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