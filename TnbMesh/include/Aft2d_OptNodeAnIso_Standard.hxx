#pragma once
#ifndef _Aft2d_OptNodeAnIso_Standard_Header
#define _Aft2d_OptNodeAnIso_Standard_Header

#include <Aft2d_OptNodeAnIso_StandardFwd.hxx>
#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeAnIso_Standard::Perform();

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeAnIso_Standard::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeAnIso_Standard::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_OptNodeAnIso_Standard);

#endif // !_Aft2d_OptNodeAnIso_Standard_Header
