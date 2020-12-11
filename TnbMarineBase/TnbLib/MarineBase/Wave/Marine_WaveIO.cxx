#include <Marine_Wave.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom_Surface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_WaveGeometry)
{
	ar & theCurveGeometry_;
	ar & theSurfaceGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_WaveGeometry)
{
	ar & theCurveGeometry_;
	ar & theSurfaceGeometry_;
}