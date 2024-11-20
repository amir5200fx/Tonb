#pragma once
#ifndef _GeoMesh_Background_Info_Header
#define _GeoMesh_Background_Info_Header

#include <Mesh_Module.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	class GeoMesh_Background_SmoothingHvCorrection_Info
	{

		/*Private Data*/

		Standard_Integer theMaxNbIters_;
		Standard_Real theFactor_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theMaxNbIters_;
			ar & theFactor_;
		}

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MX_NB_ITERS;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_FACTOR;

		GeoMesh_Background_SmoothingHvCorrection_Info()
			: theMaxNbIters_(DEFAULT_MX_NB_ITERS)
			, theFactor_(DEFAULT_FACTOR)
		{}


		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, MaxNbIters)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Factor)
	};

	class GeoMesh_Background_SmoothingLaplacian_Info
	{

		/*Private Data*/

		Standard_Integer theMaxNbIters_;
		Standard_Real theFactor_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theMaxNbIters_;
			ar & theFactor_;
		}

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MX_NB_ITERS;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_FACTOR;

		GeoMesh_Background_SmoothingLaplacian_Info()
			: theMaxNbIters_(DEFAULT_MX_NB_ITERS)
			, theFactor_(DEFAULT_FACTOR)
		{}


		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, MaxNbIters)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Factor)
	};
}

#endif // !_GeoMesh_Background_Info_Header
