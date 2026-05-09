#include <GeoTop2d_Vertex.hxx>

#include <GeoTop2d_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::GeoTop2d_Edge> 
tnbLib::GeoTop2d_Vertex::ForwardBoundaryEdge() const
{
	auto vtx = std::dynamic_pointer_cast<GeoTop2d_Vertex>(This());
	for (const auto& x : Edges())
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		if (edge->IsOnBoundary())
		{
			if (edge->First() IS_EQUAL vtx)
			{
				return std::move(edge);
			}
		}
	}
	return nullptr;
}

std::shared_ptr<tnbLib::GeoTop2d_Edge> 
tnbLib::GeoTop2d_Vertex::BackwardBoundaryEdge() const
{
	auto vtx = std::dynamic_pointer_cast<GeoTop2d_Vertex>(This());
	for (const auto& x : Edges())
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		if (edge->IsOnBoundary())
		{
			if (edge->Second() IS_EQUAL vtx)
			{
				return std::move(edge);
			}
		}
	}
	return nullptr;
}