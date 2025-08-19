#pragma once
#ifndef _Cad_gSingularityBase_Header
#define _Cad_gSingularityBase_Header

#include <Cad_SingularityBase.hxx>
#include <Cad_gSingularityBaseFwd.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::shared_ptr<Aft2d_gPlnCurveSurface> 
		Cad_gSingularityBase::ParametricCurve_Pole
		(
			const Pnt2d& theP0, 
			const Pnt2d& theP1
		);

	template<>
	static TnbMesh_EXPORT std::shared_ptr<Aft2d_gPlnCurveSurface>
		Cad_gSingularityBase::ParametricCurve_Line
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		);

}

#endif // !_Cad_gSingularityBase_Header
