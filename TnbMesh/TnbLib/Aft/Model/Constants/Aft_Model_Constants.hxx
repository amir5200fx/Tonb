#pragma once
#ifndef _Aft_Model_Constants_Header
#define _Aft_Model_Constants_Header

#include <Standard_TypeDef.hxx>

#include <Mesh_Module.hxx>

namespace tnbLib
{

	struct Aft_Model_Constants
	{
		static TnbMesh_EXPORT const Standard_Integer ALLOWED_MAX_LEVEL_GENERATION;

		static TnbMesh_EXPORT const Standard_Real DEFAULT_LOCALFRONT_FACTOR;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_MIN_DISTANCE_FACTOR;
	};
}

#endif // !_Aft_Model_Constants_Header
