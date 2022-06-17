#pragma once
#ifndef _Aft_OptNode_Tools_Header
#define _Aft_OptNode_Tools_Header

#include <Mesh_Module.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Aft_OptNode_Tools
	{

		/*Private Data*/

	public:

		static TnbMesh_EXPORT std::tuple<Pnt2d, Pnt2d, Standard_Boolean> 
			BisectInitialGuess
			(
				const Geo2d_MetricPrcsrAnIso& theMetricMap,
				const Pnt2d& theP0,
				const Pnt2d& theGuess,
				const Standard_Real h,
				const Standard_Integer theMaxLev
			);
	};
}

#endif // !_Aft_OptNode_Tools_Header
