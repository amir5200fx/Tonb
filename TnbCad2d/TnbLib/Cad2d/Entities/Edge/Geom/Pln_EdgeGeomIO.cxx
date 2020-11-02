#include <Pln_EdgeGeom.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Curve.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_EdgeGeom)
{
	ar << Curve();
	ar << Sense();
	ar << Mesh();
}

DECLARE_LOAD_IMP(tnbLib::Pln_EdgeGeom)
{
	ar >> Curve();
	ar >> ChangeSense();
	ar >> Mesh();
}