#include <GeoMetricFun2d_Uniform.hxx>
#include <Entity2d_Metric2.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

namespace tnbLib
{

	static const std::string saveExt = Geo2d_MetricFunction::extension;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose = 0;

	static std::shared_ptr<Entity2d_Box> myRegion;
	static std::shared_ptr<Geo2d_MetricFunction> myMetricFun;

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

	void loadFile()
	{
		checkFolder("region");

		const auto currentPath = boost::filesystem::current_path();

		boost::filesystem::current_path(currentPath.string() + R"(\region)");

		auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity2d_Box::extension).string();

		file::CheckExtension(name);

		myRegion = file::LoadFile<std::shared_ptr<Entity2d_Box>>(name + Entity2d_Box::extension, verbose);
		if (NOT myRegion)
		{
			FatalErrorIn(FunctionSIG)
				<< " the region file is null!" << endl
				<< abort(FatalError);
		}

		//- change back the current path
		boost::filesystem::current_path(currentPath);

		loadTag = true;
	}

	auto createDir(double x, double y)
	{
		return gp_Dir2d(x, y);
	}

	auto createMetric(double h1, double h2, const gp_Dir2d& e1, const gp_Dir2d& e2)
	{
		Entity2d_Metric2 m(h1, h2, e1, e2);
		return std::move(m);
	}

	auto createMetric(double a, double b, double c)
	{
		Entity2d_Metric1 m(a, b, c);
		return std::move(m);
	}

	void createMap(const std::string& name, const Entity2d_Metric1& m)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}
		myMetricFun = std::make_shared<GeoMetricFun2d_Uniform>(0, name, m, *myRegion);
		exeTag = true;

		if (verbose)
		{
			Info << " - The metric is created, successfully!" << endl;
		}
	}

	void createMap(const Entity2d_Metric1& m)
	{
		createMap("metric", m);
	}

	void createMap(const std::string& name, const Entity2d_Metric2& m)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}
		myMetricFun = std::make_shared<GeoMetricFun2d_Uniform>(0, name, m, *myRegion);
		exeTag = true;

		if (verbose)
		{
			Info << " - The metric is created, successfully!" << endl;
		}
	}

	void createMap(const Entity2d_Metric2& m)
	{
		createMap("metric", m);
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

		file::SaveTo(myMetricFun, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		saveTo(myMetricFun->Name());
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
		// io functions [12/9/2021 Amir]
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/9/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/9/2021 Amir]
		mod->add(chaiscript::fun([](double x, double y)-> auto {return createDir(x, y); }), "createDirection");
		mod->add(chaiscript::fun([](double h1, double h2, const gp_Dir2d& d1, const gp_Dir2d& d2)-> auto {return createMetric(h1, h2, d1, d2); }), "createMetric");
		mod->add(chaiscript::fun([](double a, double b, double c)-> auto {return createMetric(a, b, c); }), "createMetric");

		mod->add(chaiscript::fun([](const Entity2d_Metric1& m)-> void {createMap(m); }), "createMap");
		mod->add(chaiscript::fun([](const std::string& name, const Entity2d_Metric1& m)-> void {createMap(name, m); }), "createMap");
		mod->add(chaiscript::fun([](const Entity2d_Metric2& m)-> void {createMap(m); }), "createMap");
		mod->add(chaiscript::fun([](const std::string& name, const Entity2d_Metric2& m)-> void {createMap(name, m); }), "createMap");
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
			Info << " This application is aimed to create a uniform metric map." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - [Dir] createDirection(x, y)" << endl
				<< " - [Metric] createMetric(a, b, c)" << endl
				<< " - [Metric] createMetric(h1, h2, Dir1, Dir2)" << endl
				<< " - createMap(name [optional], Metric)" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshPlaneMetricMapUniform"));

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