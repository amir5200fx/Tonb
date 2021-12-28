#include <Geo2d_SamplePoints_4Pts.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <OSstream.hxx>
#include <TnbError.hxx>

const Standard_Integer tnbLib::Geo2d_SamplePoints_4Pts::nbPts = 4;

const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_4Pts::P0(0, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_4Pts::P1(1, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_4Pts::P2(1, 1);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_4Pts::P3(0, 1);

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