#include <Cad_ApprxCurveOnSurface.hxx>

#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_ItemSort.hxx>
#include <Geo_Tools.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <Vec3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>

namespace tnbLib
{

	namespace cadLib
	{
		static void Check(const std::pair<Standard_Real, Standard_Real>& theSeg)
		{
			if (theSeg.first IS_EQUAL theSeg.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid segment has been detected!" << endl
					<< abort(FatalError);
			}
		}

		static auto Mean(const std::pair<Standard_Real, Standard_Real>& theSeg)
		{
			return MEAN(theSeg.first, theSeg.second);
		}

		static auto Left(const std::pair<Standard_Real, Standard_Real>& theSeg)
		{
			auto t = std::make_pair(theSeg.first, Mean(theSeg));
			return std::move(t);
		}

		static auto Right(const std::pair<Standard_Real, Standard_Real>& theSeg)
		{
			auto t = std::make_pair(Mean(theSeg), theSeg.second);
			return std::move(t);
		}

		static auto CalcSamples
		(
			const Geom2d_Curve& theCurve, 
			const Geom_Surface& theSurf, 
			const std::vector<Standard_Real>& xs
		)
		{
			std::vector<Pnt3d> samples;
			samples.reserve(xs.size());
			for (const auto x : xs)
			{
				Pnt2d pt = theCurve.Value(x);
				auto Pt = theSurf.Value(pt.X(), pt.Y());
				samples.push_back(std::move(Pt));
			}
			return std::move(samples);
		}

		static auto CalcSegPoints
		(
			const Geom2d_Curve& theCurve,
			const Geom_Surface& theSurf, 
			const std::pair<Standard_Real, Standard_Real>& theSeg
		)
		{
#ifdef _DEBUG
			Check(theSeg);
#endif // _DEBUG
			const auto[t0, t1] = theSeg;
			Pnt2d p0 = theCurve.Value(t0);
			Pnt2d p1 = theCurve.Value(t1);
			auto P0 = theSurf.Value(p0.X(), p0.Y());
			auto P1 = theSurf.Value(p1.X(), p1.Y());
			auto t = std::make_pair(std::move(P0), std::move(P1));
			return std::move(t);
		}

		static auto CalcApproximate(const std::pair<Pnt3d, Pnt3d>& theSeg, const std::vector<Pnt3d>& theSamples)
		{
			const auto&[p0, p1] = theSeg;
			Standard_Real maxDis = 0;
			for (const auto& x : theSamples)
			{
				auto dis = Geo_Tools::SquareDistance_cgal(x, p0, p1);
				if (dis > maxDis)
					maxDis = dis;
			}
			return maxDis;
		}

		static auto CalcUniformDistb(const Standard_Integer nbPts, const Standard_Real x0, const Standard_Real x1)
		{
			Debug_If_Condition(nbPts <= 0);
			std::vector<Standard_Real> xs(nbPts);
			const auto dx = (x0 - x1) / (Standard_Real)nbPts;
			Standard_Integer i = 0;
			for (auto& x : xs)
			{
				x = (x0 + 0.5*dx) + i * dx;
				Debug_If_Condition(x >= x1);
				i++;
			}
			return std::move(xs);
		}

		auto CalcAngle(const std::pair<Pnt3d, Pnt3d>& theSeg, const Pnt3d& pt)
		{
			const auto&[p0, p1] = theSeg;
			Vec3d vt(p0, p1);
			Standard_Real a0 = 0;
			Standard_Real a1 = 0;
			try
			{
				Vec3d v0(p0, pt);
				a0 = vt.Angle(v0);
			}
			catch (const Standard_Failure&)
			{
				a0 = 0;
			}

			try
			{
				Vec3d v0(pt, p1);
				a1 = vt.Angle(v0);
			}
			catch (const Standard_Failure&)
			{
				a1 = 0;
			}
			return std::max(a0, a1);
		}

		static auto CalcMaxAngle(const std::pair<Pnt3d, Pnt3d>& theSeg, const std::vector<Pnt3d>& theSamples)
		{
			Debug_If_Condition(theSamples.size() < 2);
			const auto&[p0, p1] = theSeg;
			Pnt3d pt;
			Standard_Real maxD = 0;
			for (const auto& x : theSamples)
			{
				auto d0 = p0.Distance(x);
				auto d1 = p1.Distance(x);
				if (d0 + d1 > maxD)
				{
					maxD = d0 + d1;
					pt = x;
				}
			}
			return CalcAngle(theSeg, pt);
		}

		static void Subdivide
		(
			const Geom2d_Curve& theCurve,
			const Geom_Surface& theSurface,
			const std::pair<Standard_Real, Standard_Real>& theSegment,
			const Standard_Integer theNbSamples, 
			const Standard_Real theApprox, 
			const Standard_Real theAngle, 
			const Standard_Real theMinSizeSq, 
			const Standard_Integer theLev, 
			const Standard_Integer theInitLev, 
			const Standard_Integer theMaxLev,
			std::vector<std::pair<Standard_Real, Standard_Real>>& theSegments
		)
		{
			if (theLev < theInitLev)
			{
				Subdivide
				(
					theCurve, theSurface,
					Left(theSegment), theNbSamples, 
					theApprox, theAngle, theMinSizeSq,
					theLev + 1, theInitLev,
					theMaxLev, theSegments
				);

				Subdivide
				(
					theCurve, theSurface,
					Right(theSegment), theNbSamples,
					theApprox, theAngle, theMinSizeSq,
					theLev + 1, theInitLev,
					theMaxLev, theSegments
				);
				return;
			}

			if (theLev >= theMaxLev)
			{
				theSegments.push_back(theSegment);
				return;
			}

			auto segPnts = CalcSegPoints(theCurve, theSurface, theSegment);
			const auto&[P0, P1] = segPnts;
			const auto sqDist = P0.SquareDistance(P1);

			if (sqDist <= theMinSizeSq)
				return;

			const auto[x0, x1] = theSegment;
			auto samples = CalcSamples(theCurve, theSurface, CalcUniformDistb(theNbSamples, x0, x1));

			const auto approx = CalcApproximate(segPnts, samples);
			if (theApprox*sqDist < approx)
			{
				Subdivide
				(
					theCurve, theSurface,
					Left(theSegment), theNbSamples,
					theApprox, theAngle, theMinSizeSq,
					theLev + 1, theInitLev,
					theMaxLev, theSegments
				);

				Subdivide
				(
					theCurve, theSurface,
					Right(theSegment), theNbSamples,
					theApprox, theAngle, theMinSizeSq,
					theLev + 1, theInitLev,
					theMaxLev, theSegments
				);
				return;
			}

			const auto angle = CalcMaxAngle(segPnts, samples);
			if (theAngle < angle)
			{
				Subdivide
				(
					theCurve, theSurface,
					Left(theSegment), theNbSamples,
					theApprox, theAngle, theMinSizeSq,
					theLev + 1, theInitLev,
					theMaxLev, theSegments
				);

				Subdivide
				(
					theCurve, theSurface,
					Right(theSegment), theNbSamples,
					theApprox, theAngle, theMinSizeSq,
					theLev + 1, theInitLev,
					theMaxLev, theSegments
				);
				return;
			}
			theSegments.push_back(theSegment);
		}
	}
}

void tnbLib::Cad_ApprxCurveOnSurface::Perform()
{
	if (NOT ParaCurve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no parametric curve has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Surface())
	{
		FatalErrorIn(FunctionSIG)
			<< "no surface has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT ApproxInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info. has been loaded!" << endl
			<< abort(FatalError);
	}

	const auto nbSamples = ApproxInfo()->NbSamples();
	const auto approx = ApproxInfo()->Approx();
	const auto angle = ApproxInfo()->Angle();
	const auto minSize = ApproxInfo()->MinSize();
	const auto initNbSub = ApproxInfo()->InitNbSubdivision();
	const auto maxSub = ApproxInfo()->MaxNbSubdivision();

	std::vector<std::pair<Standard_Real, Standard_Real>> segments;
	auto seg = std::make_pair(FirstParameter(), LastParameter());

	cadLib::Subdivide
	(
		*ParaCurve(), *Surface(),
		seg, nbSamples,
		approx*approx,
		Geo_Tools::DegToRadian(angle), 
		minSize*minSize,
		0, initNbSub, maxSub, segments
	);

	Geo_ItemSort<std::pair<Standard_Real, Standard_Real>> 
		sorting((
			[]
	(
		const std::pair<Standard_Real, Standard_Real>& l, 
		const std::pair<Standard_Real, Standard_Real>& r
		)-> Standard_Boolean {return cadLib::Mean(l) < cadLib::Mean(r); }
	));

	sorting.Perform(segments);

	std::vector<Pnt2d> pts;
	pts.reserve(segments.size() + 2);

	const auto& curve = *ParaCurve();
	pts.push_back(curve.Value(FirstParameter()));
	for (const auto& seg : segments)
	{
		auto x = cadLib::Mean(seg);
		pts.push_back(curve.Value(x));
	}
	pts.push_back(curve.Value(LastParameter()));

	auto poly = std::make_shared<Entity2d_Polygon>();
	poly->Points() = std::move(pts);

	ApproxRef() = std::move(poly);
	Change_IsDone() = Standard_True;
}

void tnbLib::Cad_ApprxCurveOnSurface::SetParaCurve
(
	const Handle(Geom2d_Curve)& thePara, 
	const Standard_Real theFirst,
	const Standard_Real theLast
)
{
	thePara_ = thePara;
	theFirstParameter_ = theFirst;
	theLastParameter_ = theLast;
}