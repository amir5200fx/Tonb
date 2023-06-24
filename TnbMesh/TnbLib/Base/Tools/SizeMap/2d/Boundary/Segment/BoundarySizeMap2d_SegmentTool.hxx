#pragma once
#ifndef _BoundarySizeMap2d_SegmentTool_Header
#define _BoundarySizeMap2d_SegmentTool_Header

#include <Mesh2d_BoundarySizeMapTool.hxx>
#include <Geo2d_SegmentCloudFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations


	class BoundarySizeMap2d_SegmentTool
		: public Mesh2d_BoundarySizeMapTool
	{

		/*Private Data*/

		Standard_Integer theMaxNbCorrIters_;

		std::shared_ptr<Geo2d_SegmentCloud> theCloud_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);
		
	protected:

		//- default constructor

		BoundarySizeMap2d_SegmentTool()
		{}


		// constructors [6/23/2023 Payvand]

		BoundarySizeMap2d_SegmentTool
		(
			const std::shared_ptr<Mesh2d_ReferenceValues>& theRef,
			const std::shared_ptr<Entity2d_Box>& theDomain,
			const std::shared_ptr<Geo3d_SegmentCloud>& theCloud,
			const std::shared_ptr<Cad2d_Plane>& theModel
		)
			: Mesh2d_BoundarySizeMapTool(theModel, theDomain, theRef)
			, theMaxNbCorrIters_(DEFAULT_MAX_NB_CORR_ITERS)
			, theCloud_(theCloud)
		{}

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_NB_CORR_ITERS;



		//- public functions and operators

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

		void SetCloud(const std::shared_ptr<Geo2d_SegmentCloud>& theCloud)
		{
			theCloud_ = theCloud;
		}

		void SetCloud(std::shared_ptr<Geo2d_SegmentCloud>&& theCloud)
		{
			theCloud_ = std::move(theCloud);
		}

		TnbMesh_EXPORT std::vector<std::shared_ptr<Pln_Edge>> RetrieveSegments() const;

		TnbMesh_EXPORT void RetrieveSegmentsTo(std::vector<std::shared_ptr<Pln_Edge>>&) const;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::BoundarySizeMap2d_SegmentTool);

#endif // !_BoundarySizeMap2d_SegmentTool_Header
