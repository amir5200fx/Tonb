#pragma once
#ifndef _BoundarySizeMap2d_UniformSegmentTool_Header
#define _BoundarySizeMap2d_UniformSegmentTool_Header

#include <BoundarySizeMap2d_SegmentTool.hxx>

namespace tnbLib
{

	// Forward Declarations [6/23/2023 Payvand]
	class Geo_BasicApprxCurve_Info;

	class BoundarySizeMap2d_UniformSegmentTool
		: public BoundarySizeMap2d_SegmentTool
	{

		/*Private Data*/

		std::shared_ptr<Geo_BasicApprxCurve_Info> theInfo_;

		Standard_Integer theUnBalancing_;
		Standard_Integer theBucketSize_;
		Standard_Boolean PostBalance_;

		// Private functions and operators [6/23/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [6/23/2023 Payvand]

		BoundarySizeMap2d_UniformSegmentTool()
		{}

	public:

		static TnbMesh_EXPORT std::shared_ptr<Geo_BasicApprxCurve_Info> DEFAULT_INFO;
		static TnbMesh_EXPORT Standard_Boolean POST_BALANCE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_BUCKET_SIZE;
		static TnbMesh_EXPORT Standard_Integer DEFAULT_UNBALANCING;

		// constructors [6/23/2023 Payvand]

		BoundarySizeMap2d_UniformSegmentTool
		(
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Geo2d_SegmentCloud>& theCloud,
			const std::shared_ptr<Cad2d_Plane>& theModel
		)
			: BoundarySizeMap2d_SegmentTool(theRef, theDomain, theCloud, theModel)
			, theInfo_(DEFAULT_INFO)
			, PostBalance_(POST_BALANCE)
			, theBucketSize_(DEFAULT_BUCKET_SIZE)
			, theUnBalancing_(DEFAULT_UNBALANCING)
		{}

		// Public functions and operators [6/23/2023 Payvand]

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

		void Perform() override;

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

BOOST_CLASS_EXPORT_KEY(tnbLib::BoundarySizeMap2d_UniformSegmentTool);

#endif // !_BoundarySizeMap2d_UniformSegmentTool_Header
