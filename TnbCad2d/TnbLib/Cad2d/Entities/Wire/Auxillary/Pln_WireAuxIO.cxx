#include <Pln_WireAux.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_WireAux)
{
	ar & theBoundingBox_;
	ar & theOrientation_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_WireAux)
{
	ar & theBoundingBox_;
	ar & theOrientation_;
}