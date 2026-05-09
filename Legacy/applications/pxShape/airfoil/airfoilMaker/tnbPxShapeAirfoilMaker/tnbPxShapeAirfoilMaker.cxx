#include <Geo_Tools.hxx>
#include <Geo_CosineDistb.hxx>
#include <GeoSizeFun_Uniform.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <Geo_MetricPrcsr_Info.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Curve.hxx>
#include <Pln_CurveTools.hxx>
#include <Pln_Tools.hxx>
#include <Mesh2d_CurveEntity.hxx>
#include <Mesh_CurveLength.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction.hxx>
#include <Mesh_CurveOptmPoint_Newton.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <Global_File.hxx>

#include <fstream>
#include <vector>

#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2d_Line.hxx>

namespace fs = boost::filesystem;

namespace tnbLib
{

	typedef std::shared_ptr<Pln_Curve> curve_t;
	typedef std::shared_ptr<NumAlg_AdaptiveInteg_Info> info_t;
	typedef NumAlg_AdaptiveInteg_Info intgInfo;
	typedef Mesh2d_CurveEntity curveEntity;

	typedef Mesh_Curve_Info meshInfo;
	typedef std::shared_ptr<meshInfo> meshInfo_t;

	static std::vector<curve_t> myCurves;
	static bool verbose = false;
	static bool loaded = false;
	static bool exeTag = false;

	static const unsigned int DEFAULT_NB_DIVISIONS_LOW = 15;
	static const unsigned int DEFAULT_NB_DIVISIONS_MEDIUM = 25;
	static const unsigned int DEFAULT_NB_DIVISIONS_HIGH = 60;

	static auto nbPnts = DEFAULT_NB_DIVISIONS_LOW;

	static std::vector<curve_t> myCamberProfiles;
	static std::vector<curve_t> myThickProfiles;

	static std::vector<double> mySpanCamberProfile;
	static std::vector<double> mySpanThickProfile;

	//static curve_t camberCurve;
	//static curve_t thckProfile;
	//static curve_t lowerThck;

	static curve_t myUpperCurve;
	static curve_t myLowerCurve;

	static info_t myNumInfo;

	static double x0 = 0;
	static double x1 = 0;

	static int maxLevCurveLen = 20;

	std::vector<double> retrieveSpans(const std::vector<curve_t>& curves)
	{
		auto iter = curves.begin();
		auto x0 = (*iter)->FirstCoord().X();
		auto x1 = (*iter)->LastCoord().X();

		std::vector<double> spans;
		spans.reserve(curves.size() + 1);
		spans.push_back(x0);
		spans.push_back(x1);

		iter++;
		while (iter NOT_EQUAL curves.end())
		{
			auto xi = (*iter)->LastCoord().X();
			spans.push_back(xi);

			iter++;
		}
		return std::move(spans);
	}

	void checkProfile(const std::vector<curve_t>& curves)
	{
		auto iter = curves.begin();
		auto p0 = (*iter)->LastCoord();
		iter++;
		while (iter NOT_EQUAL curves.end())
		{
			auto p1 = (*iter)->FirstCoord();
			if (p0.Distance(p1) > gp::Resolution())
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid profile has been detected!" << endl
					<< abort(FatalError);
			}
			p0 = (*iter)->LastCoord();
			iter++;
		}
	}

	void checkLoad()
	{
		if (NOT loaded)
		{
			FatalErrorIn(FunctionSIG)
				<< "the curves are not loaded!" << endl
				<< abort(FatalError);
		}
	}

	void setTessellation(const word& t)
	{
		if (t IS_EQUAL "low")
		{
			nbPnts = DEFAULT_NB_DIVISIONS_LOW;
		}
		else if (t IS_EQUAL "medium")
		{
			nbPnts = DEFAULT_NB_DIVISIONS_MEDIUM;
		}
		else if (t IS_EQUAL "high")
		{
			nbPnts = DEFAULT_NB_DIVISIONS_HIGH;
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "undefined tessellation type" << endl
				<< abort(FatalError);
		}
	}

	void loadCurves(const std::string& name)
	{
		if (verbose)
		{
			Info << endl;
			Info << " loading the curves..." << endl;
			Info << endl;
		}

		{
			if (boost::filesystem::is_directory(boost::filesystem::path("camber")))
			{
				std::string address = ".\\camber\\" + name;
				std::fstream file;
				file.open(address, std::ios::in);

				if (file.fail())
				{
					FatalErrorIn(FunctionSIG)
						<< "file is not found" << endl
						<< abort(FatalError);
				}

				boost::archive::polymorphic_text_iarchive ia(file);

				ia >> myCamberProfiles;
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to find directory: camber" << endl
					<< abort(FatalError);
			}
		}

		{
			if (boost::filesystem::is_directory(boost::filesystem::path("thickness")))
			{
				std::string address = ".\\thickness\\" + name;
				std::fstream file;
				file.open(address, std::ios::in);

				if (file.fail())
				{
					FatalErrorIn(FunctionSIG)
						<< "file is not found" << endl
						<< abort(FatalError);
				}

				boost::archive::polymorphic_text_iarchive ia(file);

				ia >> myThickProfiles;
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to find directory: thickness" << endl
					<< abort(FatalError);
			}
		}

		mySpanCamberProfile = retrieveSpans(myCamberProfiles);
		mySpanThickProfile = retrieveSpans(myThickProfiles);

		if (verbose)
		{
			Info << endl;
			Info << " the curves are loaded, successfully" << endl;
			Info << endl;
		}
		loaded = true;
	}

	/*void calcBoundaries()
	{
		auto p0 = camberCurve->FirstCoord();
		x0 = p0.X();

		auto p1 = camberCurve->LastCoord();
		x1 = p1.X();
	}*/

	std::pair<double, double> xValue(double x, const Handle(Geom2d_Curve)& geometry)
	{
		//const auto& geometry = c->Geometry();

		gp_Pnt2d pt(x, 0);
		gp_Vec2d dir(0, 1);
		Handle(Geom2d_Curve) line = new Geom2d_Line(pt, dir);

		Geom2dAPI_InterCurveCurve alg(geometry, line);

		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid data to construct an airfoil" << endl
				<< abort(FatalError);
		}
		auto t = std::make_pair(alg.Point(1).Y(), alg.Intersector().Point(1).ParamOnFirst());
		return std::move(t);
	}

	std::pair<double, double> xValue(double x, const std::vector<curve_t>& curves, const std::vector<double>& spans)
	{
		auto s = Geo_Tools::FindSpan(x, spans);
		const auto& c = curves[s];
		auto t = xValue(x, c->Geometry());
		return std::move(t);
	}

	const auto& retrieveCurve(double x, const std::vector<curve_t>& curves, const std::vector<double>& spans)
	{
		auto s = Geo_Tools::FindSpan(x, spans);
		return curves[std::min(s, curves.size() - 1)];
	}

	std::tuple<std::vector<double>, std::vector<double>, std::vector<gp_Dir2d>>
		calcPts
		(
			const std::shared_ptr<Geo_xDistb>& dist
		)
	{
		std::vector<double> xs, ys;
		std::vector<gp_Dir2d> ts;
		xs.reserve(dist->Size());
		ys.reserve(dist->Size());
		ts.reserve(dist->Size());

		//const auto& geometry = camberCurve->Geometry();

		gp_Pnt2d pt;
		gp_Vec2d vt;

		for (auto t : dist->Values())
		{
			const auto& geometry = retrieveCurve(t, myCamberProfiles, mySpanCamberProfile)->Geometry();
			try
			{
				auto p = xValue(t, geometry).second;
				geometry->D1(p, pt, vt);
			}
			catch (const Standard_Failure&)
			{
				FatalErrorIn(FunctionSIG)
					<< "the continuity of the curve is not C1" << endl
					<< abort(FatalError);
			}
			xs.push_back(pt.X());
			ys.push_back(pt.Y());

			try
			{
				gp_Dir2d dir(vt);
				ts.push_back(std::move(dir));
			}
			catch (const Standard_Failure&)
			{
				FatalErrorIn(FunctionSIG)
					<< "the continuity of the curve is not C1" << endl
					<< abort(FatalError);
			}
		}
		auto paired = std::make_tuple(std::move(xs), std::move(ys), std::move(ts));
		return std::move(paired);
	}

	std::vector<double> calcThick(const std::vector<double>& xs)
	{
		std::vector<double> yt;
		yt.reserve(xs.size());

		for (auto x : xs)
		{
			const auto& c = retrieveCurve(x, myThickProfiles, mySpanThickProfile);
			auto y = 0.5 * xValue(x, c->Geometry()).first;
			yt.push_back(y);
		}
		return std::move(yt);
	}

	std::vector<Pnt2d> calcUpperPoints
	(
		const std::vector<double>& xc,
		const std::vector<double>& yc,
		const std::vector<double>& uYt,
		const std::vector<gp_Dir2d>& tc
	)
	{
		std::vector<Pnt2d> pts;
		pts.reserve(xc.size());

		for (size_t i = 0; i < xc.size(); i++)
		{
			auto yt = uYt[i];
			auto cost = tc[i].X();
			auto sint = tc[i].Y();

			auto xu = xc[i] - yt * sint;
			auto yu = yc[i] + yt * cost;

			Pnt2d pt(xu, yu);
			pts.push_back(std::move(pt));
		}
		return std::move(pts);
	}

	std::vector<Pnt2d> calcLowerPoints
	(
		const std::vector<double>& xc,
		const std::vector<double>& yc,
		const std::vector<double>& lYt,
		const std::vector<gp_Dir2d>& tc
	)
	{
		std::vector<Pnt2d> pts;
		pts.reserve(xc.size());

		for (size_t i = 0; i < xc.size(); i++)
		{
			auto yt = lYt[i];
			auto cost = tc[i].X();
			auto sint = tc[i].Y();

			auto xl = xc[i] + yt * sint;
			auto yl = yc[i] - yt * cost;

			Pnt2d pt(xl, yl);
			pts.push_back(std::move(pt));
		}
		return std::move(pts);
	}

	double calcLength(const curveEntity& curve, int lev, int maxLev, intgInfo& info)
	{
		try
		{
			return Mesh_CurveLength::Length(curve, info);
		}
		catch (const ConvError&)
		{
			if (lev > maxLev)
			{
				FatalErrorIn(FunctionSIG)
					<< "Can not Calculate length of the curve" << endl
					<< " - Level of the calculation: " << lev << endl
					<< " - Max. nb of the levels: " << maxLev << endl
					<< abort(FatalError);
			}

			return calcLength
			(
				curveEntity
				(
					curve.Curve(),
					curve.SizeMap(),
					curve.FirstParameter(),
					MEAN(curve.FirstParameter(), curve.LastParameter())),
				lev + 1, maxLev, info)
				+ calcLength
				(
					curveEntity
					(
						curve.Curve(),
						curve.SizeMap(),
						MEAN(curve.FirstParameter(), curve.LastParameter()),
						curve.LastParameter()),
					lev + 1, maxLev, info);
		}
	}

	double calcLength(const curveEntity& curve, int maxLev, intgInfo& info)
	{
		return calcLength(curve, 0, maxLev, info);
	}

	double calcNextParameter
	(
		double u0,
		double guess,
		double step,
		double umax,
		double lev,
		double maxLev,
		curveEntity& curve,
		meshInfo& info
	)
	{
		Mesh_CurveOptmPoint_Correction<Geom2d_Curve, Geo2d_MetricPrcsr>
			correction(u0, guess, curve, *info.CorrAlgInfo(), info.NewtonIntgInfo());
		correction.Perform();

		Debug_If_Condition_Message(NOT correction.IsDone(),
			"mesh_curveoptpoint_correction algorithm has not been performed!");
		auto corrected = correction.Corrected();

		Mesh_CurveOptmPoint_Newton<Geom2d_Curve, Geo2d_MetricPrcsr>
			alg(u0, step, curve);

		try
		{
			alg.Perform(corrected, info.NewtonIterInfo(),
				info.NewtonIntgInfo());
			Debug_If_Condition_Message(NOT alg.IsDone(),
				"mesh_curveoptpoint_newton algorithm has not been performed!");
			return alg.Corrected();
		}
		catch (const ConvError&)
		{
			if (lev > maxLev)
			{
				if (info.IgnoreNonConvergency())
				{
					return alg.Corrected();
				}

				FatalErrorIn(FunctionSIG)
					<< "Can not Calculate parameter of the curve" << endl
					<< abort(FatalError);
			}

			const auto ds2 = step / 2;
			const auto du = u0 + (corrected - u0) / 2;

			auto u0n =
				calcNextParameter
				(
					u0,
					du, ds2, umax,
					lev + 1, maxLev,
					curve, info);
			return
				calcNextParameter
				(
					u0n, u0n + du, ds2,
					umax, lev + 1,
					maxLev, curve, info
				);
		}
	}

	double calcNextParameter
	(
		double u0,
		double guess,
		double step,
		double umax,
		curveEntity& curve,
		meshInfo& info
	)
	{
		return calcNextParameter
		(
			u0, guess, step,
			umax, 0, info.LengthCalcMaxLevel(),
			curve, info
		);
	}

	double calcOffsetCurveParameter(const curve_t& camber, double len, double s, meshInfo& info)
	{
		auto b = camber->BoundingBox(1.0E-6);
		auto sizeFunc = std::make_shared<GeoSizeFun_Uniform<Pnt2d>>(1.0, b);

		auto metricInfo = std::make_shared<Geo_MetricPrcsr_Info>(myNumInfo);
		auto metricProcsr = std::make_shared<Geo2d_MetricPrcsr>(sizeFunc, metricInfo);

		auto integrand =
			std::make_shared<Mesh2d_CurveEntity>
			(
				*camber->Geometry(),
				*metricProcsr,
				camber->FirstParameter(),
				camber->LastParameter()
				);

		//auto curveLen = calcLength(*integrand, maxLevCurveLen, *myNumInfo);
		auto curveLen = len / s;

		auto NbSegments =
			MAX
			(
				Geo_Tools::Round(curveLen * (1.0 + EPS6)),
				Geo_Tools::Round(curveLen * (1.0 - EPS6)));
		if (NbSegments < 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "unexpected error has been occurred in offset curve calculation" << endl
				<< abort(FatalError);
		}

		const auto Ds = curveLen / (double)NbSegments;
		const auto dt = 1.0 / curveLen;

		auto u0 = camber->FirstParameter();
		auto guess = u0 + dt;

		if (guess < camber->FirstParameter()) guess = camber->FirstParameter();
		if (guess > camber->LastParameter()) guess = camber->LastParameter();

		auto u1 = calcNextParameter(u0, guess, Ds, camber->LastParameter(), *integrand, info);

		if (NOT INSIDE(u1, u0, camber->LastParameter()))
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid Parameter, unable to find the next parameter: " << u1 << endl
				<< " - First parameter: " << camber->FirstParameter() << endl
				<< " - Last parameter: " << camber->LastParameter() << endl
				<< abort(FatalError);
		}
		return u1;
	}

	/*std::pair<curve_t, curve_t>
		leadingEdgeCurves
		(
			const curve_t& camber,
			const curve_t& upper,
			const curve_t& lower,
			double offsetPerc,
			meshInfo& info
		)
	{
		const auto& geometry = camber->Geometry();

		gp_Pnt2d pt;
		gp_Vec2d vt;
		geometry->D1(camber->FirstParameter(), pt, vt);

		vt = vt.GetNormal();

		auto b = camber->BoundingBox(1.0E-6);
		auto sizeFunc = std::make_shared<GeoSizeFun_Uniform<Pnt2d>>(1.0, b);

		auto metricProcsr = std::make_shared<Geo2d_MetricPrcsr>(sizeFunc, myNumInfo);

		auto integrand =
			std::make_shared<Mesh2d_CurveEntity>
			(
				*camber->Geometry(),
				*metricProcsr,
				camber->FirstParameter(),
				camber->LastParameter()
				);

		auto curveLen = calcLength(*integrand, maxLevCurveLen, *myNumInfo);

		const auto u0 = camber->FirstParameter();
		const auto u1 = calcOffsetCurveParameter(camber, curveLen, offsetPerc*curveLen, info);

		const auto c = camber->Value(u1);


	}*/

	void execute()
	{
		if (myCamberProfiles.empty())
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "no camber profile has been detected!" << endl
				<< abort(FatalError);
		}
		checkLoad();

		const auto p0 = myCamberProfiles[0]->FirstCoord().X();
		const auto p1 = myCamberProfiles[myCamberProfiles.size() - 1]->LastCoord().X();

		const auto dist = std::make_shared<Geo_CosineDistb>(nbPnts);
		dist->SetLower(p0);
		dist->SetUpper(p1);
		dist->Perform();

		const auto [xc, yc, tc] = calcPts(dist);

		const auto uYt = calcThick(xc);
		const auto lYt = calcThick(xc);

		const auto uPts = calcUpperPoints(xc, yc, uYt, tc);
		const auto lPts = calcLowerPoints(xc, yc, lYt, tc);

		/*const auto& uQ0 = uPts[0];
		const auto& lQ0 = lPts[0];

		const auto& uQ1 = uPts[uPts.size() - 1];
		const auto& lQ1 = lPts[lPts.size() - 1];*/

		auto c0 = Pln_CurveTools::Interpolation(uPts);
		auto c1 = Pln_CurveTools::Interpolation(lPts);

		myLowerCurve = std::make_shared<Pln_Curve>(0, "upper profile", std::move(c0));
		myUpperCurve = std::make_shared<Pln_Curve>(1, "lower profile", std::move(c1));

		exeTag = true;
	}

	void saveTo(const std::string& name)
	{
		std::vector<curve_t> curves;
		curves.push_back(myUpperCurve);
		curves.push_back(myLowerCurve);

		auto myEdges = Pln_Tools::RetrieveEdges(curves);

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
		for (const auto& x : myEdges)
		{
			std::string icurrent = address + "\\" + std::to_string(i);

			fs::path idir(std::to_string(i));
			fs::create_directory(idir);

			fs::current_path(icurrent);

			file::SaveTo(x, name + Pln_Edge::extension, verbose);

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
		saveTo("");
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadCurves(name); }), "loadFiles");
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");

		mod->add(chaiscript::fun([](const std::string& l)->void {setTessellation(l); }), "setTessellation");
		mod->add(chaiscript::fun([](unsigned short v)->void {verbose = v; }), "setVerbose");

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
			Info << "this is help" << endl;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setGlobals(mod);

			chai.add(mod);

			auto address = file::GetSystemFile("tnbPxShapeAirfoilMaker");
			fileName myFileName(address);

			try
			{
				chai.eval_file(myFileName);
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
	return 0;
}