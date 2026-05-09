#pragma once
#ifndef _BoundarySizeMap2d_UniformSegmentTool_Header
#define _BoundarySizeMap2d_UniformSegmentTool_Header

#include <BoundarySizeMap2d_SegmentTool.hxx>

namespace tnbLib
{

	// Forward Declarations [6/23/2023 Payvand]
	class BoundarySizeMap2d_UniformSegmentTool_Info;

	class BoundarySizeMap2d_UniformSegmentTool
		: public BoundarySizeMap2d_SegmentTool
	{

		/*Private Data*/

		std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool_Info> theInfo_;


		// Private functions and operators [6/23/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [6/23/2023 Payvand]

		BoundarySizeMap2d_UniformSegmentTool()
		{}

	public:


		// constructors [6/23/2023 Payvand]

		BoundarySizeMap2d_UniformSegmentTool
		(
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Geo2d_SegmentCloud>& theCloud,
			const std::shared_ptr<Cad2d_Plane>& theModel,
			const std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool_Info>& theInfo
		)
			: BoundarySizeMap2d_SegmentTool(theRef, theDomain, theCloud, theModel)
			, theInfo_(theInfo)
		{}

		// Public functions and operators [6/23/2023 Payvand]

		const auto& ApproxInfo() const
		{
			return theInfo_;
		}

		void Perform() override;

		void SetApproxInfo(const std::shared_ptr<BoundarySizeMap2d_UniformSegmentTool_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::BoundarySizeMap2d_UniformSegmentTool);

#endif // !_BoundarySizeMap2d_UniformSegmentTool_Header
