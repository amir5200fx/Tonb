#pragma once
#ifndef _Aft2d_OptNodeSurface_Altr_Header
#define _Aft2d_OptNodeSurface_Altr_Header

#include <Aft_OptNode.hxx>
#include <Aft2d_OptNodeSurface_Calculator.hxx>
#include <Aft2d_OptNodeSurface_AltrFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_Altr::Perform();


	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_Altr::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_Altr::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_OptNodeSurface_Altr);

#endif // !_Aft2d_OptNodeSurface_Altr_Header
