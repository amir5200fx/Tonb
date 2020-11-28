#include <Pln_EdgeGeom.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_EdgeGeom)
{
	bool sense = Sense();
	ar << Curve();
	ar << sense;
	ar << Mesh();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_EdgeGeom)
{
	ar >> Curve();
	ar >> ChangeSense();
	ar >> Mesh();
}