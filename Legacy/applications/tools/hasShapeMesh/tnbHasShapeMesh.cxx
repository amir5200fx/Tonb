#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <TopoDS_Shape.hxx>
#include <BRepTools.hxx>

namespace tnbLib
{

	static const std::string extension = Cad_Shape::extension;

	static unsigned short verbose(0);
	static bool exeTag = false;
	static bool loadTag = false;

	static std::shared_ptr<Cad_Shape> myShape;
	static std::string myFileName;

	static bool hasMesh = false;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadModel(const std::string& name)
	{
		file::CheckExtension(name);

		myShape = file::LoadFile<std::shared_ptr<Cad_Shape>>(name + extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}
		if (verbose)
		{
			Info << " - shape's name: " << myShape->Name() << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void loadModel()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension);
		myFileName = name.string();
		loadModel(myFileName);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		if (myShape)
		{
			const auto& shape = myShape->Shape();
			hasMesh = Cad_Tools::HasTriangulation(shape);
		}

		if (verbose)
		{
			Info << endl
				<< " - Has been discretized? " << (hasMesh ? "YES" : "NO") << endl
				<< endl
				<< " The application is performed, successfully!" << endl;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([]()-> void {loadModel(); }), "loadModel");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		//- apps
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

int main(int argc, char *argv[])
{

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit(2);
	}

	if (argc IS_EQUAL 2)
	{

		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << endl;
			Info << "This application is aimed to clean the mesh of surfaces." << endl;
			Info << endl;
			Info << " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadModel(name [optional])" << endl
				<< endl
				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl
				<< endl
				<< " # Operators: " << endl << endl

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
				//std::string address = ".\\system\\tnbHasShapeMesh";
				fileName myFileName(file::GetSystemFile("tnbHasShapeMesh"));

				chai.eval_file(myFileName);
				if (NOT hasMesh)
					return 1;
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
	return 2;
}