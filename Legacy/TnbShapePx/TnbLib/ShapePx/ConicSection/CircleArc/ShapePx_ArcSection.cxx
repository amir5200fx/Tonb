#include <ShapePx_ArcSection.hxx>

#include <ShapePx_TopoSect_Corner.hxx>
#include <ShapePx_TopoSectSegment.hxx>
#include <Cad2d_QuadraticArc.hxx>
#include <Pln_CurveTools.hxx>
#include <Geo_Tools.hxx>
#include <Vec2d.hxx>
#include <Dir2d.hxx>
#include <NumAlg_FalsePos.hxx>
#include <NumAlg_Secant.hxx>
#include <NumAlg_BisectionSolver.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Standard_Handle.hxx>
#include <gp_Elips2d.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

#define IterType tnbLib::ShapePx_ArcSectionIterInfo_Bisection

const Standard_Real tnbLib::ShapePx_ArcSection::DEFAULT_TOLERANCE(1.0E-6);
const std::shared_ptr<tnbLib::ShapePx_ArcSectionIterInfo> 
tnbLib::ShapePx_ArcSection::DEFAULT_ITER_INFO = std::make_shared<IterType>(std::make_shared<NumAlg_BisectionSolver_Info>());

namespace tnbLib
{

	class ArcSectionIterInfo_RunTimeConfig
	{

		/*Private Data*/

	public:

		//- default constructor

		ArcSectionIterInfo_RunTimeConfig()
		{
			Init();
		}

		static void Init();
	};
}

void tnbLib::ArcSectionIterInfo_RunTimeConfig::Init()
{
	const auto& myInfo = std::dynamic_pointer_cast<IterType>(ShapePx_ArcSection::DEFAULT_ITER_INFO)->Info();
	
	myInfo->SetTolerance(1.0E-6);
	myInfo->SetDelta(1.0E-6);
	myInfo->SetMaxIterations(500);
}

static const tnbLib::ArcSectionIterInfo_RunTimeConfig myRunTimeConfig;

static const auto myBisInfo = std::make_shared<tnbLib::NumAlg_BisectionSolver_Info>();

namespace tnbLib
{

	class ArcSectionBisectionInitIterInfo_RunTimeConfig
	{

		/*Private Data*/

	public:

		//- default constructor

		ArcSectionBisectionInitIterInfo_RunTimeConfig()
		{
			Init();
		}

		static void Init();
	};
}

void tnbLib::ArcSectionBisectionInitIterInfo_RunTimeConfig::Init()
{
	myBisInfo->SetTolerance(1.0e-3);
	myBisInfo->SetDelta(1.0E-3);
	myBisInfo->SetMaxIterations(5);
}

static const tnbLib::ArcSectionBisectionInitIterInfo_RunTimeConfig myInitBisectionRunTimeConfig;

namespace tnbLib
{

	typedef std::pair<Pnt2d, Standard_Real> circleType;
	typedef std::tuple<Pnt2d, Pnt2d, Pnt2d> triangleType;

	auto RetrieveTriangle(const std::shared_ptr<ShapePx_TopoSection>& section)
	{
		const auto[pole0, pole1, pole2] = ShapePx_ConicSection::RetrieveSuperTriangle(*section);

		auto p0 = pole0->Coord();
		auto p1 = pole1->Coord();
		auto p2 = pole2->Coord();

		auto t = std::make_tuple(std::move(p0), std::move(p1), std::move(p2));
		return std::move(t);
	}

	auto RetrieveCorner(const triangleType& tri)
	{
		auto[p0, p1, p2] = tri;
		return std::move(p1);
	}

	auto RetrieveP0P2(const triangleType& tri)
	{
		auto[p0, p1, p2] = tri;
		auto t = std::make_pair(std::move(p0), std::move(p2));
		return std::move(t);
	}

	auto CalcNormalDirections(const Pnt2d& p0, const Pnt2d& corner, const Pnt2d& p2, const Standard_Real tol)
	{
		Vec2d v0(corner, p0);
		Vec2d v1(corner, p2);

		if (v0.Magnitude() < tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "null magnitude vector has been found!" << endl
				<< abort(FatalError);
		}

		if (v1.Magnitude() < tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "null magnitude vector has been found!" << endl
				<< abort(FatalError);
		}

		auto n0 = Dir2d(Vec2d(v0.Rotated(M_PI_2)));
		auto n1 = Dir2d(Vec2d(v1.Rotated(M_PI_2)));

		if (n0.IsParallel(n1, tol))
		{
			FatalErrorIn(FunctionSIG)
				<< "cannot find centre of the section!" << endl
				<< abort(FatalError);
		}

		auto t = std::make_pair(std::move(n0), std::move(n1));
		return std::move(t);
	}

	auto CalcCentre(const triangleType& tri, const Standard_Real tol)
	{
		const auto[p0, p1, p2] = tri;

		const auto[n0, n1] = CalcNormalDirections(p0, p1, p2, tol);

		auto c = Geo_Tools::IntersectionTwoLines(p0, n0, p2, n1, tol);
		return std::move(c);
	}

	auto RetrieveEllipse
	(
		const Pnt2d& centre, 
		const Pnt2d& p0,
		const Pnt2d& p1, 
		const Standard_Real tol
	)
	{
		const auto r0 = centre.Distance(p0);
		if (r0 < tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid section has been detected!" << endl
				<< " - Tolerance: " << tol << endl
				<< abort(FatalError);
		}

		const auto r1 = centre.Distance(p1);
		if (r1 < tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid section has been detected!" << endl
				<< " - Tolerance: " << tol << endl
				<< abort(FatalError);
		}

		if (r1 < r0)
		{
			gp_Ax2d majorAx(centre, Dir2d(p0, centre));
			gp_Elips2d t(majorAx, r0, r1, Standard_True);
			return std::move(t);
		}
		else
		{
			auto t = RetrieveEllipse(centre, p1, p0, tol);
			return std::move(t);
		}
	}

	auto CalcPointOnEllipse
	(
		const Handle(Geom2d_Curve)& elps,
		const Handle(Geom2d_Curve)& l, 
		const Standard_Real tol
	)
	{
		Geom2dAPI_InterCurveCurve alg;
		alg.Init(l, elps, tol);

		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid situation has been detected!" << endl
				<< " - nb. of intersection points: " << alg.NbPoints() << endl
				<< abort(FatalError);
		}
		return alg.Point(1);
	}

	/*auto isConverged(const Pnt2d& arcPoint, const circleType& c, const Standard_Real tol)
	{
		return (Standard_Boolean)(std::abs(arcPoint.Distance(c.first) - c.second) <= tol);
	}*/

	auto CalcPointOnArc
	(
		const Handle(Geom2d_Curve)& line,
		const Handle(Geom2d_Curve)& arc, 
		const Standard_Real tol
	)
	{
		Geom2dAPI_InterCurveCurve alg;
		alg.Init(line, arc, tol);
		
		if (alg.NbPoints() NOT_EQUAL 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid situation has been detected!" << endl
				<< abort(FatalError);
		}
		return alg.Point(1);
	}

	auto CreateArc(const std::vector<Pnt2d>& pnts)
	{
		TColgp_Array1OfPnt2d poles(1, pnts.size());
		TColStd_Array1OfReal weights(1, pnts.size());
		for (Standard_Integer i = 1; i <= pnts.size(); i++)
		{
			poles.SetValue(i, pnts[i - 1]);
			weights.SetValue(i, 1.0);
		}

		TColStd_Array1OfReal knots(1, 2);
		knots.SetValue(1, 0.0);
		knots.SetValue(2, 1.0);

		TColStd_Array1OfInteger mults(1, 2);
		mults.SetValue(1, 5);
		mults.SetValue(2, 5);
		
		Handle(Geom2d_BSplineCurve) curve;
		try
		{
			curve = new Geom2d_BSplineCurve(poles, weights, knots, mults, 4);
			return std::move(curve);
		}
		catch (const Standard_Failure& x)
		{
			FatalErrorIn(FunctionSIG)
				<< x.GetMessageString() << endl;
			return std::move(curve);
		}
	}

	auto RetrieveCoords(const std::shared_ptr<ShapePx_TopoSection>& section)
	{
		auto poles = ShapePx_ConicSection::RetrievePoles(*section);
		std::vector<Pnt2d> coords;
		coords.reserve(poles.size());
		for (const auto& x : poles)
		{
			Debug_Null_Pointer(x);
			coords.push_back(x->Coord());
		}
		return std::move(coords);
	}

	void setWeights5
	(
		const Standard_Real w,
		const std::vector<Standard_Real>& ws,
		const std::shared_ptr<ShapePx_TopoSection>& section
	)
	{
		auto Ws = ws;
		Ws[1] *= w;
		Ws[2] = w;
		Ws[3] *= w;

		auto poles = ShapePx_ConicSection::RetrievePoles(*section);

		Standard_Integer k = 0;
		for (const auto& x : poles)
		{
			Debug_Null_Pointer(x);
			x->SetWeight(Ws[k++]);
		}
	}

	void setWeights3
	(
		const Standard_Real w, 
		const std::shared_ptr<ShapePx_TopoSection>& section
	)
	{
		auto poles = ShapePx_ConicSection::RetrievePoles(*section);
		poles[1]->SetWeight(w);
	}
}

namespace tnbLib
{
	template<class Fun>
	class ArcSection_Function
		: public Fun
	{

		/*Private Data*/

		Pnt2d theCentre_;

		Standard_Real theRadius_;
		Standard_Real theTolerance_;

		std::vector<Standard_Real> theWs_;

		Handle(Geom2d_BSplineCurve) theCurve_;
		Handle(Geom2d_Curve) theLine_;

	public:

		//- default constructor

		ArcSection_Function()
			: theTolerance_(1.0E-6)
		{}

		ArcSection_Function
		(
			const Standard_Real theRadius,
			const Pnt2d& theCentre, 
			const std::vector<Standard_Real>& theWs, 
			const Handle(Geom2d_BSplineCurve)& theCurve,
			const Handle(Geom2d_Curve)& theLine
		)
			: theRadius_(theRadius)
			, theCentre_(theCentre)
			, theWs_(theWs)
			, theCurve_(theCurve)
			, theLine_(theLine)
			, theTolerance_(1.0E-6)
		{}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		auto Radius() const
		{
			return theRadius_;
		}

		const auto& Centre() const
		{
			return theCentre_;
		}

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& Line() const
		{
			return theLine_;
		}

		const auto& Ws() const
		{
			return theWs_;
		}

		void SetCentre(Pnt2d&& coord)
		{
			theCentre_ = std::move(coord);
		}

		void SetWs(std::vector<Standard_Real>&& theWs)
		{
			theWs_ = std::move(theWs);
		}

		void SetCurve(Handle(Geom2d_BSplineCurve) && theCurve)
		{
			theCurve_ = std::move(theCurve);
		}

		void SetLine(Handle(Geom2d_Line) && theLine)
		{
			theLine_ = std::move(theLine);
		}

		void SetTolerance(const Standard_Real tol)
		{
			theTolerance_ = tol;
		}

		void SetRadius(const Standard_Real x)
		{
			theRadius_ = x;
		}

		Standard_Real Value(const Standard_Real x) const override
		{
			Debug_Null_Pointer(Curve());

			Curve()->SetWeight(2, Ws()[1] * x);
			Curve()->SetWeight(3, x);
			Curve()->SetWeight(4, Ws()[3] * x);
			
			auto pt = CalcPointOnArc(Line(), Curve(), Tolerance());
			return pt.Distance(Centre()) - Radius();
		}
	};
}

void tnbLib::ShapePx_ArcSection::Perform()
{
	const auto& section = Section();
	if (NOT section)
	{
		FatalErrorIn(FunctionSIG)
			<< "no section has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto tri = ::tnbLib::RetrieveTriangle(section);
	const auto centre = ::tnbLib::CalcCentre(tri, Tolerance());
	const auto corner = ::tnbLib::RetrieveCorner(tri);
	const auto[p0, p2] = ::tnbLib::RetrieveP0P2(tri);

	try
	{
		//Handle(Geom2d_Ellipse) elps = new Geom2d_Ellipse(RetrieveEllipse(centre, p0, p2, Tolerance()));
		auto elps = Pln_CurveTools::MakeElipsArc(RetrieveEllipse(centre, p0, p2, Tolerance()), p0, p2);

		//Handle(Geom2d_Line) line = new Geom2d_Line(centre, Dir2d(centre, corner));
		auto line = Pln_CurveTools::MakeSegment(centre, corner);

		const auto pointOnEllipse = ::tnbLib::CalcPointOnEllipse(elps, line, Tolerance());
		const auto radius = centre.Distance(pointOnEllipse);

		ShapePx_ConicSection::Perform();

		switch (SectionType())
		{
		case sectType::quadratic:
		{
			auto alg = std::make_shared<Cad2d_QuadraticArc>();
			Debug_Null_Pointer(alg);

			alg->SetP0(p0);
			alg->SetP2(p2);

			alg->SetDir0(Dir2d(p0, corner));
			alg->SetDir2(Dir2d(p2, corner));

			alg->SetPtOnCrv(pointOnEllipse);
			alg->SetTolerance(Tolerance());

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm is not performed!");

			const auto& c = alg->Geometry();
			Debug_Null_Pointer(c);

			const auto w = c->Weight(2);

			setWeights3(w, section);
		}
		case sectType::quartic:
		{
			const auto arc = CreateArc(::tnbLib::RetrieveCoords(section));

			if (auto iterInfo = std::dynamic_pointer_cast<ShapePx_ArcSectionIterInfo_Bisection>(IterInfo()))
			{
				ArcSection_Function<NumAlg_Bisection_Function> func(radius, centre, WeightCoffs(), arc, line);
				NumAlg_BisectionSolver<ArcSection_Function<NumAlg_Bisection_Function>, true> alg(func, *iterInfo->Info());

				alg.Perform(0.01, 1.0);
				Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

				auto w = iterInfo->Info()->Result();

				setWeights5(w, WeightCoffs(), section);
			}
			else if (auto iterInfo = std::dynamic_pointer_cast<ShapePx_ArcSectionIterInfo_FalsePos>(IterInfo()))
			{
				ArcSection_Function<NumAlg_Bisection_Function> bisFunc(radius, centre, WeightCoffs(), arc, line);
				NumAlg_BisectionSolver<ArcSection_Function<NumAlg_Bisection_Function>, true> initGuess(bisFunc, *myBisInfo);
				initGuess.Perform(0.01, 1.0);
				Debug_If_Condition_Message(NOT initGuess.IsDone(), "the algorithm is not performed");

				ArcSection_Function<NumAlg_FalsePos_Function<true>> func(radius, centre, WeightCoffs(), arc, line);
				NumAlg_FalsePos<ArcSection_Function<NumAlg_FalsePos_Function<true>>, true> alg(func, *iterInfo->Info());
				alg.SetLower(0);
				alg.SetUpper(1);
				alg.Perform(myBisInfo->X0(), myBisInfo->X1());
				Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

				auto w = MEAN(iterInfo->Info()->X0(), iterInfo->Info()->X1());

				setWeights5(w, WeightCoffs(), section);
			}
			else if (auto iterInfo = std::dynamic_pointer_cast<ShapePx_ArcSectionIterInfo_Secant>(IterInfo()))
			{
				ArcSection_Function<NumAlg_Bisection_Function> bisFunc(radius, centre, WeightCoffs(), arc, line);
				NumAlg_BisectionSolver<ArcSection_Function<NumAlg_Bisection_Function>, true> initGuess(bisFunc, *myBisInfo);
				initGuess.Perform(0.01, 1.0);
				Debug_If_Condition_Message(NOT initGuess.IsDone(), "the algorithm is not performed");

				ArcSection_Function<NumAlg_Secant_Function<true>> func(radius, centre, WeightCoffs(), arc, line);
				NumAlg_Secant<ArcSection_Function<NumAlg_Secant_Function<true>>, true> alg(func, *iterInfo->Info());
				alg.SetLower(0);
				alg.SetUpper(1);
				alg.Perform(myBisInfo->X0(), myBisInfo->X1());
				Debug_If_Condition_Message(NOT alg.IsDone(), "the algorithm is not performed!");

				auto w = MEAN(iterInfo->Info()->X0(), iterInfo->Info()->X1());

				setWeights5(w, WeightCoffs(), section);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "no valid type of iter. info. has been found!" << endl
					<< abort(FatalError);
			}
			break;
		}
		default:
			FatalErrorIn(FunctionSIG)
				<< "unrecognized type of section has been detected!" << endl
				<< abort(FatalError);
			break;
		}	
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
	}
	Change_IsDone() = Standard_True;
}