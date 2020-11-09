#include <StbGMaker_AlgAux.hxx>

#include <Geo_Serialization.hxx>
#include <Entity2d_Box.hxx>

DECLARE_SAVE_IMP(tnbLib::StbGMaker_AlgAux)
{
	ar & theAx2_;
	ar & theBoundingBox_;
}

DECLARE_LOAD_IMP(tnbLib::StbGMaker_AlgAux)
{
	ar & theAx2_;
	ar & theBoundingBox_;
}