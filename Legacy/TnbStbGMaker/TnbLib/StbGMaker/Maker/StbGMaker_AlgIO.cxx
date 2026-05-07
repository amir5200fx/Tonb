#include <StbGMaker_Alg.hxx>

#include <StbGMaker_WP.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::StbGMaker_Alg)
{
	ar & boost::serialization::base_object<StbGMaker_AlgAux>(*this);
	ar & theWorkingPlanes_;
	ar & theCounter_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::StbGMaker_Alg)
{
	ar & boost::serialization::base_object<StbGMaker_AlgAux>(*this);
	ar & theWorkingPlanes_;
	ar & theCounter_;
}