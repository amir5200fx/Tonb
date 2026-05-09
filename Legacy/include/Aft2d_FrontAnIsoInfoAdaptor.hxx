#pragma once
#ifndef _Aft2d_FrontAnIsoInfoAdaptor_Header
#define _Aft2d_FrontAnIsoInfoAdaptor_Header

#include <Mesh_Module.hxx>
#include <Aft2d_FrontInfoAdaptorTemplate.hxx>
#include <Aft2d_NodeAnIsoFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_ElementAnIsoFwd.hxx>
#include <Aft_FrontTraits.hxx>
#include <Aft2d_FrontAnIsoInfoAdaptorFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_FrontAnIsoInfoAdaptor::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_FrontAnIsoInfoAdaptor::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_FrontAnIsoInfoAdaptor_Header