#include <Cad_GeomSurface.hxx>
#include <Cad_GeomCurve.hxx>
#include <Cad_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>

namespace tnbLib
{
	static const std::string loadExt = Cad_GeomSurface::extension;
	static const std::string saveExt = Cad_GeomCurve::extension;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Cad_GeomSurface> mySurface;
	static std::string myFileName;

	static std::shared_ptr<Cad_GeomCurve> U0;
	static std::shared_ptr<Cad_GeomCurve> Un;
	static std::shared_ptr<Cad_GeomCurve> V0;
	static std::shared_ptr<Cad_GeomCurve> Vn;

	static unsigned short verbose(0);

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySurface = file::LoadFile<std::shared_ptr<Cad_GeomSurface>>(name + loadExt, verbose);
		if (NOT mySurface)
		{
			FatalErrorIn(FunctionSIG)
				<< "the surface is null" << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt);
		myFileName = name.string();
		loadFile(myFileName);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		{
			size_t i = 0;
			std::string name = "u0";

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address + saveExt);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << U0;

			if (verbose)
			{
				Info << " the file, " << i << ", is saved in: " << address << ", successfully!" << endl;
			}
		}

		{
			size_t i = 1;
			std::string name = "un";

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address + saveExt);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << Un;

			if (verbose)
			{
				Info << " the file, " << i << ", is saved in: " << address << ", successfully!" << endl;
			}
		}

		{
			size_t i = 2;
			std::string name = "v0";

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address + saveExt);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << V0;

			if (verbose)
			{
				Info << " the file, " << i << ", is saved in: " << address << ", successfully!" << endl;
			}
		}

		{
			size_t i = 3;
			std::string name = "vn";

			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address + saveExt);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << Vn;

			if (verbose)
			{
				Info << " the file, " << i << ", is saved in: " << address << ", successfully!" << endl;
			}
		}
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no shape has been loaded, yet!" << endl
				<< abort(FatalError);
		}

		auto surface = Handle(Geom_BSplineSurface)::DownCast(mySurface->Geometry());
		if (NOT surface)
		{
			FatalErrorIn(FunctionSIG)
				<< "the surface is not bspline!" << endl
				<< abort(FatalError);
		}

		{
			auto geom = Cad_Tools::BoundaryCurveU0(surface);
			U0 = std::make_shared<Cad_GeomCurve>(std::move(geom));
		}

		{
			auto geom = Cad_Tools::BoundaryCurveUn(surface);
			Un = std::make_shared<Cad_GeomCurve>(std::move(geom));
		}

		{
			auto geom = Cad_Tools::BoundaryCurveV0(surface);
			V0 = std::make_shared<Cad_GeomCurve>(std::move(geom));
		}

		{
			auto geom = Cad_Tools::BoundaryCurveVn(surface);
			Vn = std::make_shared<Cad_GeomCurve>(std::move(geom));
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
		mod->add(chaiscript::fun([](const std::string& name)->void {loadFile(name); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([]()->void {saveTo(); }), "saveTo");

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");

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
			Info << " This application is aimed to retrieve boundary curves of a bspline surface." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl
				<< " - saveTo()" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl
				<< " - execute()"
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
				fileName theFileName(file::GetSystemFile("tnbCadToolGetBndCurves"));

				chai.eval_file(theFileName);
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