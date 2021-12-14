#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_MetricPrcsrAnIso.hxx>
#include <Aft2d_SolutionData.hxx>
#include <Aft2d_SolutionDataAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft_MetricPrcsr_Info.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	static const std::string extension = Aft2d_SolutionData::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Aft2d_SolutionDataBase> mySoluData;
	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_SolutionDataBase>>(name + extension, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
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

		file::SaveTo(mySoluData, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT mySoluData->SizeFunction())
		{
			FatalErrorIn(FunctionSIG)
				<< "no size function has been found!" << endl
				<< abort(FatalError);
		}

		if (mySoluData->IsIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionData>(mySoluData);
			Debug_Null_Pointer(soluData);

			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsr>(0, name, soluData->SizeFunction(), soluData->GlobalMetricInfo());
			soluData->SetMetric(std::move(metricPrcsr));
		}
		else if (mySoluData->IsAnIso())
		{
			auto soluData = std::dynamic_pointer_cast<Aft2d_SolutionDataAnIso>(mySoluData);
			Debug_Null_Pointer(soluData);

			if (NOT soluData->MetricFunction())
			{
				FatalErrorIn(FunctionSIG)
					<< "no metric function has been found!" << endl
					<< abort(FatalError);
			}

			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrAnIso>(0, name, soluData->SizeFunction(), soluData->MetricFunction(), soluData->GlobalMetricInfo());
			soluData->SetMetric(std::move(metricPrcsr));
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Unspecified type of data has been detected!" << endl
				<< abort(FatalError);
		}

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}
	}

	void execute()
	{
		execute("metricProcessor");
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions [12/12/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [12/12/2021 Amir]

		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/12/2021 Amir]

		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to create metric processor." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute(name [optional])" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshMetricPrcsr2d"));

				chai.eval_file(myFileName);
				return 0;
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
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}