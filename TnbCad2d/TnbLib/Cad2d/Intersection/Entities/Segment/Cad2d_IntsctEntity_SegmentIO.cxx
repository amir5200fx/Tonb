#include <Cad2d_IntsctEntity_Segment.hxx>

#include <Pln_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_IntsctEntity_Segment)
{
	ar& boost::serialization::base_object<Cad2d_IntsctEntity>(*this);
	ar& theEdge_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_IntsctEntity_Segment)
{
	ar& boost::serialization::base_object<Cad2d_IntsctEntity>(*this);
	ar& theEdge_;
}