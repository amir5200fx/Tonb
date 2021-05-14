#include <GModel_SurfaceGeometry.hxx>

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