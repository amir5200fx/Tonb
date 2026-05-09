#pragma once
#ifndef _BoundarySizeMap3d_SegmentTool_Header
#define _BoundarySizeMap3d_SegmentTool_Header

#include <Mesh3d_BoundarySizeMapTool.hxx>
#include <Mesh_SizeMapTool_Info.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [6/23/2022 Amir]

	class Geo3d_SegmentCloud;

	class BoundarySizeMap3d_SegmentTool
		: public Mesh3d_BoundarySizeMapTool
	{

		/*Private Data*/

		Standard_Integer theMaxNbCorrIters_;

		std::shared_ptr<Geo3d_SegmentCloud> theCloud_;

		// private functions and operators [7/20/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [6/23/2022 Amir]

		BoundarySizeMap3d_SegmentTool()
		{}


		// constructors [6/23/2022 Amir]

		BoundarySizeMap3d_SegmentTool
		(
			const std::shared_ptr<Mesh3d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity3d_Box>& theDomain,
			const std::shared_ptr<Geo3d_SegmentCloud>& theCloud,
			const std::shared_ptr<Cad_TModel>& theModel
		)
			: Mesh3d_BoundarySizeMapTool(theModel, theDomain, theRef)
			, theMaxNbCorrIters_(DEFAULT_MAX_NB_CORR_ITERS)
			, theCloud_(theCloud)
		{}

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_NB_CORR_ITERS;

		
		// public functions and operators [6/23/2022 Amir]


		auto MaxNbCorrIters() const
		{
			return theMaxNbCorrIters_;
		}

		const auto& Cloud() const
		{
			return theCloud_;
		}

		void SetMaxNbCorrIters(const Standard_Integer theIters)
		{
			theMaxNbCorrIters_ = theIters;
		}

		void SetCloud(const std::shared_ptr<Geo3d_SegmentCloud>& theCloud)
		{
			theCloud_ = theCloud;
		}

		void SetCloud(std::shared_ptr<Geo3d_SegmentCloud>&& theCloud)
		{
			theCloud_ = std::move(theCloud);
		}


		TnbMesh_EXPORT std::vector<std::shared_ptr<TModel_Paired>> RetrieveSegments() const;

		TnbMesh_EXPORT void RetrieveSegmentsTo(std::vector<std::shared_ptr<TModel_Paired>>&) const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::BoundarySizeMap3d_SegmentTool);

#endif // !_BoundarySizeMap3d_SegmentTool_Header
