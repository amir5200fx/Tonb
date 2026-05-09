#include <Cad_GeomSurface.hxx>
#include <Cad_PreviewTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <Global_Timer.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_Surface.hxx>
#include <Geom_BSplineSurface.hxx>

namespace tnbLib
{

	static const std::string loadExt = Cad_GeomSurface::extension;
	static const std::string saveExt = Entity3d_Triangulation::extension;

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	static std::string myFileName;
	static std::shared_ptr<Cad_GeomSurface> mySurf;
	static std::shared_ptr<Entity3d_Triangulation> myTri;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySurf = file::LoadFile<std::shared_ptr<Cad_GeomSurface>>(name + loadExt, verbose);
		if (NOT mySurf)
		{
			FatalErrorIn(FunctionSIG)
				<< "the shape is null!" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << " - surface's name: " << mySurf->Name() << endl;
			Info << endl;
		}
		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadFile(myFileName);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name + saveExt);
		std::ofstream myFile(fn);

		TNB_oARCH_FILE_TYPE ar(myFile);
		ar << myTri;

		myFile.close();

		if (verbose)
		{
			Info << endl;
			Info << " the file is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application has not been performed!" << endl
				<< abort(FatalError);
		}

		saveTo(myFileName);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		auto patch = Handle(Geom_BSplineSurface)::DownCast(mySurf->Geometry());
		if (NOT patch)
		{
			FatalErrorIn(FunctionSIG)
				<< "the surface is not bspline!" << endl
				<< abort(FatalError);
		}

		const auto& poles = patch->Poles();

		std::vector<std::vector<Pnt3d>> rows;
		rows.reserve(poles.ColLength());
		for (int i = 1; i <= poles.ColLength(); i++)
		{
			std::vector<Pnt3d> row;
			row.reserve(poles.RowLength());
			for (int j = 1; j <= poles.RowLength(); j++)
			{
				auto pt = Pnt3d(poles(i, j));
				row.push_back(std::move(pt));
			}
			rows.push_back(std::move(row));
		}
		auto chain = Cad_PreviewTools::RetrieveChain(rows);
		myTri = Geo_Tools::Triangulation(*chain);

		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
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

	void setGlobals(const module_t& mod)
	{

		//- IO functions:
		mod->add(chaiscript::fun([](const std::string& name)->void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		//- Settings:
		mod->add(chaiscript::fun([](unsigned short c)->void {setVerbose(c); }), "setVerbose");

		//- operators:
		mod->add(chaiscript::fun([]() ->void {execute(); }), "execute");
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
			Info << " This application is aimed to retrieve the control net of a BSpline surface." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
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

			setGlobals(mod);

			chai.add(mod);

			try
			{
				//std::string address = ".\\system\\tnbSurfacePolesViewer";
				fileName theFileName(file::GetSystemFile("tnbSurfacePolesViewer"));

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