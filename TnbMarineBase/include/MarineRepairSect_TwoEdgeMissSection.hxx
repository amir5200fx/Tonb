#pragma once
#ifndef _MarineRepairSect_TwoEdgeMissSection_Header
#define _MarineRepairSect_TwoEdgeMissSection_Header

#include <MarineRepairSect_Section.hxx>

namespace tnbLib
{

	// Forward Declarations
	class MarineRepairSect_HoverSegment;


	class MarineRepairSect_TwoEdgeMissSection
		: public MarineRepairSect_Section
	{

		/*Private Data*/

		std::shared_ptr<MarineRepairSect_HoverSegment> theSegment0_;
		std::shared_ptr<MarineRepairSect_HoverSegment> theSegment1_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	public:


		//- default constructor

		MarineRepairSect_TwoEdgeMissSection()
		{}


		//- constructors

		MarineRepairSect_TwoEdgeMissSection
		(
			const std::shared_ptr<MarineRepairSect_HoverSegment>& theSegment0,
			const std::shared_ptr<MarineRepairSect_HoverSegment>& theSegment1
		)
			: theSegment0_(theSegment0)
			, theSegment1_(theSegment1)
		{}

		MarineRepairSect_TwoEdgeMissSection
		(
			std::shared_ptr<MarineRepairSect_HoverSegment>&& theSegment0,
			std::shared_ptr<MarineRepairSect_HoverSegment>&& theSegment1
		)
			: theSegment0_(std::move(theSegment0))
			, theSegment1_(std::move(theSegment1))
		{}

		MarineRepairSect_TwoEdgeMissSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<MarineRepairSect_HoverSegment>& theSegment0,
			const std::shared_ptr<MarineRepairSect_HoverSegment>& theSegment1
		)
			: MarineRepairSect_Section(theIndex, theName)
			, theSegment0_(theSegment0)
			, theSegment1_(theSegment1)
		{}

		MarineRepairSect_TwoEdgeMissSection
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<MarineRepairSect_HoverSegment>&& theSegment0,
			std::shared_ptr<MarineRepairSect_HoverSegment>&& theSegment1
		)
			: MarineRepairSect_Section(theIndex, theName)
			, theSegment0_(std::move(theSegment0))
			, theSegment1_(std::move(theSegment1))
		{}


		//- public functions and operators

		const auto& Segment0() const
		{
			return theSegment0_;
		}

		const auto& Segment1() const
		{
			return theSegment1_;
		}

		TnbMarine_EXPORT std::vector<std::shared_ptr<Pln_Curve>> FillingCurves() const override;


		void LoadSegment0(const std::shared_ptr<MarineRepairSect_HoverSegment>& theSegment)
		{
			theSegment0_ = theSegment;
		}

		void LoadSegment1(const std::shared_ptr<MarineRepairSect_HoverSegment>& theSegment)
		{
			theSegment1_ = theSegment;
		}

		void LoadSegment0(std::shared_ptr<MarineRepairSect_HoverSegment>&& theSegment)
		{
			theSegment0_ = std::move(theSegment);
		}

		void LoadSegment1(std::shared_ptr<MarineRepairSect_HoverSegment>&& theSegment)
		{
			theSegment1_ = std::move(theSegment);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MarineRepairSect_TwoEdgeMissSection);

#endif // !_MarineRepairSect_TwoEdgeMissSection_Header
