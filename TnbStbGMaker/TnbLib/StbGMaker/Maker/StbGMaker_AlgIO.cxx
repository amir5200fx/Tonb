#include <StbGMaker_Alg.hxx>

#include <StbGMaker_WP.hxx>

DECLARE_SAVE_IMP(tnbLib::StbGMaker_Alg)
{
	ar & boost::serialization::base_object<StbGMaker_AlgAux>(*this);
	ar & theWorkingPlanes_;
	ar & theCounter_;
}

DECLARE_LOAD_IMP(tnbLib::StbGMaker_Alg)
{
	ar & boost::serialization::base_object<StbGMaker_AlgAux>(*this);
	ar & theWorkingPlanes_;
	ar & theCounter_;
}