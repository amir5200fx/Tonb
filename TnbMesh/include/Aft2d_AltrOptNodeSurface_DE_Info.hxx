#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_DE_Info_Header
#define _Aft2d_AltrOptNodeSurface_DE_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Aft2d_AltrOptNodeSurface_DE_Info
	{

		/*Private Data*/

		Standard_Integer theGenSize_;
		Standard_Integer thePopSize_;

		Standard_Real theMutWeight_;
		Standard_Real theMutCross_;


		// private functions and operators [6/12/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theGenSize_;
			ar & thePopSize_;
			ar & theMutWeight_;
			ar & theMutCross_;
		}

	public:

		static TnbMesh_EXPORT const std::string extension;

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_GEN_SIZE;
		static TnbMesh_EXPORT const Standard_Integer DEFAULT_POP_SIZE;

		static TnbMesh_EXPORT const Standard_Real DEFAULT_MUT_WEIGHT;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_MUT_CROSS;

		// default constructor [6/12/2022 Amir]

		Aft2d_AltrOptNodeSurface_DE_Info()
			: theGenSize_(DEFAULT_GEN_SIZE)
			, thePopSize_(DEFAULT_POP_SIZE)
			, theMutWeight_(DEFAULT_MUT_WEIGHT)
			, theMutCross_(DEFAULT_MUT_CROSS)
		{}


		// constructors [6/12/2022 Amir]


		// public functions and operators [6/12/2022 Amir]

		auto GenSize() const
		{
			return theGenSize_;
		}

		auto PopSize() const
		{
			return thePopSize_;
		}

		auto MutWeight() const
		{
			return theMutWeight_;
		}

		auto MutCross() const
		{
			return theMutCross_;
		}

		void SetGenSize(const Standard_Integer n)
		{
			theGenSize_ = n;
		}

		void SetPopSize(const Standard_Integer n)
		{
			thePopSize_ = n;
		}

		void SetMutWeight(const Standard_Real x)
		{
			theMutWeight_ = x;
		}

		void SetMutCross(const Standard_Real x)
		{
			theMutCross_ = x;
		}
	};
}

#endif // !_Aft2d_AltrOptNodeSurface_DE_Info_Header
