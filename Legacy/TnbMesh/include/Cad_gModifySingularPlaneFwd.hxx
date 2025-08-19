#pragma once
#ifndef _Cad_gModifySingularPlaneFwd_Header
#define _Cad_gModifySingularPlaneFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/3/2022 Amir]
	template<class SurfType>
	class Cad_ModifySingularPlane;

	class GModel_Surface;

	typedef Cad_ModifySingularPlane<GModel_Surface> Cad_gModifySingularPlane;
}

#endif // !_Cad_gModifySingularPlaneFwd_Header
