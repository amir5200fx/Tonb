#include <TModel_GeneratedEdgeGeometry.hxx>

#include <TModel_Curve.hxx>
#include <Entity3d_Polygon.hxx>
#include <Entity2d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_GeneratedEdgeGeometry)
{
	ar & theCurve_;
	ar & theMesh_;
	ar & theParaMesh_;
	ar & theSense_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_GeneratedEdgeGeometry)
{
	ar & theCurve_;
	ar & theMesh_;
	ar & theParaMesh_;
	ar & theSense_;
}