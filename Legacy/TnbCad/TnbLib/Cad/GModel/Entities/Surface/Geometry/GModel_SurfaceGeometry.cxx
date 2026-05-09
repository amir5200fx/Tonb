#include <GModel_SurfaceGeometry.hxx>

#include <Cad_Tools.hxx>
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

Handle(Poly_Triangulation)
tnbLib::GModel_SurfaceGeometry::RetrieveTriangulation() const
{
	if (Face().IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "no face has been found." << endl
			<< abort(FatalError);
	}
	auto tri = Cad_Tools::RetrieveTriangulation(Face());
	return std::move(tri);
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