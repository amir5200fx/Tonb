#include <Pln_EdgeAdaptor.hxx>

#include <Pln_Wire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_EdgeAdaptor)
{
	ar << Wire();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_EdgeAdaptor)
{
	ar >> Wire();
}