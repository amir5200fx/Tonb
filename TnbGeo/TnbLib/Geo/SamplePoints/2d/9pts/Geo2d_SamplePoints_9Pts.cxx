#include <Geo2d_SamplePoints_9Pts.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Geo2d_SamplePoints_9Pts::nbPts = 9;

const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P0(0, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P1(0.5, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P2(1, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P3(1, 0.5);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P4(1, 1);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P5(0.5, 1);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P6(0, 1);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P7(0, 0.5);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_9Pts::P8(0.5, 0.5);

tnbLib::Pnt2d
tnbLib::Geo2d_SamplePoints_9Pts::CalcPoint
(
	const Standard_Integer theIndex,
	const Entity2d_Box & theRegion
) const
{
#include <Geo2d_SamplePoints_Interpolate.jxx>
}

std::vector<tnbLib::Pnt2d>
tnbLib::Geo2d_SamplePoints_9Pts::RetrieveSamples() const
{
#include <Geo2d_SamplePoints_RetrievePoints.jxx>
}