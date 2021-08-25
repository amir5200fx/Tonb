#pragma once
#ifndef _MarineRepairSect_AnalyzSection_Header
#define _MarineRepairSect_AnalyzSection_Header

#include <Marine_Entity.hxx>
#include <Cad2d_RemoveNonManifold.hxx>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_CmpSection;

	class MarineRepairSect_AnalyzSection
		: public Marine_Entity
	{

		/*Private Data*/

		std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> theSegments_;


	public:

		//- default constructor

		MarineRepairSect_AnalyzSection()
		{}


		//- constructors

		MarineRepairSect_AnalyzSection
		(
			const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& theSegments
		)
			: theSegments_(theSegments)
		{}

		MarineRepairSect_AnalyzSection
		(
			std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>&& theSegments
		)
			: theSegments_(std::move(theSegments))
		{}

		MarineRepairSect_AnalyzSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& theSegments
		)
			: Marine_Entity(theIndex, theName)
			, theSegments_(theSegments)
		{}

		MarineRepairSect_AnalyzSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>&& theSegments
		)
			: Marine_Entity(theIndex, theName)
			, theSegments_(std::move(theSegments))
		{}


		//- public functions and operators

		const auto& Segments() const
		{
			return theSegments_;
		}


		TnbMarine_EXPORT Standard_Boolean HasDefectSegment() const;
		TnbMarine_EXPORT Standard_Integer CalcNbDefectSegments() const;

		std::shared_ptr<MarineRepairSect_CmpSection> CalcCmpSection() const;

		void SetSegments(const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& theSegments)
		{
			theSegments_ = theSegments;
		}

		void SetSegments(std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>&& theSegments)
		{
			theSegments_ = std::move(theSegments);
		}
	};
}

#endif // !_MarineRepairSect_AnalyzSection_Header
