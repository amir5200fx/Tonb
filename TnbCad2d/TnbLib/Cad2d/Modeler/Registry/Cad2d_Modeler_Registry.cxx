#include <Cad2d_Modeler_Registry.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	const std::shared_ptr<Pln_Edge> cad2dLib::Modeler_Registry::null_edge = std::make_shared<Pln_Edge>();
}

tnbLib::cad2dLib::Modeler_Registry::Modeler_Registry()
{
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::cad2dLib::Modeler_Registry::RemoveEdgeFromRegistry
(
	const Standard_Integer theIndex
)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn("std::shared_ptr<Pln_Edge> RemoveEdgeFromRegistry(const Standard_Integer theIndex)")
			<< "the item is not in the tree: " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theEdges_.erase(iter);
	return std::move(item);
}

void tnbLib::cad2dLib::Modeler_Registry::RegisterToEdges
(
	const Standard_Integer theIndex,
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	auto insert = theEdges_.insert(std::make_pair(theIndex, theEdge));
	if (NOT insert.second)
	{
		FatalErrorIn("void RegisterToEdges(const Standard_Integer theIndex, const std::shared_ptr<Pln_Edge>& theEdge)")
			<< "duplicate data: " << theIndex << endl
			<< abort(FatalError);
	}
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Registry::IsContainEdge
(
	const Standard_Integer theIndex
) const
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
		return Standard_False;
	return Standard_True;
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Registry::IsContain
(
	const std::shared_ptr<Pln_Edge>& theEdge
) const
{
	Debug_Null_Pointer(theEdge);
	return IsContainEdge(theEdge->Index());
}

const std::shared_ptr<tnbLib::Pln_Edge>& 
tnbLib::cad2dLib::Modeler_Registry::SelectEdge
(
	const Standard_Integer theIndex
) const
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		return null_edge;
	}
	return iter->second;
}

Standard_Boolean 
tnbLib::cad2dLib::Modeler_Registry::IsNull
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	return theEdge IS_EQUAL null_edge;
}