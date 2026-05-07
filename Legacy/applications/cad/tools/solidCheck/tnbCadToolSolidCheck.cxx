#include <Cad_Shape.hxx>
#include <Cad_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static unsigned short verbose = 0;
	static bool loadTag = false;


	static const auto model_directory = "shape";

	static std::shared_ptr<Cad_Shape> myShape;

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
				verbose
				);
		if (NOT myShape)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded." << endl
				<< abort(FatalError);
		}
		loadTag = true;
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
		loadTag = true;
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
		Info << " # no. of solids: " << shapes.size() << endl;
		int k = 0;
		for (const auto& x : shapes)
		{
			++k;
			if (Cad_Tools::IsValidSolid(x))
			{
				Info << " - solid no. " << k << ", is valid? YES; volume: " << Cad_Tools::CalcVolume(x) << endl;
			}
			else
			{
				Info << " - solid no. " << k << ", is valid? NO." << endl;
			}
		}
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
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");

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
			Info << " This application is aimed to check a solid." << endl << endl;
				
			Info << " You can load the shape from 'shape' directory." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile()" << endl

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

			setFuns(mod);

			chai.add(mod);

			//std::string address = ".\\system\\mesh2dToPlt";

			try
			{
				fileName myFileName(file::GetSystemFile("tnbCadToolSolidCheck"));
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