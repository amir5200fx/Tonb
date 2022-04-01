#include <Cad2d_VertexVertexIntersection.hxx>

#include <Pln_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_VertexVertexIntersection)
{
	ar& boost::serialization::base_object<Cad2d_EntityEntityIntersection>(*this);

	ar& theVtx0_;
	ar& theVtx1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_VertexVertexIntersection)
{
	ar& boost::serialization::base_object<Cad2d_EntityEntityIntersection>(*this);

	ar& theVtx0_;
	ar& theVtx1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad2d_VertexVertexIntersection);