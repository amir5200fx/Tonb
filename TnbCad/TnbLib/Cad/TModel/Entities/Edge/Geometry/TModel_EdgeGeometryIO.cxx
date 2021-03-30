#include <TModel_EdgeGeometry.hxx>

#include <TModel_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <Entity3d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_EdgeGeometry)
{
	ar & theCurve_;
	ar & theParaCurve_;

	ar & theMesh_;

	ar & theSense_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_EdgeGeometry)
{
	ar & theCurve_;
	ar & theParaCurve_;

	ar & theMesh_;

	ar & theSense_;
}