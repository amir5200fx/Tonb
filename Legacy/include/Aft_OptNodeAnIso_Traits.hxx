#pragma once
#ifndef _Aft_OptNodeAnIso_Traits_Header
#define _Aft_OptNodeAnIso_Traits_Header

#include <Aft2d_OptNodeAnIso_StandardFwd.hxx>
#include <Aft2d_OptNodeAnIso_nonIterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeUniMetric_nonIterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeUniMetric_IterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeSurface_nonIterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeAnIso_StandardFwd.hxx>
#include <Aft2d_OptNodeSurface_StandardFwd.hxx>
#include <Aft2d_OptNodeSurface_AltrFwd.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_IterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_nonIterAdaptiveFwd.hxx>

namespace tnbLib
{

	template<class T>
	struct info_type_from_aniso_optNode_alg{};

	// Forward Declarations [3/5/2022 Amir]
	class Aft2d_OptNodeAnIso_nonIterAdaptiveInfo;
	class Aft_SizeCorr_IterativeInfo;

	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeAnIso_nonIterAdaptive> { typedef Aft2d_OptNodeAnIso_nonIterAdaptiveInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeUniMetric_nonIterAdaptive> { typedef Aft2d_OptNodeAnIso_nonIterAdaptiveInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeUniMetric_IterAdaptive> { typedef Aft_SizeCorr_IterativeInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeAnIso_Standard> { typedef Aft_SizeCorr_IterativeInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeSurface_Standard> { typedef Aft_SizeCorr_IterativeInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeSurface_nonIterAdaptive> { typedef Aft2d_OptNodeAnIso_nonIterAdaptiveInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeSurfaceUniMetric_IterAdaptive> { typedef Aft_SizeCorr_IterativeInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeSurfaceUniMetric_nonIterAdaptive> { typedef Aft2d_OptNodeAnIso_nonIterAdaptiveInfo infoType; };
	template<> struct info_type_from_aniso_optNode_alg<Aft2d_OptNodeSurface_Altr> { typedef Aft_SizeCorr_IterativeInfo infoType; };
}

#endif // !_Aft_OptNodeAnIso_Traits_Header
