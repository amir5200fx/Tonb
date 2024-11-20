#pragma once
#ifndef _Cad_SingularityTools_Header
#define _Cad_SingularityTools_Header

#include <Mesh_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_TriangulationFwd.hxx>
#include <Global_TypeDef.hxx>
#include <Global_Handle.hxx>

#include <vector>
#include <memory>

class Geom_Surface;
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [3/30/2022 Amir]
	class Pln_Curve;

	template<class CurveType>
	class Cad_PoleSingularCurve;

	class Cad_SingularityTools
	{

		/*Private Data*/

	public:

		static TnbMesh_EXPORT std::vector<std::shared_ptr<Pln_Curve>> 
			RetrieveSides(const Entity2d_Box&);

		static TnbMesh_EXPORT std::shared_ptr<Entity2d_Triangulation> 
			GetTriangulation(const Entity2d_Box&);

		static TnbMesh_EXPORT Handle(Geom2d_Curve) GetParaCurve(const Pnt2d&, const Pnt2d&);
		static TnbMesh_EXPORT Handle(Geom2d_Curve) GetParaCurve(const std::vector<Pnt2d>&);

		static TnbMesh_EXPORT Pnt2d 
			FindParametricCoord
			(
				const Entity2d_Polygon& thePoly, 
				const Geom_Surface&, 
				const Standard_Real theLength
			);

		template<class CurveType>
		static std::shared_ptr<Cad_PoleSingularCurve<CurveType>> 
			ParametricPoleCurve(const Entity2d_Polygon&);
	};
}

#include <Cad_SingularityToolsI.hxx>

#endif // !_Cad_SingularityTools_Header
