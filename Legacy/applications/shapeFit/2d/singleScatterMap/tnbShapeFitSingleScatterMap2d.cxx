#include <PtdShapeFit2d_SingleScatterMap.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static std::shared_ptr<PtdShapeFit2d_ScatterMap> myScatterMap;
	static std::vector<std::shared_ptr<Entity2d_Polygon>> myPolys;

	static unsigned short verbose = 0;
	static auto loadTag = false;
	static auto exeTag = false;

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

	void loadPolygons()
	{
		checkFolder("polygon");

		const auto currentPath = boost::filesystem::current_path();

		// change the current path [2/6/2023 Payvand]
		boost::filesystem::current_path(currentPath.string() + R"(\polygon)");

		if (file::IsFile(boost::filesystem::current_path(), ".PATH"))
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), ".PATH").string();
			fileName fn(name + ".PATH");

			std::ifstream myFile;
			myFile.open(fn);
			if (myFile.is_open())
			{
				std::string address;
				while (std::getline(myFile, address))
				{
					// change the current path [2/6/2023 Payvand]
					boost::filesystem::current_path(address);

					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity2d_Polygon::extension).string();

						auto pl = file::LoadFile<std::shared_ptr<Entity2d_Polygon>>(name + Entity2d_Polygon::extension, verbose);
						if (NOT pl)
						{
							FatalErrorIn(FunctionSIG)
								<< " the polygon is null." << endl
								<< abort(FatalError);
						}

						myPolys.push_back(std::move(pl));
					}
				}
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "the file is not open: " << name + ".PATH" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity2d_Polygon::extension).string();

			auto pl = file::LoadFile<std::shared_ptr<Entity2d_Polygon>>(name + Entity2d_Polygon::extension, verbose);
			if (NOT pl)
			{
				FatalErrorIn(FunctionSIG)
					<< " the polygon is null." << endl
					<< abort(FatalError);
			}
			myPolys.push_back(std::move(pl));
		}
		//- change back the current path
		boost::filesystem::current_path(currentPath);
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		auto pl = file::LoadFile<std::shared_ptr<Entity2d_Polygon>>(name + Entity2d_Polygon::extension, verbose);
		if (NOT pl)
		{
			FatalErrorIn(FunctionSIG)
				<< "the polygon is null!" << endl
				<< abort(FatalError);
		}
		myPolys.push_back(std::move(pl));
	}

	void loadFile()
	{
		if (boost::filesystem::is_directory("polygon"))
		{
			loadPolygons();
		}
		else
		{
			auto name = file::GetSingleFile(boost::filesystem::current_path(), Entity2d_Polygon::extension).string();
			loadFile(name);
		}
		loadTag = true;
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

		file::SaveTo(myScatterMap, name + PtdShapeFit2d_ScatterMap::extension, verbose);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			Info << endl
				<< "no file has been loaded" << endl
				<< abort(FatalError);
		}

		auto pnts = std::make_shared<std::vector<Pnt2d>>();
		for (const auto& pl : myPolys)
		{
			for (const auto& x : pl->Points())
			{
				pnts->push_back(x);
			}
		}
		myScatterMap = std::make_shared<PtdShapeFit2d_SingleScatterMap>(std::move(pnts));

		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}

		exeTag = true;
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

		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- settings

		mod->add(chaiscript::fun([](unsigned short i)->void {verbose = i; }), "setVerbose");

		// Operators [2/11/2023 Payvand]
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
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
	//sysLib::init_gl_marine_integration_info();
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
			Info << endl;
			Info << " This application is aimed to create a two-dimensional scatter map for shape fitting." << endl
				<< " - It loads one polygon as a file or multiple polygons with a path file." << endl
				<< " - The path file must be provided in a 'polygon' directory." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name)" << endl << endl

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

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbShapeFitSingleScatterMap2d"));
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
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}