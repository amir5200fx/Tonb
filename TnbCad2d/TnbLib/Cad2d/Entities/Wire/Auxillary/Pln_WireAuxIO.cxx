#include <Pln_WireAux.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_WireAux)
{
	ar & BoundingBox();
	ar & Orientation();
}

DECLARE_LOAD_IMP(tnbLib::Pln_WireAux)
{
	Entity2d_Box b;
	Pln_Orientation ori;
	ar & b;
	ar & ori;

	SetBoundingBox(std::move(b));
	SetOrientation(ori);
}