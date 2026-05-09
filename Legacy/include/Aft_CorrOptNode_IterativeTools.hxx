#pragma once
#ifndef _Aft_CorrOptNode_IterativeTools_Header
#define _Aft_CorrOptNode_IterativeTools_Header

#include <Geo_SizeFunctionTraits.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [3/1/2022 Amir]
	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	class Aft_SizeCorr_IterativeInfo;
	class Pnt2d;

	class Aft_CorrOptNode_IterativeTools
	{

		/*Private Data*/

	public:

		template<class FrontType, class SizeFun, class MetricFun, class InfoType>
		static Standard_Boolean
			Correct
			(
				const Geo_MetricPrcsr<SizeFun, MetricFun>& theMap,
				typename point_type_from_sizeMap<SizeFun>::ptType& theP0,
				const FrontType& theEdge,
				const InfoType& theInfo
			);

		template<class SizeFun, class MetricFun, class InfoType>
		static Standard_Boolean 
			Correct
			(
				const Geo_MetricPrcsr<SizeFun, MetricFun>& theMap,
				const typename point_type_from_sizeMap<SizeFun>::ptType& theP0,
				typename point_type_from_sizeMap<SizeFun>::ptType& theP,
				const Standard_Real h,
				const InfoType& theInfo
			);

		// Returns false if the algorithm is converged [5/26/2022 Amir]
		template<class SizeFun, class MetricFun, class InfoType>
		static Standard_Boolean
			CorrectOptNode
			(
				const Geo_MetricPrcsr<SizeFun, MetricFun>& theMap,
				const Pnt2d& theV0,
				const Pnt2d& theV1,
				const Pnt2d& theCentre,
				Pnt2d& theP0,
				const Standard_Real h,
				const InfoType& theInfo
			);
	};
}

#include <Aft_CorrOptNode_IterativeToolsI.hxx>

#endif // !_Aft_CorrOptNode_IterativeTools_Header
