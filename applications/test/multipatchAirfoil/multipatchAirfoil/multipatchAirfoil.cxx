#include <Mesh2d_Curve.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo_MetricPrcsr_Info.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_CurveTools.hxx>
#include <Cad_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Curve.hxx>
#include <Pnt3d.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Face.hxx>
#include <Geom_SurfaceOfLinearExtrusion.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom_BSplineCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>

#undef DebugInfo

#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRep_Tool.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Builder.hxx>
#include <TopExp_Explorer.hxx>

namespace tnbLib
{
	static const auto myOverallLenIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static const auto myIterIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static const auto myNewtonIterInfo = std::make_shared<NumAlg_NewtonSolver_Info>();
	static const auto myOptPointCorrInfo = std::make_shared<Mesh_CurveOptmPoint_Correction_Info>();

	class OverallLenIntegInfoRunTime
	{

	public:

		OverallLenIntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};

	class IterIntegInfoRunTime
	{

	public:

		IterIntegInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};

	class NewtonIterInfoRunTime
	{

	public:

		NewtonIterInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};

	class OptPointCorrInfoRunTime
	{

	public:

		OptPointCorrInfoRunTime()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::OverallLenIntegInfoRunTime::SetInfo()
{
	myOverallLenIntegInfo->SetMaxNbIterations(500);
	myOverallLenIntegInfo->SetNbInitIterations(6);
	myOverallLenIntegInfo->SetTolerance(1.0E-8);
}

namespace tnbLib
{

	void setMaxNbIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)
	{
		info->SetMaxNbIterations(n);
	}

	void setNbInitIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, int n)
	{
		info->SetNbInitIterations(n);
	}

	void setTolerance(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& info, double x)
	{
		info->SetTolerance(x);
	}
}

void tnbLib::IterIntegInfoRunTime::SetInfo()
{
	myIterIntegInfo->SetMaxNbIterations(50);
	myIterIntegInfo->SetNbInitIterations(3);
	myIterIntegInfo->SetTolerance(1.0E-4);
}

void tnbLib::NewtonIterInfoRunTime::SetInfo()
{
	myNewtonIterInfo->SetMaxIterations(50);
	myNewtonIterInfo->SetSmall(1.0E-6);
	myNewtonIterInfo->SetZero(1.0E-6);
	myNewtonIterInfo->SetTolerance(1.0E-6);
	myNewtonIterInfo->SetUnderRelaxation(0.9);
}

namespace tnbLib
{

	void setMaxNbIterations(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, int n)
	{
		info->SetMaxIterations(n);
	}

	void setSmall(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetSmall(x);
	}

	void setZero(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetZero(x);
	}

	void setTolerance(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetTolerance(x);
	}

	void setUnderRelaxation(const std::shared_ptr<NumAlg_NewtonSolver_Info>& info, double x)
	{
		info->SetUnderRelaxation(x);
	}
}

void tnbLib::OptPointCorrInfoRunTime::SetInfo()
{
	myOptPointCorrInfo->SetMaxLevel(10);
	myOptPointCorrInfo->SetTolerance(1.0E-6);
	myOptPointCorrInfo->SetUnderRelaxation(0.9);
}

namespace tnbLib
{

	void setMaxLevel(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, int n)
	{
		info->SetMaxLevel(n);
	}

	void setTolerance(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, double x)
	{
		info->SetTolerance(x);
	}

	void setUnderRelaxation(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& info, double x)
	{
		info->SetUnderRelaxation(x);
	}
}

static tnbLib::OverallLenIntegInfoRunTime myOverallLenIntegInfoRunTimeObj;
static tnbLib::IterIntegInfoRunTime myIterIntegInfoRunTimeObj;
static tnbLib::NewtonIterInfoRunTime myNewtonIterInfoRunTimeObj;
static tnbLib::OptPointCorrInfoRunTime myOptPointCorrInfoRunTimeObj;

namespace tnbLib
{

	static double spanLen = 1.0;
	static bool doubleSide = false;
	static double path_len = 0.025;
	static int nb_patches = 4;

	static unsigned short verbose = 0;
	static auto exeTag = false;
	static auto loadTag = false;

	static Pnt2d tip_coord;

	std::shared_ptr<std::vector<Pnt2d>> my_coords;

	static std::shared_ptr<Cad_GeomSurface> my_surface;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setSpanLen(double x)
	{
		spanLen = x;
		if (verbose)
		{
			Info << endl
				<< " - the span length is set to: " << spanLen << endl;
		}
	}

	void setTwoSided(bool cond)
	{
		doubleSide = cond;
		if (verbose)
		{
			Info << endl
				<< " - the two sided condition is set to: " << (doubleSide ? "TRUE" : "FALSE") << endl;
		}
	}

	void setTipCoord(const Pnt2d& pt)
	{
		tip_coord = pt;
		if (verbose)
		{
			Info << endl
				<< " - the tip coord is set to: " << tip_coord << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		std::ifstream file(name);
		if (file.is_open())
		{
			my_coords = std::make_shared<std::vector<Pnt2d>>();
			std::string line;
			while (std::getline(file, line))
			{
				std::istringstream iss(line);

				double x, y;
				if (iss >> x >> y)
				{
					my_coords->push_back({ x,y });
				}
				else
				{
					FatalErrorIn(FunctionSIG)
						<< "Failed to extract two numbers from the line." << endl
						<< abort(FatalError);
				}
			}
			file.close();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "Failed to open the file." << endl
				<< abort(FatalError);
		}
		loadTag = true;
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed." << endl
				<< abort(FatalError);
		}
		file::SaveTo(my_surface, name + Cad_GeomSurface::extension, verbose);
	}

	void saveTo()
	{
		saveTo("");
	}

	auto slices(const std::shared_ptr<Pln_Curve>& geom, const double len)
	{
		const auto& g = geom->Geometry();
		auto size_fun = std::make_shared<GeoSizeFun2d_Uniform>(len, geom->BoundingBox(0));
		auto metric_info = std::make_shared<Geo_MetricPrcsr_Info>(myIterIntegInfo);
		auto metric_prcsr = std::make_shared<Geo2d_MetricPrcsr>(size_fun, metric_info);
		
		auto info = std::make_shared<Mesh_Curve_Info>();
		info->OverrideCorrAlgInfo(myOptPointCorrInfo);
		info->OverrideNewtonIntgInfo(myIterIntegInfo);
		info->OverrideNewtonIterInfo(myNewtonIterInfo);
		info->OverrideOverallLengthIntgInfo(myOverallLenIntegInfo);

		const auto alg = std::make_shared<Mesh2d_Curve>();
		alg->LoadCurve(g, geom->FirstParameter(), geom->LastParameter());
		alg->LoadMap(metric_prcsr);
		alg->LoadInfo(info);
		alg->Perform();

		const auto& params = alg->Parameters();
		return params;
	}

	auto patchSurface(const Handle(Geom2d_Curve)& geom, double u0, const double len, const int n)
	{
		std::cout <<"u0 = " << u0 << std::endl;
		std::cout << "len = " << len << std::endl;
		std::cout << "lower= " << geom->FirstParameter() << ", upper: " << geom->LastParameter() << std::endl;
		auto trimmed = Pln_CurveTools::Trim(geom, u0, geom->LastParameter());
		const auto curve = std::make_shared<Pln_Curve>(trimmed);
		const auto params = slices(curve, len);
		std::vector<double> selected;
		for (size_t i = 0; i <= n; i++)
		{
			auto p = params.at(i);
			std::cout << "p = " << p << std::endl;
			selected.push_back(p);
		}
		PAUSE;
		return std::move(selected);
	}

	auto createSurface(const Handle(Geom_Curve)& curve, double u0, double u1)
	{
		auto trimmed = Cad_Tools::ConvertToTrimmed(curve, u0, u1);
		Handle(Geom_Surface) surface = new Geom_SurfaceOfLinearExtrusion(curve, gp::DZ());
		Handle(Geom_Surface) patch;
		if (doubleSide)
		{
			patch = new Geom_RectangularTrimmedSurface(surface, -0.5 * spanLen, 0.5 * spanLen, false);
		}
		else
		{
			patch = new Geom_RectangularTrimmedSurface(surface, 0, spanLen, false);
		}
		return std::move(patch);
	}

	auto getCurve3d(const Handle(Geom2d_Curve)& curve_2d, double u0, double u1)
	{
		const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(curve_2d);
		const auto& poles_2d = bspline->Poles();
		
		TColgp_Array1OfPnt pnts(1, poles_2d.Size());
		for (Standard_Integer i = 1; i <= poles_2d.Size(); i++)
		{
			const auto& p2 = poles_2d.Value(i);
			gp_Pnt p3(p2.X(), p2.Y(), 0);
			pnts.SetValue(i, p3);
		}
		Handle(Geom_BSplineCurve) curve_3d = 
			new Geom_BSplineCurve(pnts, bspline->Knots(), bspline->Multiplicities(), bspline->Degree());
		return curve_3d;
	}

	auto getUnTrimmed(const Handle(Geom2d_Curve)& curve_2d)
	{
		const auto trimmed = Handle(Geom2d_TrimmedCurve)::DownCast(curve_2d);
		return std::make_tuple(trimmed->BasisCurve(), trimmed->FirstParameter(), trimmed->LastParameter());
	}

	auto retrieveCurves(const TopoDS_Shape& theShape)
	{
		std::vector<Handle(Geom_BSplineCurve)> curves;
		for (TopExp_Explorer explorer(theShape, TopAbs_EDGE); explorer.More(); explorer.Next())
		{
			auto edge = TopoDS::Edge(explorer.Current());
			TopLoc_Location loc;
			Standard_Real first, last;
			auto curve = BRep_Tool::Curve(edge, first, last);

			auto bSplCurve = Handle(Geom_BSplineCurve)::DownCast(curve);
			if (bSplCurve.IsNull())
			{
				FatalErrorIn(FunctionSIG)
					<< "null curve has been detected!" << endl
					<< abort(FatalError);
			}
			curves.push_back(std::move(bSplCurve));
		}
		return std::move(curves);
	}

	void execute(const std::string& name)
	{
		if (NOT my_coords)
		{
			FatalErrorIn(FunctionSIG)
				<< "no offset points have been detected." << endl
				<< abort(FatalError);
		}
		const auto& curve_2d = Pln_CurveTools::Interpolation(*my_coords);
		std::vector<Pnt2d> pts;
		{
			const Geom2dAPI_ProjectPointOnCurve
				alg(tip_coord, curve_2d, curve_2d->FirstParameter(), curve_2d->LastParameter());
			const double par = alg.LowerDistanceParameter();
			auto params_1 = patchSurface(curve_2d, par, path_len, nb_patches);
			for (size_t i = 1; i < params_1.size(); i++)
			{
				pts.emplace_back(curve_2d->Value(params_1.at(i)));
			}
		}
		{
			auto reversed = curve_2d->Reversed();
			const Geom2dAPI_ProjectPointOnCurve
				alg(tip_coord, reversed, reversed->FirstParameter(), reversed->LastParameter());
			const double par = alg.LowerDistanceParameter();
			auto params_2 = patchSurface(reversed, par, path_len, nb_patches);
			for (auto p: params_2)
			{
				pts.emplace_back(reversed->Value(p));
			}
		}
		std::vector<double> pars;
		pars.emplace_back(curve_2d->FirstParameter());
		for (const auto& pt: pts)
		{
			const Geom2dAPI_ProjectPointOnCurve
				alg(pt, curve_2d, curve_2d->FirstParameter(), curve_2d->LastParameter());
			pars.emplace_back(alg.LowerDistanceParameter());
		}
		pars.emplace_back(curve_2d->LastParameter());
		std::sort(pars.begin(), pars.end());
		TopoDS_Compound compound;
		TopoDS_Builder builder;
		builder.MakeCompound(compound);
		for (size_t i = 1; i < pars.size(); i++)
		{
			auto u0 = pars.at(i - 1);
			auto u1 = pars.at(i);
			std::cout << "u0 = " << u0 << ", u1 = " << u1 << std::endl;
			auto c3 = getCurve3d(curve_2d, u0, u1);
			Handle(Geom_Surface) surface = new Geom_SurfaceOfLinearExtrusion(c3, gp::DZ());

			Handle(Geom_Surface) patch;
			TopoDS_Face face;
			if (doubleSide)
			{
				//patch = new Geom_RectangularTrimmedSurface(surface,u0, u1 , -0.5 * spanLen, 0.5 * spanLen);
				face = BRepBuilderAPI_MakeFace(surface, u0, u1, -0.5 * spanLen, 0.5 * spanLen, 1.0E-3);
			}
			else
			{
				//patch = new Geom_RectangularTrimmedSurface(surface, u0, u1, 0, spanLen);
				face = BRepBuilderAPI_MakeFace(surface, u0, u1, 0, spanLen, 1.0E-3);
			}
			/*if (i% 2 == 0)
			{
				continue;
			}*/
			builder.Add(compound, face);
		}
		if (verbose)
		{
			Info << endl
				<< " The application is performed, successfully!" << endl;
		}
		exeTag = true;
		Cad_Tools::ExportToIGES("mm", compound, "airfoil.iges");
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
		// io functions [5/14/2023 Payvand]
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

		// settings [5/14/2023 Payvand]
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");
		mod->add(chaiscript::fun([](double x)-> void {setSpanLen(x); }), "setSpanLength");
		mod->add(chaiscript::fun([](bool c)-> void {setTwoSided(c); }), "setTwoSided");

		// operators [5/14/2023 Payvand]
		mod->add(chaiscript::fun([](const std::string& name)-> void {execute(name); }), "execute");
		mod->add(chaiscript::fun([]()-> void {execute(""); }), "execute");
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
			Info << " This application is aimed to create a surface airfoil." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name)" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setSpanLenght(x)" << endl
				<< " - setTwoSided(cond);   cond : true, false" << endl
				<< " - setVerbose(unsigned int); Levels: 0, 1" << endl << endl

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
				fileName myFileName(file::GetSystemFile("multipatchAirfoil"));

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