#include <Aft3d_GeoPrcsr.hxx>

#include <Aft3d_Facet.hxx>
#include <Aft3d_SizeFun.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::shared_ptr<tnbLib::Entity3d_Box>& tnbLib::legLib::Aft3d_GeoPrcsr::Domain() const
{
	return theSizeFun_->GetDomain();
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::DimSize() const
{
	return Domain()->Diameter();
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::ElementSize(const Pnt3d& thePnt) const
{
	return theSizeFun_->Value(thePnt);
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::ElementSize(const Aft3d_Facet& theFace) const
{
	return theSizeFun_->Value(theFace.CalcCentre());
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::Oriented(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2,
                                                       const Pnt3d& theCoord) const
{
	return Geo_Tools::Oriented_cgal(theCoord, theP0, theP1, theP2);
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::CalcSquareDistance(const Pnt3d& theP0, const Pnt3d& theP1) const
{
	return theP0.SquareDistance(theP1);
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::CalcDistance(const Pnt3d& theP0, const Pnt3d& theP1) const
{
	return theP0.Distance(theP1);
}

tnbLib::Pnt3d tnbLib::legLib::Aft3d_GeoPrcsr::CalcCentre(const Pnt3d& theP0, const Pnt3d& theP1,
                                                         const Pnt3d& theP2) const
{
	return (theP0 + theP1 + theP2) / 3.0;
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::CalcDistanceFromTriangle(const Pnt3d& theCoord, const Pnt3d& theP0,
	const Pnt3d& theP1, const Pnt3d& theP2) const
{
	return std::sqrt(Geo_Tools::CalcSquareDistancePointFromTriangle_cgal(theCoord, theP0, theP1, theP2));
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::CalcSquareDistanceFromTriangle(const Pnt3d& theCoord, const Pnt3d& theP0,
	const Pnt3d& theP1, const Pnt3d& theP2) const
{
	return Geo_Tools::CalcSquareDistancePointFromTriangle_cgal(theCoord, theP0, theP1, theP2);
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::CalcDistanceEdgeFromEdge(const Pnt3d& theP0, const Pnt3d& theP1,
	const Pnt3d& theQ0, const Pnt3d& theQ1) const
{
	return std::sqrt(Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(theP0, theP1, theQ0, theQ1));
}

Standard_Real tnbLib::legLib::Aft3d_GeoPrcsr::CalcSquareDistanceEdgeFromEdge(const Pnt3d& theP0, const Pnt3d& theP1,
	const Pnt3d& theQ0, const Pnt3d& theQ1) const
{
	return Geo_Tools::CalcSquareDistanceSegmentFromSegment_Eberly(theP0, theP1, theQ0, theQ1);
}

tnbLib::Entity3d_Box tnbLib::legLib::Aft3d_GeoPrcsr::CalcSearchingRegion(const Standard_Real theRadius,
	const Pnt3d& theCentre) const
{
	Entity3d_Box b{ theCentre - theRadius, theCentre + theRadius };
	return std::move(b);
}

tnbLib::Entity3d_Box tnbLib::legLib::Aft3d_GeoPrcsr::CalcSearchingRegion(const Standard_Real theRadius, const Pnt3d& theCentre,
	const Aft3d_Facet&) const
{
	Entity3d_Box b{ theCentre - theRadius, theCentre + theRadius };
	return std::move(b);
}

tnbLib::Entity3d_Box tnbLib::legLib::Aft3d_GeoPrcsr::CalcSearchingRegion(const Standard_Real theRadius,
	const Aft3d_Facet& theFace) const
{
	auto b = CalcSearchingRegion(theRadius, theFace.CalcCentre());
	return std::move(b);
}

tnbLib::Entity3d_Box tnbLib::legLib::Aft3d_GeoPrcsr::CalcEffectiveFront(const Standard_Real theRadius, const Pnt3d& theCentre,
	const Aft3d_Facet&) const
{
	Entity3d_Box b{ theCentre - theRadius, theCentre + theRadius };
	return std::move(b);
}
