#include <Pln_WireAdaptor.hxx>

#include <Cad2d_Plane.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_WireAdaptor)
{
	ar & Plane();
}

DECLARE_LOAD_IMP(tnbLib::Pln_WireAdaptor)
{
	ar & Plane();
}

