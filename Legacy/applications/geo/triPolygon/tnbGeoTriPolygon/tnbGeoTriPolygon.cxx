#include <Geo2d_PolygonDelTri.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_EXETAG_OBJ;

	static std::vector<std::shared_ptr<Entity2d_Polygon>> myPolygons;
	static std::shared_ptr<Entity2d_Triangulation> myTri;

	TNB_SET_VERBOSE_FUN;

	void loadFiles()
	{
		auto currentPath = boost::filesystem::current_path().string();
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			size_t i = 0;
			while (boost::filesystem::is_directory(boost::filesystem::path(std::to_string(i))))
			{
				auto current = currentPath + R"(\)" + std::to_string(i);
				auto name = file::GetSingleFile(current, Entity2d_Polygon::extension).string();
				file::CheckExtension(name);
				file::SetCurrentPath(current);
				auto ent = file::LoadFile<std::shared_ptr<Entity2d_Polygon>>(name + Entity2d_Polygon::extension, verbose);
				TNB_CHECK_LOADED_FILE(ent);
				
				myPolygons.push_back(std::move(ent));
				++i;
				file::SetCurrentPath(currentPath);
			}
		}
		file::SetCurrentPath(currentPath);
		if (verbose)
		{
			Info << endl
				<< " - " << myPolygons.size()
				<< " polygons are loaded successfully in "
				<< global_time_duration
				<< " ms."
				<< endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		TNB_CHECK_EXE_TAG;
		file::SaveTo(myTri, name + Entity2d_Triangulation::extension, verbose);
	}

	void execute()
	{
		TNB_CHECK_LOADED;
		{
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			auto delTri = std::make_shared<Geo2d_PolygonDelTri>(myPolygons);
			delTri->Perform();
			myTri = delTri->Triangulation();
		}
		if (verbose)
		{
			Info << endl
				<< " - The application is successfully performed, in " << global_time_duration << " ns." << endl;
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
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");

		//- Settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- operators
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
			Info << endl;
			Info << " This application is aimed to triangulate a two-dimensional polygon." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name)" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl
				<< endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFunctions(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbGeoTriPolygon"));

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