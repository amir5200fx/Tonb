#include <Cad_ApprxMetric.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Cad3d_GModel.hxx>
#include <GModel_MetricAnalyzer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<GModel_MetricAnalyzer> myAnalyzer;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	bool isNumber(const std::string s)
	{
		if (s.size() IS_EQUAL 0) return false;
		for (int i = 0; i < s.size(); i++)
		{
			if ((s[i] >= '0' && s[i] <= '9') IS_EQUAL false)
			{
				return false;
			}
		}
		return true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(myAnalyzer, name + GModel_MetricAnalyzer::extension, verbose);
	}

	void saveTo()
	{
		saveTo("metricAnalyzer");
	}

	auto loadInfos()
	{
		checkFolder("global");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/30/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\global)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_ApprxMetricInfo::extension).string();
		auto glSurfInfo = file::LoadFile<std::shared_ptr<Cad_ApprxMetricInfo>>(name + Cad_ApprxMetricInfo::extension, verbose);
		if (NOT glSurfInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< " the global surface info file is null" << endl
				<< abort(FatalError);
		}

		std::map<int, std::shared_ptr<Cad_ApprxMetricInfo>> surfInfoMap;
		{
			// load subs [12/30/2021 Amir]
			for
				(
					boost::filesystem::directory_iterator iter(currentPath);
					iter != boost::filesystem::directory_iterator();
					iter++
					)
			{
				auto fname = iter->path().string();
				if (isNumber(fname))
				{
					auto surfNb = std::stoi(fname);

					// change the current path [12/30/2021 Amir]
					boost::filesystem::current_path(currentPath.string() + R"(\)" + fname);

					try
					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad_ApprxMetricInfo::extension).string();
						auto surfInfo = file::LoadFile<std::shared_ptr<Cad_ApprxMetricInfo>>(name + Cad_ApprxMetricInfo::extension, verbose);
						if (NOT surfInfo)
						{
							FatalErrorIn(FunctionSIG)
								<< " the info curve file is null!" << endl
								<< abort(FatalError);
						}

						auto paired = std::make_pair(surfNb, std::move(surfInfo));
						auto insert = surfInfoMap.insert(std::move(paired));
						if (NOT insert.second)
						{
							FatalErrorIn(FunctionSIG)
								<< "unable to insert the curve info into the map!" << endl
								<< " Duplicate data maybe?!" << endl
								<< abort(FatalError);
						}

						if (verbose)
						{
							Info << " - the surface info, " << surfNb << ", has been loaded, successfully!" << endl;
						}
					}
					catch (const error& x)
					{
						Info << " - Couldn't load the surface info: " << endl;
						Info << x.message() << endl;
					}
				}
			}
		}

		// change back the current path [12/30/2021 Amir]
		boost::filesystem::current_path(currentPath);

		auto t = std::make_tuple(std::move(glSurfInfo), std::move(surfInfoMap));
		return std::move(t);
	}

	auto loadModel()
	{
		checkFolder("model");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/30/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\model)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad3d_GModel::extension).string();

		auto model = file::LoadFile<std::shared_ptr<Cad3d_GModel>>(name + Cad3d_GModel::extension, verbose);
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< " the model file is null" << endl
				<< abort(FatalError);
		}

		// change back the current path [12/30/2021 Amir]
		boost::filesystem::current_path(currentPath);
		return std::move(model);
	}

	void execute()
	{
		auto [glInfo, infoMap] = loadInfos();

		auto model = loadModel();

		auto analyzer = std::make_shared<GModel_MetricAnalyzer>();

		analyzer->SetModel(std::move(model));
		analyzer->OverrideGlobalInfo(std::move(glInfo));
		analyzer->InfosRef() = std::move(infoMap);

		myAnalyzer = std::move(analyzer);

		exeTag = true;

		if (verbose)
		{
			Info << " the application is performed, successfully!" << endl;
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
		// io functions [12/30/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/30/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/30/2021 Amir]
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
			Info << " This application is aimed to create a metric analyzer of a GModel." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

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
				fileName theFileName(file::GetSystemFile("tnbCadToolGModelMetricAnalyzer"));

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