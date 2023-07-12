#include <Geo2d_BasicApprxCurve.hxx>

#include <Geo2d_BasicApprxCurveAdaptor.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	typedef Geo_ApprxCurveBase::Segment Segment;
	typedef typename Geo_ApprxCurveBase::segList segList;

	void Subdivide
	(
		const Geom2d_Curve& theCurve,
		const Segment& theSeg,
		const Standard_Integer theNbSamples,
		const Standard_Real theApprox,
		const Standard_Real theMinSizeSQ,
		const Standard_Integer theLevel,
		const Standard_Integer theInitLev,
		const Standard_Integer theMaxLev,
		segList& theSegments
	)
	{
		if (theLevel < theInitLev)
		{
			Subdivide
			(
				theCurve,
				theSeg.Left(),
				theNbSamples,
				theApprox, theMinSizeSQ, theLevel + 1,
				theInitLev, theMaxLev, theSegments
			);

			Subdivide
			(
				theCurve,
				theSeg.Right(),
				theNbSamples,
				theApprox, theMinSizeSQ, theLevel + 1,
				theInitLev, theMaxLev, theSegments
			);
			return;
		}

		if (theLevel >= theMaxLev)
		{
			theSegments.push_back(theSeg);
			return;
		}

		auto segPnts = geoLib::CalcSegPoints(theCurve, theSeg);
		auto sqDis = geoLib::CalcSqDist<Geom2d_Curve>(segPnts);

		if (sqDis <= theMinSizeSQ)
			return;

		auto samples =
			geoLib::CalcSamples
			(
				theCurve,
				geoLib::CalcXs<Geom2d_Curve, false>::_(theNbSamples, theSeg.theX0, theSeg.theX1)
			);

		auto approx = geoLib::CalcApproximate<Geom2d_Curve>(segPnts, samples);

		if (theApprox * sqDis < approx)
		{
			Subdivide
			(
				theCurve,
				theSeg.Left(),
				theNbSamples,
				theApprox, theMinSizeSQ, theLevel + 1,
				theInitLev, theMaxLev, theSegments
			);

			Subdivide
			(
				theCurve,
				theSeg.Right(),
				theNbSamples,
				theApprox, theMinSizeSQ, theLevel + 1,
				theInitLev, theMaxLev, theSegments
			);
			return;
		}
		theSegments.push_back(theSeg);
	}
}

template<>
void tnbLib::Geo2d_BasicApprxCurve::Subdivide(segList& theSegments) const
{
	Debug_Null_Pointer(Info());
	const auto& theInfo = *Info();

	const auto& geometry = Curve()->Geometry();
	::tnbLib::Subdivide
	(
		*geometry,
		Segment(FirstParameter(), LastParameter()),
		theInfo.NbSamples(),
		theInfo.Approx() * theInfo.Approx(),
		theInfo.MinSize() * theInfo.MinSize(),
		0, theInfo.InitNbSubdivision(),
		theInfo.MaxNbSubdivision(), theSegments
	);
}