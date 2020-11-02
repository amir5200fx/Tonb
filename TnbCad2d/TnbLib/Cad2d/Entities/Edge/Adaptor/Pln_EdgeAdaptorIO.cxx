#include <Pln_EdgeAdaptor.hxx>

#include <Pln_Wire.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_EdgeAdaptor)
{
	ar << Wire();
}

DECLARE_LOAD_IMP(tnbLib::Pln_EdgeAdaptor)
{
	ar >> Wire();
}