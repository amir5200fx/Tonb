#pragma once
#ifndef _MeshBase_Tools_Header
#define _MeshBase_Tools_Header

#include <Standard_Handle.hxx>
#include <Standard_TypeDef.hxx>
#include <Mesh_Module.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>

#include <vector>

//- Forward Declarations
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pln_Curve;
	class GModel_ParaCurve;
	class TModel_ParaCurve;

	class MeshBase_Tools
	{

	public:

		static TnbMesh_EXPORT void SetSourcesToMesh
		(
			const std::vector<std::pair<Pnt2d, Standard_Real>>& theSources,
			const Standard_Real theBaseSize, 
			GeoMesh2d_Background& theMesh
		);

		static TnbMesh_EXPORT const Handle(Geom2d_Curve)& Geometry(const std::shared_ptr<Pln_Curve>& theCurve);
		static TnbMesh_EXPORT const Handle(Geom2d_Curve)& Geometry(const std::shared_ptr<TModel_ParaCurve>& theCurve);
		static TnbMesh_EXPORT const Handle(Geom2d_Curve)& Geometry(const std::shared_ptr<GModel_ParaCurve>& theCurve);

		static TnbMesh_EXPORT Standard_Real FirstParameter(const std::shared_ptr<Pln_Curve>& theCurve);
		static TnbMesh_EXPORT Standard_Real FirstParameter(const std::shared_ptr<TModel_ParaCurve>& theCurve);
		static TnbMesh_EXPORT Standard_Real FirstParameter(const std::shared_ptr<GModel_ParaCurve>& theCurve);

		static TnbMesh_EXPORT Standard_Real LastParameter(const std::shared_ptr<Pln_Curve>& theCurve);
		static TnbMesh_EXPORT Standard_Real LastParameter(const std::shared_ptr<TModel_ParaCurve>& theCurve);
		static TnbMesh_EXPORT Standard_Real LastParameter(const std::shared_ptr<GModel_ParaCurve>& theCurve);
	};
}

#endif // !_MeshBase_Tools_Header
