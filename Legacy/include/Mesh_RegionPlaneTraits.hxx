#pragma once
#ifndef _Mesh_RegionPlaneTraits_Header
#define _Mesh_RegionPlaneTraits_Header

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;
	class GModel_ParaCurve;
	class TModel_ParaCurve;

	class Cad2d_Plane;
	class GModel_Plane;
	class TModel_Plane;

	template<class CurveType> struct Mesh_RegionPlaneTraits {};

	template<> struct Mesh_RegionPlaneTraits<Pln_Curve> { typedef Cad2d_Plane plnType; };
	template<> struct Mesh_RegionPlaneTraits<GModel_ParaCurve> { typedef GModel_Plane plnType; };
	template<> struct Mesh_RegionPlaneTraits<TModel_ParaCurve> { typedef TModel_Plane plnType; };
}

#endif // !_Mesh_RegionPlaneTraits_Header
