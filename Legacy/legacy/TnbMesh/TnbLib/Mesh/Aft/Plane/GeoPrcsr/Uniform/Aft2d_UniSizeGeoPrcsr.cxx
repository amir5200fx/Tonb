#include <Aft2d_UniSizeGeoPrcsr.hxx>

#include <Aft2d_Edge.hxx>
#include <Aft2d_Node.hxx>
#include <Geo_Tools.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity2d_Box.hxx>

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::BaseSize() const
{
	return theSize_;
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::ElementSize(const Pnt2d&) const
{
	return theSize_;
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::ElementSize(const Aft2d_Edge&) const
{
	return theSize_;
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::Oriented
(
	const Pnt2d& theCoord,
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	return Geo_Tools::Oriented_cgal(theCoord, theP0, theP1);
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcUnitDistance
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1
) const
{
	return Distance(theP0, theP1) / theSize_;
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcDistance
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	return Distance(theP0, theP1);
}

Standard_Real
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcDistanceSQ
(
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	return SquareDistance(theP0, theP1);
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcDistanceFromSegment
(
	const Pnt2d& theCoord,
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	return Geo_Tools::Distance_cgal(theCoord, theP0, theP1);
}

Standard_Real 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcDistanceFromSegmentSQ
(
	const Pnt2d& theCoord, 
	const Pnt2d& theP0,
	const Pnt2d& theP1
) const
{
	return Geo_Tools::SquareDistance_cgal(theCoord, theP0, theP1);
}

tnbLib::Pnt2d 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcOptmCoord
(
	const Standard_Real theH, 
	const Aft2d_Edge& theEdge
) const
{
	const auto& m = theEdge.Centre();
	auto v = (theEdge.Node1()->Coord() - m).UnitLength();
	v.Rotate90ccw();

	auto pt = m + theH * v;
	return std::move(pt);
}

tnbLib::Pnt2d 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcCentre
(
	const Pnt2d& theP0, 
	const Pnt2d& theP1
) const
{
	auto m = Geo_Tools::CalcCentre(theP0, theP1);
	return std::move(m);
}

tnbLib::Entity2d_Box
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcSearchRegion
(
	const Standard_Real theRadius,
	const Pnt2d& theCentre
) const
{
	auto b = Entity2d_Box::Box(theCentre, theRadius);
	return std::move(b);
}

tnbLib::Entity2d_Box 
tnbLib::legLib::Aft2d_UniSizeGeoPrcsr::CalcSearchRegion
(
	const Standard_Real theRadius,
	const Pnt2d& theCentre, 
	const Aft2d_Edge& /*theEdge*/
) const
{
	auto b = Entity2d_Box::Box(theCentre, theRadius);
	return std::move(b);
}