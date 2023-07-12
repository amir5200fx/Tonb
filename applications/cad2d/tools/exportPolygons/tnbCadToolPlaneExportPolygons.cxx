#include <Cad2d_Plane.hxx>
#include <Pln_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_EXETAG_OBJ;
	TNB_DEFINE_FILENAME_OBJ;
	static const auto model_directory = "model";

	static std::shared_ptr<Cad2d_Plane> myPlane;
	static std::vector<std::shared_ptr<Entity2d_Polygon>> myPolygons;

	TNB_SET_VERBOSE_FUN;

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);
		myPlane = 
			file::LoadFile<std::shared_ptr<Cad2d_Plane>>
			(name + Cad2d_Plane::extension, verbose);
		TNB_CHECK_LOADED_FILE(myPlane);
		myFileName = name;
		loadTag = true;
	}

	void loadModel()
	{
		myPlane = file::LoadSingleFile<std::shared_ptr<Cad2d_Plane>>
			(model_directory, Cad2d_Plane::extension, verbose, myFileName);
		TNB_CHECK_LOADED_FILE(myPlane);
		loadTag = true;
	}

	void loadFile()
	{
		if (file::IsDirectory(model_directory))
		{
			loadModel();
		}
		else
		{
			auto name = 
				file::GetSingleFile(boost::filesystem::current_path(), Cad2d_Plane::extension)
				.string();
			loadModel(name);
		}
	}

	TNB_SAVE_MULTI_FILES_FUN("results", Entity2d_Polygon::extension, myPolygons);

	void saveTo()
	{
		TNB_CHECK_LOADED;
		saveTo(myFileName);
	}

	void execute()
	{
		TNB_CHECK_LOADED;
		const auto& wire = myPlane->OuterWire();
		auto wires = Pln_Tools::RetrieveWires(*myPlane);
		for (const auto& x : wires)
		{
			myPolygons.push_back(Pln_Tools::RetrievePolygon(*x));
		}
		TNB_PERFORMED_TAG;
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
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

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
			Info << " This application is aimed to retrieve polygons from a plane." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl

				<< " - loadFile()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute()" << endl
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
				fileName myFileName(file::GetSystemFile("tnbCadToolPlaneExportPolygons"));

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