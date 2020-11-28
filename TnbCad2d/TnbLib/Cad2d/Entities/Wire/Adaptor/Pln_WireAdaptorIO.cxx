#include <Pln_WireAdaptor.hxx>

#include <Cad2d_Plane.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_WireAdaptor)
{
	ar & Plane();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_WireAdaptor)
{
	ar & Plane();
}

