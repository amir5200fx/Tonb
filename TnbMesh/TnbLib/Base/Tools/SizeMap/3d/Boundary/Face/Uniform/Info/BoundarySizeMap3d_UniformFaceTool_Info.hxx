#pragma once
#ifndef _BoundarySizeMap3d_UniformFaceTool_Info_Header
#define _BoundarySizeMap3d_UniformFaceTool_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [9/6/2022 Amir]
	class Geo3d_ApprxSurfPatch_Info;

	class BoundarySizeMap3d_UniformFaceTool_Info
	{

		/*Private Data*/

		std::shared_ptr<Geo3d_ApprxSurfPatch_Info> theApprxSurfInfo_;

		Standard_Integer theUnBalancing_;
		Standard_Integer theBucketSize_;

		Standard_Integer theNbSamples_;

		Standard_Boolean PostBalance_;


		// private functions and operators [9/6/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT std::shared_ptr<Geo3d_ApprxSurfPatch_Info> DEFAULT_APPRX_SURF_INFO;

		static TnbMesh_EXPORT Standard_Boolean POST_BALANCE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_BUCKET_SIZE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_UNBALANCING;

		static TnbMesh_EXPORT Standard_Integer DEFAULT_NB_SAMPLES;

		// default constructor [9/6/2022 Amir]

		BoundarySizeMap3d_UniformFaceTool_Info()
			: theApprxSurfInfo_(DEFAULT_APPRX_SURF_INFO)
			, theUnBalancing_(DEFAULT_UNBALANCING)
			, theBucketSize_(DEFAULT_BUCKET_SIZE)
			, PostBalance_(POST_BALANCE)
			, theNbSamples_(DEFAULT_NB_SAMPLES)
		{}

		// constructors [9/6/2022 Amir]


		// public functions and operators [9/6/2022 Amir]

		const auto& ApprxSurfInfo() const
		{
			return theApprxSurfInfo_;
		}

		auto UnBalancing() const
		{
			return theUnBalancing_;
		}

		auto BucketSize() const
		{
			return theBucketSize_;
		}

		auto ApplyPostBalance() const
		{
			return PostBalance_;
		}

		auto NbSamples() const
		{
			return theNbSamples_;
		}

		void SetApprxSurfInfo(const std::shared_ptr<Geo3d_ApprxSurfPatch_Info>& theInfo)
		{
			theApprxSurfInfo_ = theInfo;
		}

		void SetApprxSurfInfo(std::shared_ptr<Geo3d_ApprxSurfPatch_Info>&& theInfo)
		{
			theApprxSurfInfo_ = std::move(theInfo);
		}

		void SetUnBalancing(const Standard_Integer n)
		{
			theUnBalancing_ = n;
		}

		void SetBucketSize(const Standard_Integer n)
		{
			theBucketSize_ = n;
		}

		void SetPostBalance(const Standard_Boolean postBalance)
		{
			PostBalance_ = postBalance;
		}

		void SetNbSamples(const Standard_Integer n)
		{
			theNbSamples_ = n;
		}
	};
}

#endif // !_BoundarySizeMap3d_UniformFaceTool_Info_Header
