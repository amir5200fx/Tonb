#include <Cad2d_RemoveNonManifold.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_RemoveNonManifold::Node)
{
	ar & theVtx_;
	ar & theSegments_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_RemoveNonManifold::Node)
{
	ar & theVtx_;
	ar & theSegments_;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_RemoveNonManifold::Segment)
{
	ar & theEdges_;

	ar & theNode0_;
	ar & theNode1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_RemoveNonManifold::Segment)
{
	ar & theEdges_;

	ar & theNode0_;
	ar & theNode1_;
}

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_RemoveNonManifold::Ring)
{
	ar & boost::serialization::base_object<Cad2d_RemoveNonManifold::Segment>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_RemoveNonManifold::Ring)
{
	ar & boost::serialization::base_object<Cad2d_RemoveNonManifold::Segment>(*this);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad2d_RemoveNonManifold::Segment);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad2d_RemoveNonManifold::Ring);