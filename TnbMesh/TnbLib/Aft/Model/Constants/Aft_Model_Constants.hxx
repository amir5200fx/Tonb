#pragma once
#ifndef _Aft_Model_Constants_Header
#define _Aft_Model_Constants_Header

#include <Standard_TypeDef.hxx>

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{

	struct Aft_Model_Constants
	{
		static TnbMesh_EXPORT const Standard_Integer ALLOWED_MAX_LEVEL_GENERATION;

		static TnbMesh_EXPORT const Standard_Real DEFAULT_LOCALFRONT_FACTOR;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_MIN_DISTANCE_FACTOR;

	private:

		// Private functions and operators [11/25/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			// empty body [11/25/2021 Amir]
		}

	};
}

#endif // !_Aft_Model_Constants_Header
