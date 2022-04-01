#include <Cad2d_IntsctEntity_Pair.hxx>

#include <Cad2d_IntsctEntity.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad2d_IntsctEntity_Pair)
{
	ar& boost::serialization::base_object<Global_Indexed>(*this);
	ar& boost::serialization::base_object<Global_Named>(*this);

	ar& theEntity0_;
	ar& theEntity1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad2d_IntsctEntity_Pair)
{
	ar& boost::serialization::base_object<Global_Indexed>(*this);
	ar& boost::serialization::base_object<Global_Named>(*this);

	ar& theEntity0_;
	ar& theEntity1_;
}