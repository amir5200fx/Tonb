#include <Cad2d_Modeler_Plane.hxx>

#include <Cad2d_Plane.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::cad2dLib::Modeler_Plane::Modeler_Plane()
{
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Plane::IsContainPlane
(
	const Standard_Integer theIndex
) const
{
	auto iter = thePlanes_.find(theIndex);
	if (iter IS_EQUAL thePlanes_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Plane::IsContain
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
) const
{
	Debug_Null_Pointer(thePlane);
	return IsContainPlane(thePlane->Index());
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::cad2dLib::Modeler_Plane::RemoveFromPlanes
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

const std::shared_ptr<tnbLib::Cad2d_Plane> &
tnbLib::cad2dLib::Modeler_Plane::SelectPlane
(
	const Standard_Integer theIndex
) const
{
	auto iter = thePlanes_.find(theIndex);
	if (iter IS_EQUAL thePlanes_.end())
	{
		FatalErrorIn("std::shared_ptr<Cad2d_Plane> SelectPlanes(const Standard_Integer) const")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

void tnbLib::cad2dLib::Modeler_Plane::InsertToPlanes
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