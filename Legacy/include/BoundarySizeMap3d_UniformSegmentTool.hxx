#pragma once
#ifndef _BoundarySizeMap3d_UniformSegmentTool_Header
#define _BoundarySizeMap3d_UniformSegmentTool_Header

#include <BoundarySizeMap3d_SegmentTool.hxx>

namespace tnbLib
{

	// Forward Declarations [8/25/2022 Amir]
	class Geo_BasicApprxCurve_Info;

	class BoundarySizeMap3d_UniformSegmentTool
		: public BoundarySizeMap3d_SegmentTool
	{

		/*Private Data*/

		std::shared_ptr<Geo_BasicApprxCurve_Info> theInfo_;

		Standard_Integer theUnBalancing_;
		Standard_Integer theBucketSize_;
		Standard_Boolean PostBalance_;

		// private functions and operators [7/20/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [7/18/2022 Amir]

		BoundarySizeMap3d_UniformSegmentTool()
		{}

	public:

		static TnbMesh_EXPORT std::shared_ptr<Geo_BasicApprxCurve_Info> DEFAULT_INFO;
		static TnbMesh_EXPORT Standard_Boolean POST_BALANCE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_BUCKET_SIZE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_UNBALANCING;

		// constructors [7/18/2022 Amir]

		BoundarySizeMap3d_UniformSegmentTool
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef, 
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const std::shared_ptr<Geo3d_SegmentCloud>& theCloud,
			const std::shared_ptr<Cad_TModel>& theModel
		)
			: BoundarySizeMap3d_SegmentTool(theRef, theDomain, theCloud, theModel)
			, theInfo_(DEFAULT_INFO)
			, PostBalance_(POST_BALANCE)
			, theBucketSize_(DEFAULT_BUCKET_SIZE)
			, theUnBalancing_(DEFAULT_UNBALANCING)
		{}

		// public functions and operators [7/18/2022 Amir]

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

		TnbMesh_EXPORT void Perform() override;

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

BOOST_CLASS_EXPORT_KEY(tnbLib::BoundarySizeMap3d_UniformSegmentTool);

#endif // !_BoundarySizeMap3d_UniformSegmentTool_Header
