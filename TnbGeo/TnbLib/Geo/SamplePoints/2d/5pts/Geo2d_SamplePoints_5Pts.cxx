#include <Geo2d_SamplePoints_5Pts.hxx>

#include <Geo_Tools.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::Geo2d_SamplePoints_5Pts::nbPts = 5;

const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_5Pts::P0(0, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_5Pts::P1(1, 0);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_5Pts::P2(1, 1);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_5Pts::P3(0, 1);
const tnbLib::Pnt2d tnbLib::Geo2d_SamplePoints_5Pts::P4(0.5, 0.5);

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