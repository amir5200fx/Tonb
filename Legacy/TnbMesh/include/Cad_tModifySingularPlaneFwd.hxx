#pragma once
#ifndef _Cad_tModifySingularPlaneFwd_Header
#define _Cad_tModifySingularPlaneFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/3/2022 Amir]
	template<class SurfType>
	class Cad_ModifySingularPlane;

	class TModel_Surface;

	typedef Cad_ModifySingularPlane<TModel_Surface> Cad_tModifySingularPlane;
}

#endif // !_Cad_tModifySingularPlaneFwd_Header
