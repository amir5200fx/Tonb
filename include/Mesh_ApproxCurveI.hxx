#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <algorithm>
namespace tnbLib
{

	namespace meshLib
	{

		class ApproxCuvreTools
		{

		public:

			typedef Mesh_ApproxCurveBase::Segment Segment;

			static inline auto CalcXs(const Standard_Integer nbPnts, const Standard_Real x0, const Standard_Real x1)
			{
				Debug_If_Condition(nbPnts <= 0);
				std::vector<Standard_Real> xs;
				xs.reserve(nbPnts + 2);
				const auto dx = (x1 - x0) / (nbPnts + 1);
				xs.push_back(x0);
				for (size_t i = 1; i <= nbPnts; i++)
				{
					auto x = x0 + i * dx;
					xs.push_back(x);
				}
				xs.push_back(x1);
				return std::move(xs);
			}

			template<class CurveType>
			static auto CalcSamples(const CurveType& theCurve, const std::vector<Standard_Real>& xs)
			{
				std::vector<typename cascadeLib::pt_type_from_curve<CurveType>::ptType> samples;
				samples.reserve(xs.size());
				for (const auto x : xs)
				{
					auto p = theCurve.Value(x);
					samples.push_back(std::move(p));
				}
				return std::move(samples);
			}

			template<class Point>
			static auto ApproxLength(const std::vector<Point>& samples)
			{
				Standard_Real len = 0;
				for (size_t i = 1; i < samples.size(); i++)
				{
					const auto& p0 = samples.at(i);
					const auto& p1 = samples.at(i - 1);

					len += p0.Distance(p1);
				}
				return len;
			}

			template<class CurveType>
			static auto CalcSegPoints(const CurveType& theCurve, const Segment& theSeg)
			{
				Debug_If_Condition(theSeg.X0 IS_EQUAL theSeg.X1);
				const auto P0 = theCurve.Value(theSeg.X0);
				const auto P1 = theCurve.Value(theSeg.X1);

				auto t = std::make_pair(std::move(P0), std::move(P1));
				return std::move(t);
			}

			template<class CurveType>
			static void Subdivide
			(
				const CurveType& theCurve,
				const Segment& theSeg, 
				const Standard_Integer theNbSamples, 
				const Standard_Real theTarget,
				const Standard_Real theMinSize,
				const Standard_Integer theLev, 
				const Standard_Integer theInitLev,
				const Standard_Integer theMaxLev, 
				std::vector<Segment>& theSegs
			)
			{
				if (theLev < theInitLev)
				{
					Subdivide
					(
						theCurve, theSeg.Left(),
						theNbSamples, theTarget,
						theMinSize, theLev + 1,
						theInitLev, theMaxLev,
						theSegs
					);

					Subdivide
					(
						theCurve, theSeg.Right(),
						theNbSamples, theTarget,
						theMinSize, theLev + 1,
						theInitLev, theMaxLev,
						theSegs
					);
					return;
				}

				if (theLev > theMaxLev)
				{
					theSegs.push_back(theSeg);
					return;
				}

				auto samples = CalcSamples(theCurve, CalcXs(theNbSamples, theSeg.X0, theSeg.X1));
				auto len = ApproxLength<typename cascadeLib::pt_type_from_curve<CurveType>::ptType>(samples);

				if (len < theTarget)
				{
					theSegs.push_back(theSeg);
					return;
				}
				else
				{
					Subdivide
					(
						theCurve, theSeg.Left(),
						theNbSamples, theTarget,
						theMinSize, theLev + 1,
						theInitLev, theMaxLev,
						theSegs
					);

					Subdivide
					(
						theCurve, theSeg.Right(),
						theNbSamples, theTarget,
						theMinSize, theLev + 1,
						theInitLev, theMaxLev,
						theSegs
					);
				}
			}
		};
	}
}

template<class CurveType>
inline void tnbLib::Mesh_ApproxCurve<CurveType>::Subdivide(std::vector<Segment>& theSegs) const
{
	meshLib::ApproxCuvreTools::Subdivide<typename remove_pointer<CurveType>::type>
		(
			*Curve(),
			Segment(U0(), U1()),
			AlgInfo()->NbSamples(),
			AlgInfo()->TargetSize(),
			AlgInfo()->MinSize(),
			0,
			AlgInfo()->MinNbSubdivisions(),
			AlgInfo()->MaxNbSubdivisions(),
			theSegs
			);
}

template<class CurveType>
inline void tnbLib::Mesh_ApproxCurve<CurveType>::Perform()
{
	if (NOT Curve())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded." << endl
			<< abort(FatalError);
	}

	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded." << endl
			<< abort(FatalError);
	}

	std::vector<Segment> segments;
	Subdivide(segments);

	std::sort(segments.begin(), segments.end(), [](const Segment& s0, const Segment& s1) {return s0.Mean() < s1.Mean(); });

	theMesh_ = std::make_shared<chain>();
	auto& pts = theMesh_->Points();

	pts.reserve(segments.size() + 1);

	const auto& curve = *Curve();
	pts.push_back(curve.Value(U0()));

	for (const auto& seg : segments)
	{
		auto p = curve.Value(seg.X1);
		pts.push_back(std::move(p));
	}
	Change_IsDone() = Standard_True;
}