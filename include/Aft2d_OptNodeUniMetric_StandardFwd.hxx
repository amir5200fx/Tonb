#pragma once
#ifndef _Aft2d_OptNodeUniMetric_StandardFwd_Header
#define _Aft2d_OptNodeUniMetric_StandardFwd_Header

#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/7/2022 Amir]
	template
		<
		class FrontType,
		class SizeFun,
		class MetricFun,
		class CorrAlg,
		class AltrAlg
		>
		class Aft_OptNode;

	typedef Aft_OptNode
		<
		Aft2d_EdgeAnIso,
		Geo2d_SizeFunction,
		GeoMetricFun2d_Uniform,
		void,
		void
		>
		Aft2d_OptNodeUniMetric_Standard;
}

#endif // !_Aft2d_OptNodeUniMetric_StandardFwd_Header
