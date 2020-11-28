#include <Pln_WireAux.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_WireAux)
{
	ar & BoundingBox();
	ar & Orientation();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_WireAux)
{
	Entity2d_Box b;
	Pln_Orientation ori;
	ar & b;
	ar & ori;

	SetBoundingBox(std::move(b));
	SetOrientation(ori);
}