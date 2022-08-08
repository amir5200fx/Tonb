#include <TModel_EdgeGeometry.hxx>

#include <TModel_ParaCurve.hxx>
#include <Entity3d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_EdgeGeometry)
{
	ar & theParaCurve_;
	ar & theMesh_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_EdgeGeometry)
{
	ar & theParaCurve_;
	ar & theMesh_;
}