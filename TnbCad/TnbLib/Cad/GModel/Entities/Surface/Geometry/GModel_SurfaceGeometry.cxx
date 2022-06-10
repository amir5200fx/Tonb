#include <GModel_SurfaceGeometry.hxx>

#include <Cad_GeomSurface.hxx>
#include <Pnt3d.hxx>
#include <Pnt2d.hxx>

tnbLib::GModel_SurfaceGeometry::GModel_SurfaceGeometry
(
	const std::shared_ptr<Cad_GeomSurface>& theGeometry
)
	: theGeometry_(theGeometry)
{
	// empty body
}

tnbLib::GModel_SurfaceGeometry::GModel_SurfaceGeometry
(
	std::shared_ptr<Cad_GeomSurface>&& theGeometry
)
	: theGeometry_(std::move(theGeometry))
{
	// empty body
}

tnbLib::Pnt3d 
tnbLib::GModel_SurfaceGeometry::Value
(
	const Pnt2d & theCoord
) const
{
	Debug_Null_Pointer(GeomSurface());
	auto pt = GeomSurface()->Value(theCoord);
	return std::move(pt);
}