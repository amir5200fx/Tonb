#include <Cad2d_Modeler_Corner.hxx>

#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	const Standard_Real cad2dLib::Modeler_Corner::DEFAULT_RADIUS(1.0E-4);
}

tnbLib::cad2dLib::Modeler_Corner::Modeler_Corner()
	: theTol_(0)
	, theRadius_(DEFAULT_RADIUS)
{
}

tnbLib::cad2dLib::Modeler_Corner::Modeler_Corner
(
	const Standard_Integer theIndex
)
	: Modeler_Entity(theIndex)
	, theTol_(0)
	, theRadius_(DEFAULT_RADIUS)
{
}

tnbLib::cad2dLib::Modeler_Corner::Modeler_Corner
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Modeler_Entity(theIndex, theName)
	, theTol_(0)
	, theRadius_(DEFAULT_RADIUS)
{
}

void tnbLib::cad2dLib::Modeler_Corner::InsertToCorners
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	auto insert = theVertices_.insert(std::make_pair(theIndex, theVtx));
	if (NOT insert.second)
	{
		FatalErrorIn("void InsertToCorners(const Standard_Integer theIndex, const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "Duplicate data!" << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::cad2dLib::Modeler_Corner::Remove
(
	const Standard_Integer theIndex
)
{
	auto iter = theVertices_.find(theIndex);
	if (iter IS_EQUAL theVertices_.end())
	{
		FatalErrorIn("std::shared_ptr<Pln_Vertex> Remove(const Standard_Integer theIndex)")
			<< "the item is not int the tree" << endl
			<< abort(FatalError);
	}

	auto p = iter->second;
	theVertices_.erase(iter);
	return std::move(p);
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Entity>
tnbLib::cad2dLib::Modeler_Corner::Copy() const
{
	auto crn = std::make_shared<Modeler_Corner>(Index(), Name());
	Debug_Null_Pointer(crn);

	crn->theRadius_ = Radius();
	crn->theTol_ = Tolerance();

	crn->theCoord_ = Coord();

	return std::move(crn);
}