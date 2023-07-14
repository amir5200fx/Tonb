#pragma once
#ifndef _BoundarySizeMap2d_UniformSegmentTool_Info_Header
#define _BoundarySizeMap2d_UniformSegmentTool_Info_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/14/2023 Payvand]
	class Geo_BasicApprxCurve_Info;

	class BoundarySizeMap2d_UniformSegmentTool_Info
	{

		/*Private Data*/

		std::shared_ptr<Geo_BasicApprxCurve_Info> theInfo_;

		Standard_Integer theUnBalancing_;
		Standard_Integer theBucketSize_;
		Standard_Boolean PostBalance_;

		// Private functions and operators [7/14/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT std::shared_ptr<Geo_BasicApprxCurve_Info> DEFAULT_INFO;
		static TnbMesh_EXPORT Standard_Boolean POST_BALANCE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_BUCKET_SIZE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_UNBALANCING;

		// default constructor [7/14/2023 Payvand]

		BoundarySizeMap2d_UniformSegmentTool_Info()
			: theInfo_(DEFAULT_INFO)
			, theUnBalancing_(DEFAULT_UNBALANCING)
			, theBucketSize_(DEFAULT_BUCKET_SIZE)
			, PostBalance_(POST_BALANCE)
		{}

		// constructors [7/14/2023 Payvand]


		// Public functions and operators [7/14/2023 Payvand]

		const auto& ApproxInfo() const
		{
			return theInfo_;
		}

		auto PostBalance() const
		{
			return PostBalance_;
		}

		auto BucketSize() const
		{
			return theBucketSize_;
		}

		auto UnBalancing() const
		{
			return theUnBalancing_;
		}

		void SetApproxInfo(const std::shared_ptr<Geo_BasicApprxCurve_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetPostBalance(const Standard_Boolean postBalance)
		{
			PostBalance_ = postBalance;
		}

		void SetBucketSize(const Standard_Integer theSize)
		{
			theBucketSize_ = theSize;
		}

		void SetUnBalancing(const Standard_Integer theValue)
		{
			theUnBalancing_ = theValue;
		}

	};
}

#endif // !_BoundarySizeMap2d_UniformSegmentTool_Info_Header
