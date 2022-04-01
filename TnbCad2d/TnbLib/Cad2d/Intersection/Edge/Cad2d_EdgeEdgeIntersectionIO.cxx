#include <Cad2d_EdgeEdgeIntersection.hxx>

#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_EdgeEdgeIntersection)
{
	ar& boost::serialization::base_object<Cad2d_EntityEntityIntersection>(*this);

	ar& theEdge0_;
	ar& theEdge1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_EdgeEdgeIntersection)
{
	ar& boost::serialization::base_object<Cad2d_EntityEntityIntersection>(*this);

	ar& theEdge0_;
	ar& theEdge1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad2d_EdgeEdgeIntersection);