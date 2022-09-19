#include <Geo2d_SamplePoints_4Pts.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

const Standard_Integer tnbLib::Geo2d_SamplePoints_4Pts::nbPts = 4;

tnbLib::Geo2d_SamplePoints_4Pts::Geo2d_SamplePoints_4Pts()
	: P0(Pnt2d(0, 0))
	, P1(Pnt2d(1, 0))
	, P2(Pnt2d(1, 1))
	, P3(Pnt2d(0, 1))
{}

tnbLib::Pnt2d
tnbLib::Geo2d_SamplePoints_4Pts::CalcPoint
(
	const Standard_Integer theIndex,
	const Entity2d_Box & theRegion
) const
{
#include <Geo2d_SamplePoints_Interpolate.jxx>
}

std::vector<tnbLib::Pnt2d>
tnbLib::Geo2d_SamplePoints_4Pts::RetrieveSamples() const
{
#include <Geo2d_SamplePoints_RetrievePoints.jxx>
}