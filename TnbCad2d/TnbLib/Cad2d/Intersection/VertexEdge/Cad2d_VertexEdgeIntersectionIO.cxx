#include <Cad2d_VertexEdgeIntersection.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_VertexEdgeIntersection)
{
	ar& boost::serialization::base_object<Cad2d_EntityEntityIntersection>(*this);
	ar& theVtx_;
	ar& theEdge_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_VertexEdgeIntersection)
{
	ar& boost::serialization::base_object<Cad2d_EntityEntityIntersection>(*this);
	ar& theVtx_;
	ar& theEdge_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad2d_VertexEdgeIntersection);