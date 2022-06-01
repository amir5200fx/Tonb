#include <Geo2d_SamplePoints_5Pts.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Geo2d_SamplePoints_5Pts::nbPts = 5;


tnbLib::Geo2d_SamplePoints_5Pts::Geo2d_SamplePoints_5Pts()
	: P0(Pnt2d(0, 0))
	, P1(Pnt2d(1, 0))
	, P2(Pnt2d(1, 1))
	, P3(Pnt2d(0, 1))
	, P4(Pnt2d(0.5, 0.5))
{}

tnbLib::Pnt2d
tnbLib::Geo2d_SamplePoints_5Pts::CalcPoint
(
	const Standard_Integer theIndex,
	const Entity2d_Box & theRegion
) const
{
#include <Geo2d_SamplePoints_Interpolate.jxx>
}

std::vector<tnbLib::Pnt2d>
tnbLib::Geo2d_SamplePoints_5Pts::RetrieveSamples() const
{
#include <Geo2d_SamplePoints_RetrievePoints.jxx>
}