#pragma once
#ifndef _MarineRepairSect_Segment_Header
#define _MarineRepairSect_Segment_Header

#include <Cad2d_RemoveNonManifold.hxx>
#include <Marine_Module.hxx>

namespace tnbLib
{

	class MarineRepairSect_Segment
		: public Global_Indexed
	{

		/*Private Data*/

		std::shared_ptr<Cad2d_RemoveNonManifold::Segment> theSegment_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMarine_EXPORT);

	protected:

		//- default constructor

		MarineRepairSect_Segment()
		{}


		//- constructors

		MarineRepairSect_Segment
		(
			const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment
		)
			: theSegment_(theSegment)
		{}

		MarineRepairSect_Segment
		(
			std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment
		)
			: theSegment_(std::move(theSegment))
		{}

		MarineRepairSect_Segment
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment
		)
			: Global_Indexed(theIndex)
			, theSegment_(theSegment)
		{}

		MarineRepairSect_Segment
		(
			const Standard_Integer theIndex,
			std::shared_ptr<Cad2d_RemoveNonManifold::Segment>&& theSegment
		)
			: Global_Indexed(theIndex)
			, theSegment_(std::move(theSegment))
		{}

	public:


		//- public functions and operators

		const auto& Segment() const
		{
			return theSegment_;
		}

		virtual Standard_Boolean IsCrossed() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsHovered() const
		{
			return Standard_False;
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::MarineRepairSect_Segment);

#endif // !_MarineRepairSect_Segment_Header
