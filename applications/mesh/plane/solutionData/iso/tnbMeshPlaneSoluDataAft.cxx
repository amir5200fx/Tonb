#include <Aft2d_SolutionData.hxx>
#include <Aft2d_OptNode_Calculator.hxx>
#include <Aft_MetricPrcsr_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Cad2d_Plane.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string extension = Aft2d_SolutionData::extension;

	static unsigned short verbose = 0;
	static bool exeTag = false;

	void checkFolder(const std::string& name)
	{
		if (NOT boost::filesystem::is_directory(name))
		{
			FatalErrorIn(FunctionSIG)
				<< "no {" << name << "} directory has been found!" << endl
				<< abort(FatalError);
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
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

	static std::shared_ptr<Aft2d_SolutionDataBase> mySolutionData;

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		file::CheckExtension(name);

		file::SaveTo(mySolutionData, name + extension, verbose);
	}

	void saveTo()
	{
		saveTo("solutionData");
	}

	auto loadGlobalInfo()
	{
		checkFolder("global");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\global)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Aft_MetricPrcsr_Info::extension).string();

		auto metricInfo = file::LoadFile<std::shared_ptr<Aft_MetricPrcsr_Info>>(name + Aft_MetricPrcsr_Info::extension, verbose);
		if (NOT metricInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< " the global metric info file is null!" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		return std::move(metricInfo);
	}

	auto loadCurveInfo()
	{
		checkFolder("curve");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\curve)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();

		auto glCurveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
		if (NOT glCurveInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< " the global curve info file is null" << endl
				<< abort(FatalError);
		}

		std::map<int, std::shared_ptr<Mesh_Curve_Info>> curveInfoMap;
		{
			const auto subCurrentPath = boost::filesystem::current_path();

			// load subdirectories [12/4/2021 Amir]
			for 
				(
					boost::filesystem::directory_iterator iter(subCurrentPath);
					iter != boost::filesystem::directory_iterator(); 
					iter++
					)
			{
				auto fname = iter->path().string();
				if (isNumber(fname))
				{
					auto curveNb = std::stoi(fname);

					// Change the current path [12/2/2021 Amir]
					boost::filesystem::current_path(subCurrentPath.string() + R"(\)" + fname);

					try
					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();
						auto curveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
						if (NOT curveInfo)
						{
							FatalErrorIn(FunctionSIG)
								<< " the info curve file is null!" << endl
								<< abort(FatalError);
						}

						auto paired = std::make_pair(curveNb, std::move(curveInfo));
						auto insert = curveInfoMap.insert(std::move(paired));
						if (NOT insert.second)
						{
							FatalErrorIn(FunctionSIG)
								<< "unable to insert the curve info into the map!" << endl
								<< " Duplicate data maybe?!" << endl
								<< abort(FatalError);
						}

						if (verbose)
						{
							Info << " - the curve info, " << curveNb << ", has been loaded, successfully!" << endl;
						}
					}
					catch (const error& x)
					{
						Info << " - Couldn't load the curve info: " << endl;
						Info << x.message() << endl;				
					}
				}
			}
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		auto t = std::make_tuple(std::move(glCurveInfo), std::move(curveInfoMap));
		return std::move(t);
	}

	auto loadSizeFunction()
	{
		checkFolder("sizeMap");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\sizeMap)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Geo2d_SizeFunction::extension).string();

		auto sizeFun = file::LoadFile<std::shared_ptr<Geo2d_SizeFunction>>(name + Geo2d_SizeFunction::extension, verbose);
		if (NOT sizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< " the size function file is null" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		return std::move(sizeFun);
	}

	auto loadPlane()
	{
		checkFolder("plane");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/4/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\plane)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Cad2d_Plane::extension).string();

		auto plane = file::LoadFile<std::shared_ptr<Cad2d_Plane>>(name + Cad2d_Plane::extension, verbose);
		if (NOT plane)
		{
			FatalErrorIn(FunctionSIG)
				<< " the plane file is null" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		return std::move(plane);
	}

	auto loadNodeCreator()
	{
		checkFolder("nodeCreator");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [12/21/2021 Amir]
		boost::filesystem::current_path(currentPath.string() + R"(\nodeCreator)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Aft2d_OptNode_Calculator::extension).string();

		auto alg = file::LoadFile<std::shared_ptr<Aft2d_OptNode_Calculator>>(name + Aft2d_OptNode_Calculator::extension, verbose);
		if (NOT alg)
		{
			FatalErrorIn(FunctionSIG)
				<< " the node creator file is null" << endl
				<< abort(FatalError);
		}

		// change back the current path [12/21/2021 Amir]
		boost::filesystem::current_path(currentPath);

		return std::move(alg);
	}

	void execute()
	{
		auto metricInfo = loadGlobalInfo();

		auto [glCurveInfo, curveInfoMap] = loadCurveInfo();

		auto sizeFun = loadSizeFunction();

		auto plane = loadPlane();

		auto nodeCreator = loadNodeCreator();

		auto soluData = std::make_shared<Aft2d_SolutionData>();

		soluData->LoadGlobalMetricInfo(std::move(metricInfo));
		soluData->LoadGlobalCurveInfo(std::move(glCurveInfo));

		soluData->LoadCurveInfo(std::move(curveInfoMap));

		soluData->LoadSizeFunction(std::move(sizeFun));

		soluData->LoadPlane(std::move(plane));

		soluData->LoadNodeCalculator(std::move(nodeCreator));

		mySolutionData = std::move(soluData);

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
		// io functions [12/5/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/5/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/5/2021 Amir]
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
			Info << " This application is aimed to create a solution data of the plane mesh." << endl
				<< endl
				<< " # Subdirectories: " << endl
				<< " - global (metric info)" << endl
				<< " - curve (info)" << endl
				<< " - sizeMap" << endl
				<< " - plane" << endl
				<< " - nodeCreator" << endl << endl;
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
				fileName theFileName(file::GetSystemFile("tnbMeshPlaneSoluDataAft"));

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