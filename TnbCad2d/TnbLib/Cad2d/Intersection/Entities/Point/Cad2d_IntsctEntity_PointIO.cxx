#include <Cad2d_IntsctEntity_Point.hxx>

#include <Pln_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_IntsctEntity_Point)
{
	ar& boost::serialization::base_object<Cad2d_IntsctEntity>(*this);

	ar& theVertex_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_IntsctEntity_Point)
{
	ar& boost::serialization::base_object<Cad2d_IntsctEntity>(*this);

	ar& theVertex_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Cad2d_IntsctEntity_Point);