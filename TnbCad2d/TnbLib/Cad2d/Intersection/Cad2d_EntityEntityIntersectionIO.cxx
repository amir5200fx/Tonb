#include <Cad2d_EntityEntityIntersection.hxx>

#include <Cad2d_IntsctEntity_Pair.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_EntityEntityIntersection)
{
	ar& boost::serialization::base_object<Global_Indexed>(*this);
	ar& boost::serialization::base_object<Global_Named>(*this);

	ar& theEntities_;
	ar& theTolerance_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_EntityEntityIntersection)
{
	ar& boost::serialization::base_object<Global_Indexed>(*this);
	ar& boost::serialization::base_object<Global_Named>(*this);

	ar& theEntities_;
	ar& theTolerance_;
}