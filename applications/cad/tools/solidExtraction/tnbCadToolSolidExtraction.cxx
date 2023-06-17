#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace fs = boost::filesystem;

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static const auto model_directory = "shape";

	static std::shared_ptr<Cad_Shape> myShape;
	static std::vector<std::shared_ptr<Cad_Shape>> mySolids;
	static std::string myFileName;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadShape()
	{
		myShape = file::LoadSingleFile<std::shared_ptr<Cad_Shape>>
			(
				model_directory,
				Cad_Shape::extension,
				verbose,
				myFileName
				);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadShapeFile(const std::string& name)
	{
		file::CheckExtension(name);
		myShape =
			file::LoadFile<std::shared_ptr<Cad_Shape>>
			(name + Cad_Shape::extension, verbose);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
		myFileName = name;
	}

	void loadFile()
	{
		if (file::IsDirectory(model_directory))
		{
			loadShape();
		}
		else
		{
			auto name =
				file::GetSingleFile

				(boost::filesystem::current_path(),
					Cad_Shape::extension
				).string();
			loadShapeFile(name);
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}
		auto current = fs::current_path().string();
		std::string address = current + "\\results";
		fs::path dir(address);
		if (NOT fs::is_directory(dir))
		{
			fs::create_directory(dir);
		}
		else
		{
			file::RemoveDirectory(dir);
			fs::create_directory(dir);
		}
		fs::current_path(dir);

		size_t i = 0;
		for (const auto& x : mySolids)
		{
			std::string icurrent = address + "\\" + std::to_string(i);

			fs::path idir(std::to_string(i));
			fs::create_directory(idir);

			fs::current_path(icurrent);

			file::SaveTo(x, name + Cad_Shape::extension, verbose);

			fs::current_path(dir);

			++i;
		}
		fs::current_path(current);
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

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded." << endl
				<< abort(FatalError);
		}

		auto shapes = Cad_Tools::RetrieveSolids(myShape->Shape());
		if (verbose)
		{
			Info << endl
				<< " - no. of detected solids: " << shapes.size() << endl;
		}
		int k = 0;
		for (const auto& x : shapes)
		{
			auto shape = 
				std::make_shared<Cad_Shape>(++k, myShape->Name() + " " + std::to_string(k), x);
			mySolids.push_back(std::move(shape));
		}
		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
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

	void setFuns(const module_t& mod)
	{
		// io functions [12/21/2021 Amir]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadShapeFile(name); }), "loadFile");

		// settings [12/21/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/21/2021 Amir]
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
			Info << " This application is aimed to extract the solids of a shape." << endl << endl;

			Info << " You can load the shape from 'shape' directory." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
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
				fileName myFileName(file::GetSystemFile("tnbCadToolSolidExtraction"));

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