#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <memory>

namespace tnbLib
{

	static std::shared_ptr<Entity2d_Triangulation> myTris2d;
	static std::shared_ptr<Entity3d_Triangulation> myTris3d;

	static auto model_directory = "mesh";

	TNB_DEFINE_VERBOSE_OBJ;
	TNB_DEFINE_LOADTAG_OBJ;
	TNB_DEFINE_FILENAME_OBJ;
	TNB_DEFINE_EXETAG_OBJ;

	TNB_SET_VERBOSE_FUN;

	TNB_STANDARD_LOAD_SAVE_POINTER_OBJECT(myTris2d, model_directory, myTris3d);

	void execute()
	{
		TNB_CHECK_LOADED;
		Entity3d_Triangulation tris;
		std::vector<Pnt3d> pts;
		pts.reserve(myTris2d->NbPoints());
		for (const auto& x : myTris2d->Points())
		{
			Pnt3d p3(x.X(), x.Y(), 0);
			pts.push_back(std::move(p3));
		}
		tris.Points() = std::move(pts);
		tris.Connectivity() = myTris2d->Connectivity();
		myTris3d = std::make_shared<Entity3d_Triangulation>(std::move(tris));
		TNB_EXECUTE_TAG;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadModel(name); }), "loadFile");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		// settings [12/9/2021 Amir]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators [12/9/2021 Amir]
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
			Info << " This application is aimed to convert a two-dimensional mesh to a surface mesh." << endl << endl

				<< " You can load the two-dimensional mesh file from a subdirectory." << endl
				<< " # Subdirectories:" << endl
				<< endl
				<< " - mesh" << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute(name [optional])" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMesh2dToSurface"));

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