#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	static const std::string loadExt = Entity2d_Box::extension;
	static const std::string saveExt = Geo2d_SizeFunction::extension;

	static std::shared_ptr<Entity2d_Box> myBox;
	static double mySize = 0.01;
	static bool setSize = false;

	static std::shared_ptr<Geo_SizeFunction<Pnt2d>> myFun;
	static unsigned short verbose(0);

	static bool loadTag = false;
	static bool exeTag = false;

	void setElmSize(double x)
	{
		mySize = x;
		setSize = true;
		if (verbose)
		{
			Info << endl
				<< " - the size is set to: " << mySize << endl;
		}
	}

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myBox = file::LoadFile<std::shared_ptr<Entity2d_Box>>(name + loadExt, verbose);
		if (NOT myBox)
		{
			FatalErrorIn(FunctionSIG)
				<< "the file object is null!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
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

		file::SaveTo(myFun, name + saveExt, verbose);
	}

	void saveTo()
	{
		if (NOT myFun->Name().empty())
		{
			saveTo(myFun->Name());
		}
		else
		{
			saveTo("sizeFun");
		}
	}

	void execute(const std::string& name)
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT setSize)
		{
			FatalErrorIn(FunctionSIG)
				<< "no size has been set" << endl
				<< abort(FatalError);
		}

		myFun = std::make_shared<GeoSizeFun2d_Uniform>(0, name, mySize, *myBox);
		//Geo2d_SizeFunction xx = GeoSizeFun2d_Uniform(0, name, mySize, *myBox);

		exeTag = true;
	}

	void execute()
	{
		execute("");
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
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](double x)-> void {setElmSize(x); }), "setSize");
		mod->add(chaiscript::fun([](unsigned short n)-> void {setVerbose(n); }), "setVerbose");

		//- operators
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
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
			Info << " This application is aimed to create an uniform size function." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setSize(double)" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - execute(name [optional])" << endl
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
				//std::string address = ".\\system\\tnbMeshCurve2d";
				fileName theFileName(file::GetSystemFile("tnbGeoSizeFunUniform"));

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