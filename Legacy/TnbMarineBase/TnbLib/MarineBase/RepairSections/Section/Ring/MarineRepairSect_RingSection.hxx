#pragma once
#ifndef _MarineRepairSect_RingSection_Header
#define _MarineRepairSect_RingSection_Header

#include <MarineRepairSect_Section.hxx>
#include <Cad2d_RemoveNonManifold.hxx>

namespace tnbLib
{

	class MarineRepairSect_RingSection
		: public MarineRepairSect_Section
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_RemoveNonManifold::Segment> theSegment_;

		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	public:


		//- default constructor

		MarineRepairSect_RingSection()
		{}


		//- constructors

		MarineRepairSect_RingSection(const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment)
			: theSegment_(theSegment)
		{}

		MarineRepairSect_RingSection(std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment)
			: theSegment_(std::move(theSegment))
		{}

		MarineRepairSect_RingSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment
		)
			: MarineRepairSect_Section(theIndex, theName)
			, theSegment_(theSegment)
		{}

		MarineRepairSect_RingSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment
		)
			: MarineRepairSect_Section(theIndex, theName)
			, theSegment_(std::move(theSegment))
		{}


		//- public functions and operators

		const auto& Segment() const
		{
			return theSegment_;
		}


		TnbMarine_EXPORT std::vector<std::shared_ptr<Pln_Curve>> FillingCurves() const override;

		void SetSegment(const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment)
		{
			theSegment_ = theSegment;
		}

		void SetSegment(std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment)
		{
			theSegment_ = std::move(theSegment);
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MarineRepairSect_RingSection);

#endif // !_MarineRepairSect_RingSection_Header
