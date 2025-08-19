#include <Cad2d_Modeler_Corner.hxx>

#include <Pln_Vertex.hxx>
#include <TnbError.hxx>
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

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Corner::IsContains
(
	const std::shared_ptr<Pln_Vertex>& theVtx
) const
{
	auto iter = theVertices_.find(theVtx->Index());
	if (iter IS_EQUAL theVertices_.end())
	{
		return Standard_False;
	}
	if (iter->second NOT_EQUAL theVtx)
	{
		return Standard_False;
	}
	return Standard_True;
}

tnbLib::Pnt2d 
tnbLib::cad2dLib::Modeler_Corner::CalcMeanCoord() const
{
	const auto& vertices = Vertices();
	if (vertices.empty())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< " the corner is orphan!" << endl
			<< abort(FatalError);
	}
	auto iter = vertices.begin();

	auto coord = iter->second->Coord();
	iter++;
	while (iter NOT_EQUAL vertices.end())
	{
		coord += iter->second->Coord();
		iter++;
	}
	coord /= (vertices.size());
	return std::move(coord);
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