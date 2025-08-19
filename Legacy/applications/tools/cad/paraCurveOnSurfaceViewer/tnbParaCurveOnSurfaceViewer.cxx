#include <Cad_GeomSurface.hxx>
#include <Cad_GeomCurve.hxx>
#include <Pln_Edge.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/filesystem.hpp>

#include <Geom_Surface.hxx>

namespace tnbLib
{

	static unsigned short verbose(0);

	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Cad_GeomSurface> my_surface;
	static std::shared_ptr<Pln_Edge> myCurve;

	static std::shared_ptr<Entity3d_Triangulation> myMesh;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	auto getAllFilesNames(const boost::filesystem::path& p)
	{
		boost::filesystem::directory_iterator end_itr;

		std::vector<std::string> names;
		for (boost::filesystem::directory_iterator iter(p); iter != end_itr; iter++)
		{
			if (boost::filesystem::is_regular_file(iter->path()))
			{
				auto file = iter->path().filename().string();
				names.push_back(std::move(file));
			}
		}
		return std::move(names);
	}

	auto getSingleFile(const boost::filesystem::path& p)
	{
		auto files = getAllFilesNames(p);
		if (files.size())
		{
			return files[0];
		}
		return std::string();
	}

	void loadModels()
	{
		{ //- loading the surface
			boost::filesystem::path dir("surface");
			if (NOT boost::filesystem::is_directory(dir))
			{
				FatalErrorIn(FunctionSIG)
					<< "no 'surface' directory has been found!" << endl
					<< abort(FatalError);
			}

			auto name = getSingleFile(dir);

			fileName fn(name);
			std::string address = ".\\surface\\" + name;

			std::fstream file;

			file.open(address, std::ios::in);
			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to open the file: " << address << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ar(file);

			{//- timer scope
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				ar >> my_surface;
			}

			if (NOT my_surface)
			{
				FatalErrorIn(FunctionSIG)
					<< "the surface is null!" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << " The surface has been loaded from: " << address << ", successfully in " << global_time_duration << " ms." << endl;
				Info << " - surface name: " << my_surface->Name() << endl;
			}
		}

		{ //- loading the curve
			boost::filesystem::path dir("curve");
			if (NOT boost::filesystem::is_directory(dir))
			{
				FatalErrorIn(FunctionSIG)
					<< "no 'curve' directory has been found!" << endl
					<< abort(FatalError);
			}

			auto name = getSingleFile(dir);

			fileName fn(name);
			std::string address = ".\\curve\\" + name;

			std::fstream file;

			file.open(address, std::ios::in);
			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to open the file: " << address << endl
					<< abort(FatalError);
			}

			TNB_iARCH_FILE_TYPE ar(file);

			{//- timer scope
				Global_Timer timer;
				timer.SetInfo(Global_TimerInfo_ms);

				ar >> myCurve;
			}

			if (NOT myCurve)
			{
				FatalErrorIn(FunctionSIG)
					<< "the curve is null!" << endl
					<< abort(FatalError);
			}

			if (verbose)
			{
				Info << " The curve has been loaded from: " << address << ", successfully in " << global_time_duration << " ms." << endl;
				Info << " - curve name: " << myCurve->Name() << endl;
			}
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " the application is not performed!" << endl
				<< abort(FatalError);
		}

		fileName fn(name);
		std::ofstream f(fn);

		TNB_oARCH_FILE_TYPE oa(f);
		oa << myMesh;

		if (verbose)
		{
			Info << endl;
			Info << " the model is saved in: " << fn << ", successfully!" << endl;
			Info << endl;
		}
	}

	void checkBounds(const Pnt2d& pt, const Entity2d_Box& b)
	{
		if (NOT b.IsInside(pt))
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the parametric domain!" << endl
				<< abort(FatalError);
		}
	}

	auto calcPoint(const Pnt2d& pt, const Geom_Surface& s)
	{
		auto p3 = Pnt3d(s.Value(pt.X(), pt.Y()));
		return std::move(p3);
	}

	void execute()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< " no file has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& poly = myCurve->Mesh();
		if (NOT poly)
		{
			FatalErrorIn(FunctionSIG)
				<< "the curve is not discretized!" << endl
				<< abort(FatalError);
		}

		const auto domain = my_surface->ParametricBoundingBox();

		auto chain = std::make_shared<Entity3d_Chain>();
		auto& points = chain->Points();
		points.reserve(poly->NbPoints());

		for (const auto& x : poly->Points())
		{
			checkBounds(x, domain);

			auto pt = calcPoint(x, *my_surface->Geometry());
			points.push_back(std::move(pt));
		}
		
		chain->Connectivity() = dualConnectivityList_Chain(poly->NbPoints() - 1);
		myMesh = Geo_Tools::Triangulation(*chain);

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

	void setGlobals(const module_t& mod)
	{
		mod->add(chaiscript::fun([]()->void {loadModels(); }), "loadModels");
		mod->add(chaiscript::fun([]()->void {execute(); }), "execute");
		mod->add(chaiscript::fun([](const std::string& name)->void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([](int i)->void {verbose = i; }), "setVerbose");
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
			Info << " This application is aimed to create a 3D mesh from a parametric curve of a surface." << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # I/O functions: " << endl
				<< " - loadModels()" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Settings: " << endl << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # functions: " << endl << endl

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

			std::string address = ".\\system\\tnbPlotParaCurveOnSurface";
			fileName myFileName(address);

			try
			{
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