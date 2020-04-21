#include <Cad2d_Modeler_Plane.hxx>

#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Cad2d_Modeler_Plane::Cad2d_Modeler_Plane()
{
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Modeler_Plane::RemoveFromPlanes
(
	const Standard_Integer theIndex
)
{
	auto iter = thePlanes_.find(theIndex);
	if (iter IS_EQUAL thePlanes_.end())
	{
		FatalErrorIn("std::shared_ptr<Cad2d_Plane> RemoveFromPlanes(const Standard_Integer theIndex)")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	thePlanes_.erase(iter);

	return std::move(item);
}

void tnbLib::Cad2d_Modeler_Plane::InsertToPlanes
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
{
	auto insert = thePlanes_.insert(std::make_pair(theIndex, thePlane));
	if (NOT insert.second)
	{
		FatalErrorIn("void InsertToPlanes(const Standard_Integer theIndex, const std::shared_ptr<Cad2d_Plane>& thePlane)")
			<< "duplicate data: " << theIndex << endl
			<< abort(FatalError);
	}
}