#include <Geo2d_MetricPrcsr.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static auto myInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();

	class IntegInfoRunTime
	{

	public:

		IntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::IntegInfoRunTime::SetInfo()
{
	myInfo->SetMaxNbIterations(50);
	myInfo->SetNbInitIterations(3);
	myInfo->SetTolerance(1.0E-4);
}

static tnbLib::IntegInfoRunTime myIntegInfoRunTimeObj;

namespace tnbLib
{

	typedef NumAlg_AdaptiveInteg_Info intgInfo;

	void setMaxNbIterations(const std::shared_ptr<intgInfo>& info, int n)
	{
		info->SetMaxNbIterations(n);
	}

	void setNbInitIterations(const std::shared_ptr<intgInfo>& info, int n)
	{
		info->SetNbInitIterations(n);
	}

	void setTolerance(const std::shared_ptr<intgInfo>& info, double x)
	{
		info->SetTolerance(x);
	}
}

namespace tnbLib
{

	static const std::string loadExt = Geo2d_SizeFunction::extension;
	static const std::string saveExt = Geo2d_MetricPrcsr::extension;

	static std::string myFileName;

	static std::shared_ptr<Geo2d_SizeFunction> mySizeFun;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose = 0;

	static std::shared_ptr<Geo2d_MetricPrcsr> myPrcsr;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySizeFun = file::LoadFile<std::shared_ptr<Geo2d_SizeFunction>>(name + loadExt, verbose);
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< "the size function is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo2d_SizeFunction::extension).string();
		loadFile(name);
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

		fileName fn(name + saveExt);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myPrcsr;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		if (NOT myPrcsr->Name().empty())
		{
			saveTo(myPrcsr->Name());
		}
		else
		{
			saveTo(myFileName);
		}
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		myPrcsr = std::make_shared<Geo2d_MetricPrcsr>(0, name, mySizeFun, myInfo);

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}

		exeTag = true;
	}

	void execute()
	{
		execute("");
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)-> void {setMaxNbIterations(info, n); }), "setMaxNbIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)-> void {setNbInitIterations(info, n); }), "setNbInitIterations");
		mod->add(chaiscript::fun([](const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, double x)-> void {setTolerance(info, x); }), "setTolerance");

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators

		mod->add(chaiscript::fun([]() -> const auto& {return myInfo; }), "getIntegInfo");

		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {execute(name); }), "execute");
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
			Info << " This application is aimed to create a metric processor." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - [IntegInfo].setMaxNbIterations(n)" << endl
				<< " - [IntegInfo].setNbInitIterations(n)" << endl
				<< " - [IntegInfo].setTolerance(double)" << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [IntegInfo] getIntegInfo()" << endl << endl

				<< " - execute(name [optional])" << endl
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
				//std::string address = ".\\system\\tnbMeshMetricPrcsr2d";
				fileName theFileName(file::GetSystemFile("tnbMeshMetricPrcsr2d"));

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