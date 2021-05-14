#include <GModel_SurfaceGeometry.hxx>

#include <Cad_GeomSurface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_SurfaceGeometry)
{
	ar & theGeometry_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_SurfaceGeometry)
{
	ar & theGeometry_;
}