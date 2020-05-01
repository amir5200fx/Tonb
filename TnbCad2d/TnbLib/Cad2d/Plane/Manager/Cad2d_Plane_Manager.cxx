#include <Cad2d_Plane_Manager.hxx>

#include <Cad_EntityManager.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Integer
tnbLib::cad2dLib::Plane_Manager::NbCorners() const
{
	Debug_Null_Pointer(theVertices_);
	return (Standard_Integer)theVertices_->Size();
}

Standard_Integer
tnbLib::cad2dLib::Plane_Manager::NbSegments() const
{
	Debug_Null_Pointer(theEdges_);
	return (Standard_Integer)theEdges_->Size();
}

void tnbLib::cad2dLib::Plane_Manager::RetrieveCornersTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities
) const
{
	Debug_Null_Pointer(Corners());
	const auto& corners = Corners()->RetrieveEntities();

	theEntities.reserve(corners.size());
	for (const auto& x : corners)
	{
		theEntities.push_back(x);
	}
}

void tnbLib::cad2dLib::Plane_Manager::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities
) const
{
	Debug_Null_Pointer(Segments());
	const auto& segments = Segments()->RetrieveEntities();

	theEntities.reserve(segments.size());
	for (const auto& x : segments)
	{
		theEntities.push_back(x);
	}
}