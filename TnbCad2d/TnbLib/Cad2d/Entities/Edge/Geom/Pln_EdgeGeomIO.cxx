#include <Pln_EdgeGeom.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Curve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_EdgeGeom)
{
	ar & theCurve_;
	ar & Sense_;
	ar & theMesh_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_EdgeGeom)
{
	ar & theCurve_;
	ar & Sense_;
	ar & theMesh_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Pln_EdgeGeom);