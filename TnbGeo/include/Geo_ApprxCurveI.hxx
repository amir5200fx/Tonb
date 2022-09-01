#pragma once
#include <NumAlg_Random.hxx>
#include <Geo_Tools.hxx>
#include <Geo_ItemSort.hxx>
#include <Geo_ApprxCurve_Traits.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Standard_Failure.hxx>
namespace tnbLib
{

	namespace geoLib
	{

		typedef Geo_ApprxCurveBase::Segment Segment;
		typedef typename Geo_ApprxCurveBase::segList segList;

		inline auto CalcRandomX
		(
			const Standard_Integer nbPnts, 
			const Standard_Real x0,
			const Standard_Real x1
		)
		{
			Debug_If_Condition(nbPnts <= 0);
			std::vector<Standard_Real> xs(nbPnts);
			for (auto& x : xs)
			{
				x = NumAlg_Random::Randreal(x0, x1);
			}
			return std::move(xs);
		}

		inline auto UniformDistb
		(
			const Standard_Integer nbPnts, 
			const Standard_Real x0, 
			const Standard_Real x1
		)
		{
			Debug_If_Condition(nbPnts <= 0);
			std::vector<Standard_Real> xs(nbPnts);
			const auto dx = (x0 - x1) / nbPnts;
			Standard_Integer i = 0;
			for (auto& x : xs)
			{
				x = (x0 + 0.5*dx) + i * dx;
				Debug_If_Condition(x >= x1);
				i++;
			}
			return std::move(xs);
		}

		template<class CurveType, bool RandSamples = true>
		struct CalcXs
		{
			static auto _
			(
				const Standard_Integer nbPnts,
				const Standard_Real x0,
				const Standard_Real x1
			)
			{
				auto xs = CalcRandomX(nbPnts, x0, x1);
				return std::move(xs);
			}
		};

		template<class CurveType>
		struct CalcXs<CurveType, false>
		{
			static auto _
			(
				const Standard_Integer nbPnts,
				const Standard_Real x0,
				const Standard_Real x1
			)
			{
				auto xs = UniformDistb(nbPnts, x0, x1);
				return std::move(xs);
			}
		};

		template<class CurveType>
		auto CalcSamples
		(
			const CurveType& theCurve,
			const std::vector<Standard_Real>& xs		
		)
		{
			std::vector<typename Geo_ApprxCurve_Traits<CurveType>::ptType> samples;
			samples.reserve(xs.size());
			for (const auto x : xs)
			{
				auto p = theCurve.Value(x);
				samples.push_back(std::move(p));
			}
			return std::move(samples);
		}

		template<class CurveType>
		auto CalcSegPoints
		(
			const CurveType& theCurve,
			const Segment& theSeg
		)
		{
			Debug_If_Condition(theSeg.theX0 IS_EQUAL theSeg.theX1);
			const auto P0 = theCurve.Value(theSeg.theX0);
			const auto P1 = theCurve.Value(theSeg.theX1);

			auto t = std::make_pair(std::move(P0), std::move(P1));
			return std::move(t);
		}

		template<class CurveType>
		Standard_Real CalcSqDist
		(
			const std::pair<typename Geo_ApprxCurve_Traits<CurveType>::ptType, typename Geo_ApprxCurve_Traits<CurveType>::ptType>& theSeg
		)
		{
			const auto& p0 = theSeg.first;
			const auto& p1 = theSeg.second;
			return p0.SquareDistance(p1);
		}

		template<class CurveType>
		Standard_Real CalcApproximate
		(
			const std::pair<typename Geo_ApprxCurve_Traits<CurveType>::ptType, typename Geo_ApprxCurve_Traits<CurveType>::ptType>& theSeg,
			const std::vector<typename Geo_ApprxCurve_Traits<CurveType>::ptType>& theSamples
		)
		{
			const auto& p0 = theSeg.first;
			const auto& p1 = theSeg.second;

			Standard_Real maxDis = 0;
			for (const auto& x : theSamples)
			{
				auto dis = Geo_Tools::SquareDistance_cgal(x, p0, p1);
				if (dis > maxDis)
					maxDis = dis;
			}
			return maxDis;

		}

		template<class CurveType>
		auto CalcAngle
		(
			const std::pair<typename Geo_ApprxCurve_Traits<CurveType>::ptType, typename Geo_ApprxCurve_Traits<CurveType>::ptType>& theSeg,
			const typename Geo_ApprxCurve_Traits<CurveType>::ptType& p
		)
		{
			const auto& p0 = theSeg.first;
			const auto& p1 = theSeg.second;

			typename Geo_ApprxCurve_Traits<CurveType>::vtType vt(p0, p1);
			Standard_Real a0 = 0;
			Standard_Real a1 = 0;
			try
			{
				typename Geo_ApprxCurve_Traits<CurveType>::vtType v0(p0, p);
				a0 = vt.Angle(v0);
			}
			catch (const Standard_Failure&)
			{
				a0 = 0;
			}

			try
			{
				typename Geo_ApprxCurve_Traits<CurveType>::vtType v0(p, p1);
				a1 = vt.Angle(v0);
			}
			catch (const Standard_Failure&)
			{
				a1 = 0;
			}

			return std::max(a0, a1);
		}

		template<class CurveType>
		Standard_Real CalcMaxAngle
		(
			const std::pair<typename Geo_ApprxCurve_Traits<CurveType>::ptType, typename Geo_ApprxCurve_Traits<CurveType>::ptType>& theSeg,
			const std::vector<typename Geo_ApprxCurve_Traits<CurveType>::ptType>& theSamples
		)
		{
			const auto& p0 = theSeg.first;
			const auto& p1 = theSeg.second;

			typename Geo_ApprxCurve_Traits<CurveType>::vtType vt(p0, p1);
			typename Geo_ApprxCurve_Traits<CurveType>::ptType pt;

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
			return CalcAngle<CurveType>(theSeg, pt);
		}

		template<class CurveType, bool RandSamples>
		void Subdivide
		(
			const CurveType& theCurve,
			const Segment& theSeg,
			const Standard_Integer theNbSamples,
			const Standard_Real theApprox,
			const Standard_Real theAngle,
			const Standard_Real theMinSizeSQ,
			const Standard_Integer theLevel,
			const Standard_Integer theInitlevel,
			const Standard_Integer theMaxlevel,
			segList& theSegments
		)
		{
			if (theLevel < theInitlevel)
			{
				Subdivide<CurveType, RandSamples>
					(
						theCurve, theSeg.Left(),
						theNbSamples,
						theApprox,
						theAngle,
						theMinSizeSQ,
						theLevel + 1, theInitlevel, theMaxlevel, theSegments);
				Subdivide<CurveType, RandSamples>
					(
						theCurve, theSeg.Right(),
						theNbSamples,
						theApprox,
						theAngle,
						theMinSizeSQ,
						theLevel + 1, theInitlevel, theMaxlevel, theSegments);
				return;
			}

			if (theLevel >= theMaxlevel)
			{
				theSegments.push_back(theSeg);
				return;
			}

			auto segPnts = geoLib::CalcSegPoints(theCurve, theSeg);
			auto sqDis = geoLib::CalcSqDist<CurveType>(segPnts);

			if (sqDis <= theMinSizeSQ)
				return;

			auto samples =
				geoLib::CalcSamples
				(
					theCurve,
					geoLib::CalcXs<CurveType, RandSamples>::_(theNbSamples, theSeg.theX0, theSeg.theX1)
				);

			auto approx = geoLib::CalcApproximate<CurveType>(segPnts, samples);

			if (theApprox*sqDis < approx)
			{
				Subdivide<CurveType, RandSamples>
					(
						theCurve,
						theSeg.Left(),
						theNbSamples,
						theApprox,
						theAngle,
						theMinSizeSQ,
						theLevel + 1, theInitlevel, theMaxlevel, theSegments);
				Subdivide<CurveType, RandSamples>
					(
						theCurve,
						theSeg.Right(),
						theNbSamples,
						theApprox,
						theAngle,
						theMinSizeSQ,
						theLevel + 1, theInitlevel, theMaxlevel, theSegments);
				return;
			}

			auto angle = geoLib::CalcMaxAngle<CurveType>(segPnts, samples);
			if (theAngle < angle)
			{
				Subdivide<CurveType, RandSamples>
					(
						theCurve,
						theSeg.Left(),
						theNbSamples,
						theApprox,
						theAngle,
						theMinSizeSQ,
						theLevel + 1, theInitlevel, theMaxlevel, theSegments);
				Subdivide<CurveType, RandSamples>
					(
						theCurve,
						theSeg.Right(),
						theNbSamples,
						theApprox,
						theAngle,
						theMinSizeSQ,
						theLevel + 1, theInitlevel, theMaxlevel, theSegments);
				return;
			}

			theSegments.push_back(theSeg);
		}
	}

	template<class CurveType, bool RandSamples>
	inline void Geo_ApprxCurve<CurveType, RandSamples>::Subdivide
	(
		segList & theSegments
	) const
	{
		Debug_Null_Pointer(Info());
		const auto& theInfo = *Info();

		geoLib::Subdivide<typename remove_pointer<CurveType>::type, RandSamples>
			(
				*Curve(),
				Segment(FirstParameter(), LastParameter()),
				theInfo.NbSamples(),
				theInfo.Approx()*theInfo.Approx(),
				Geo_Tools::DegToRadian(theInfo.Angle()),
				theInfo.MinSize()* theInfo.MinSize(),
				0, theInfo.InitNbSubdivision(), theInfo.MaxNbSubdivision(), theSegments
				);
	}

	template<class CurveType, bool RandSamples>
	void Geo_ApprxCurve<CurveType, RandSamples>::Perform()
	{
		if (NOT IsLoaded())
		{
			FatalErrorIn("void Perform()") << endl
				<< "the curve has not been loaded!" << endl
				<< abort(FatalError);
		}

		if (NOT Info())
		{
			FatalErrorIn("void Perform()") << endl
				<< "no info has been loaded!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(Info());
		const auto& theInfo = *Info();

		geoLib::segList Segments;
		Subdivide(Segments);

		Geo_ItemSort<geoLib::Segment> sorting(&geoLib::Segment::IsLess);
		sorting.Perform(Segments);

		theChain_ = std::make_shared<chain>();
		auto& Pts = theChain_->Points();

		Pts.reserve(Segments.size() + 2);

		const auto& curve = *Curve();
		Pts.push_back(curve.Value(FirstParameter()));

		for (const auto& seg : Segments)
		{
			const auto x = seg.Mean();
			Pts.push_back(curve.Value(x));
		}

		Pts.push_back(curve.Value(LastParameter()));
		Change_IsDone() = Standard_True;
	}

	template<class CurveType, bool RandSamples>
	void Geo_ApprxCurve<CurveType, RandSamples>::Reset()
	{
		theCurve_ = 0;
		theChain_.reset();
	}
}