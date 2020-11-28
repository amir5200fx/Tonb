#include <StbGMaker_AlgAux.hxx>

#include <Geo_Serialization.hxx>
#include <Entity2d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::StbGMaker_AlgAux)
{
	ar & theAx2_;
	ar & theBoundingBox_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::StbGMaker_AlgAux)
{
	ar & theAx2_;
	ar & theBoundingBox_;
}