#include <TModel_GeneratedEdgeGeometry.hxx>

#include <TModel_Curve.hxx>
#include <Entity3d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_GeneratedEdgeGeometry)
{
	ar & theCurve_;
	ar & theMesh_;
	ar & theSense_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_GeneratedEdgeGeometry)
{
	ar & theCurve_;
	ar & theMesh_;
	ar & theSense_;
}