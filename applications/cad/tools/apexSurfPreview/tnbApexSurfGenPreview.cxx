#include <Cad_GeomSurface.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Tools.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom_BSplineSurface.hxx>

#include <boost/filesystem.hpp>

namespace tnbLib
{

	static bool loadTag = false;
	static bool exeTag = false;
	static unsigned short verbose(0);

	static std::shared_ptr<Cad_GeomSurface> mySurf;

	static std::string myBoundary = "u0";
	static int nbSegments = 20;

	static gp_Ax1 myAxis;

	static std::vector<std::shared_ptr<Entity3d_Triangulation>> myTris;

	void setVerbose(unsigned short i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setNbSegments(int n)
	{
		nbSegments = n;
		if (verbose)
		{
			Info << endl
				<< " - the nb. of segments is set to: " << nbSegments << endl;
		}
	}

	void setApexLoc(const Pnt3d& loc)
	{
		myAxis.SetLocation(loc);
		if (verbose)
		{
			Info << " - the apex location is set to: " << myAxis.Location() << endl;
		}
	}

	void setApexDir(const Dir3d& d)
	{
		myAxis.SetDirection(d);
		if (verbose)
		{
			Info << " - the apex direction is set to: " << myAxis.Direction() << endl;
		}
	}

	void setBoundary(const std::string& b)
	{
		myBoundary = b;
		if (verbose)
		{
			Info << " - the boundary is set to: " << myBoundary << endl;
		}
	}

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		if (verbose)
		{
			Info << endl;
			Info << " loading the model from, " << fn << endl;
			Info << endl;
		}
		std::ifstream myFile(fn);
		{//- timer scope
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_ms);

			TNB_iARCH_FILE_TYPE ar(myFile);
			ar >> mySurf;
		}

		if (NOT mySurf)
		{
			FatalErrorIn(FunctionSIG)
				<< " the loaded model is null" << endl
				<< abort(FatalError);
		}

		if (verbose)
		{
			Info << endl;
			Info << " the model is loaded, from: " << name << ", successfully in " << global_time_duration << " ms." << endl;
			Info << endl;
		}

		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}

		size_t i = 0;
		for (const auto& x : myTris)
		{
			std::string address = ".\\" + std::to_string(i) + "\\" + name;
			boost::filesystem::path dir(std::to_string(i));
			boost::filesystem::create_directory(dir);

			std::ofstream file(address);

			TNB_oARCH_FILE_TYPE oa(file);

			oa << x;

			if (verbose)
			{
				Info << " - surface " << i << " saved in: " << address << ", successfully!" << endl;
			}
			i++;
		}

		if (verbose)
		{
			Info << endl
				<< " All files are saved, successfully!" << endl;
		}
	}

	auto calcBoundaryCurve(const std::shared_ptr<Cad_GeomSurface>& s, const std::string& bnd)
	{
		const auto b = s->ParametricBoundingBox();
		if (bnd IS_EQUAL "u0")
		{
			auto p0 = b.Corner(Box2d_PickAlgorithm_NW);
			auto p1 = b.Corner(Box2d_PickAlgorithm_SW);

			auto curve = Pln_CurveTools::MakeSegment(p0, p1);
			return std::move(curve);
		}
		else if (bnd IS_EQUAL "un")
		{
			auto p0 = b.Corner(Box2d_PickAlgorithm_SE);
			auto p1 = b.Corner(Box2d_PickAlgorithm_NE);

			auto curve = Pln_CurveTools::MakeSegment(p0, p1);
			return std::move(curve);
		}
		else if (bnd IS_EQUAL "v0")
		{
			auto p0 = b.Corner(Box2d_PickAlgorithm_SW);
			auto p1 = b.Corner(Box2d_PickAlgorithm_SE);

			auto curve = Pln_CurveTools::MakeSegment(p0, p1);
			return std::move(curve);
		}
		else if (bnd IS_EQUAL "vn")
		{
			auto p0 = b.Corner(Box2d_PickAlgorithm_NE);
			auto p1 = b.Corner(Box2d_PickAlgorithm_NW);

			auto curve = Pln_CurveTools::MakeSegment(p0, p1);
			return std::move(curve);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< " no boundary type has been detected!" << endl
				<< " - boundary type: " << bnd << endl
				<< " - valid boundaries: u0, un, v0, and vn" << endl
				<< abort(FatalError);
			Handle(Geom2d_Curve) curve;
			return std::move(curve);
		}
	}

	auto calcApexTri(const std::shared_ptr<Entity3d_Polygon>& poly, const Pnt3d& c)
	{
		auto tri = std::make_shared<Entity3d_Triangulation>();
		auto& points = tri->Points();
		points = poly->Points();
		points.push_back(c);

		auto& indices = tri->Connectivity();
		indices.reserve(poly->NbPoints() - 1);
		for (auto i = 1; i < poly->NbPoints(); i++)
		{
			auto i0 = i;
			auto i1 = i + 1;
			auto i2 = poly->NbPoints() + 1;

			connectivity::triple I;
			I.Value(0) = i0;
			I.Value(1) = i1;
			I.Value(2) = i2;

			indices.push_back(std::move(I));
		}
		return std::move(tri);
	}

	auto calcPoly3D(const Handle(Geom_Surface)& s, const std::vector<Pnt2d>& pnts)
	{
		auto poly = std::make_shared<Entity3d_Polygon>();
		auto& points = poly->Points();
		points.reserve(pnts.size());
		for (const auto& x : pnts)
		{
			auto pt = Pnt3d(s->Value(x.X(), x.Y()));
			points.push_back(std::move(pt));
		}
		return std::move(poly);
	}

	auto calcAxisTri(double l, const Pnt3d& c, const Dir3d& dir)
	{
		auto p1 = c + l * Pnt3d(dir.XYZ());
		auto poly = std::make_shared<Entity3d_Polygon>();
		auto& pnts = poly->Points();
		pnts.push_back(c);
		pnts.push_back(p1);

		auto chain = Geo_Tools::RetrieveChain(*poly);
		auto tri = Geo_Tools::Triangulation(*chain);
		return std::move(tri);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded!" << endl
				<< abort(FatalError);
		}

		auto b = mySurf->BoundingBox();
		const auto d = b.Diameter();

		auto curve = calcBoundaryCurve(mySurf, myBoundary);
		auto poly = calcPoly3D(mySurf->Geometry(), Pln_Tools::UniformDiscrete(curve, nbSegments)->Points());
		auto chain = Geo_Tools::RetrieveChain(*poly);

		auto curveTri = Geo_Tools::Triangulation(*chain);
		auto axisTri = calcAxisTri(d, myAxis.Location(), myAxis.Direction());
		auto apexTri = calcApexTri(poly, myAxis.Location());

		myTris.push_back(std::move(curveTri));
		myTris.push_back(std::move(axisTri));
		myTris.push_back(std::move(apexTri));

		exeTag = true;

		if (verbose)
		{
			Info << endl
				<< " the application is performed, successfully!" << endl;
		}
	}

	auto createPoint(double x, double y, double z)
	{
		return Pnt3d(x, y, z);
	}

	auto createDir(double x, double y, double z)
	{
		return Dir3d(x, y, z);
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

		//- io functions

		mod->add(chaiscript::fun([](const std::string& name)->void {loadModel(name); }), "loadModel");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");

		//- methods
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return createPoint(x, y, z); }), "createPoint");
		mod->add(chaiscript::fun([](double x, double y, double z) -> auto {return createDir(x, y, z); }), "createDirection");

		//- settings
		mod->add(chaiscript::fun([](unsigned short i)-> void {verbose = i; }), "setVerbose");
		mod->add(chaiscript::fun([](const Pnt3d& p)-> void {setApexLoc(p); }), "setApexLoc");
		mod->add(chaiscript::fun([](const Dir3d& d)-> void {setApexDir(d); }), "setApexDir");
		mod->add(chaiscript::fun([](const std::string& name)-> void {setBoundary(name); }), "setBoundary");

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
			Info << "This application is aimed to create geometric surfaces from control-net vector." << endl;
			Info << endl
				<< " - the function: " << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadModel(string)" << endl
				<< " - saveTo(string)" << endl << endl

				<< " # Methods: " << endl << endl

				<< " - execute()" << endl
				<< endl
				<< " # settings: " << endl << endl

				<< " - setApexLoc(Point)" << endl
				<< " - setApexDir(Direction)" << endl
				<< " - setBoundary(string);         - boundaries: u0, un, v0 and vn" << endl
				<< " - setVerbose(unsigned int);    - Levels: 0, 1" << endl << endl

				<< " # operators: " << endl << endl

				<< " - [Point] createPoint(double, double, double)" << endl
				<< " - [direction] createDirection(double, double, double)" << endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			std::string address = ".\\system\\tnbApexSurfGenPreview";
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