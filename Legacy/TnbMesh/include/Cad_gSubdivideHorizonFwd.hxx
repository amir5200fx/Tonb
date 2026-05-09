#pragma once
#ifndef _Cad_gSubdivideHorizonFwd_Header
#define _Cad_gSubdivideHorizonFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/21/2022 Amir]
	template<class PlnCurveType>
	class Cad_SubdivideHorizon;

	typedef Cad_SubdivideHorizon<Aft2d_gPlnCurveSurface> Cad_gSubdivideHorizon;
}

#endif // !_Cad_gSubdivideHorizonFwd_Header
