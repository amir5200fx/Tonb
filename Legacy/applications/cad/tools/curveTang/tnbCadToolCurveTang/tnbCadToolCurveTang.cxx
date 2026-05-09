#include <Cad_GeomCurve.hxx>
#include <Vec3d.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp_Pnt.hxx>
#include <gp_Vec.hxx>
#include <Geom_Curve.hxx>

namespace tnbLib
{

	static const std::string loadExt = Cad_GeomCurve::extension;
	static std::shared_ptr<Cad_GeomCurve> myCurve;
	static bool loadTag = false;

	static unsigned short verbose(0);

	static double myPar = 0;
	static bool parTag = false;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setPar(double x)
	{
		myPar = x;
		parTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the parameter is set to: " << x << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		myCurve = file::LoadFile<std::shared_ptr<Cad_GeomCurve>>(name + loadExt, verbose);
		if (NOT myCurve)
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is null!" << endl
				<< abort(FatalError);
		}

		if (NOT parTag)
		{
			myPar = myCurve->FirstParameter();
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), loadExt).string();
		loadFile(name);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& geom = myCurve->Geometry();

		auto u0 = geom->FirstParameter();
		auto u1 = geom->LastParameter();

		if (NOT INSIDE(myPar, u0, u1))
		{
			if (myPar < u0) myPar = u0;
			if (myPar > u0) myPar = u1;
			if (verbose)
			{
				Info << endl
					<< " - WARNING: the parameter, u = " << myPar << ", exceeds the span of the knot vector!" << endl
					<< " - modified parameter: " << myPar << endl
					<< abort(FatalError);
			}
		}

		gp_Pnt pt;
		gp_Vec vec;
		geom->D1(myPar, pt, vec);

		Info << endl;
		Info << " - U0: " << u0 << endl;
		Info << " - Un: " << u1 << endl;
		Info << endl;

		Info << " - Coord: " << pt << endl;
		Info << " - Tang: " << vec << endl;
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

		//- settings
		mod->add(chaiscript::fun([](unsigned short t)->void {setVerbose(t); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setPar(x); }), "setParameter");

		//- operators
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
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
			Info << " This application is aimed to calculate the tangent of a curve at a specific parameter." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl
				<< " - loadFile(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setParameter(double)" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl
				<<" - execute()" << endl
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
				fileName theFileName(file::GetSystemFile("tnbCadToolCurveTang"));

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