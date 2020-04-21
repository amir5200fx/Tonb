#include <Cad2d_Modeler_SrchEng.hxx>

#include <Entity2d_Box.hxx>
#include <error.hxx>
#include <OSstream.hxx>

const std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner>&
tnbLib::Cad2d_Modeler_SrchEng::SelectCorner
(
	const Pnt2d & theCoord
) const
{
	Entity2d_Box b(theCoord - Radius(), theCoord + Radius());
	std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>> items;
	theCorners_.GeometrySearch(b, items);

	if (items.empty())
	{
		return null;
	}

	if (items.size() IS_EQUAL 1) return items[0];
	return Cad2d_Modeler_SrchEng::MinDist(items, theCoord);
}

void tnbLib::Cad2d_Modeler_SrchEng::InsertToSrchEngine
(
	const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
)
{
	const auto& domain = theCorners_.GeometryBoundingBox();
	if (NOT domain.IsInside(theCorner->Coord()))
	{
		ReArrangeSrchEngine();
	}

	theCorners_.InsertToGeometry(theCorner);
}

void tnbLib::Cad2d_Modeler_SrchEng::RemoveFromSrchEngine
(
	const std::shared_ptr<cad2dLib::Modeler_Corner>& theCorner
)
{
	theCorners_.RemoveFromGeometry(theCorner);
}