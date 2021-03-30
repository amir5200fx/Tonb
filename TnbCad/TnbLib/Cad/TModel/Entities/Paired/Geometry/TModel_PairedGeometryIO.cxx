#include <TModel_PairedGeometry.hxx>

#include <Entity3d_Polygon.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_PairedGeometry)
{
	ar & theMesh_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_PairedGeometry)
{
	ar & theMesh_;
}