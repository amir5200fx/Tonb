#pragma once
#ifndef _Cad_gLineSingularCurve_Header
#define _Cad_gLineSingularCurve_Header

#include <Cad_LineSingularCurve.hxx>
#include <Cad_gLineSingularCurveFwd.hxx>
#include <Cad_gSingularCurve.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_gPlnCurveSurface>, 
		std::shared_ptr<Aft2d_gPlnCurveSurface>
		> 
		Cad_gLineSingularCurve::Split(const Standard_Real x) const;
}

#endif // !_Cad_gLineSingularCurve_Header
