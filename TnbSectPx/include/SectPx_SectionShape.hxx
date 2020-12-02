#pragma once
#ifndef _SectPx_SectionShape_Header
#define _SectPx_SectionShape_Header

#include <SectPx_Shape.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoSegment;

	class SectPx_SectionShape
		: public SectPx_Shape
	{

		/*Private Data*/

		std::vector<std::shared_ptr<SectPx_TopoSegment>> theSegments_;

	public:

		SectPx_SectionShape()
		{}

		SectPx_SectionShape
		(
			const std::vector<std::shared_ptr<SectPx_TopoSegment>>& theSegments
		)
			: theSegments_(theSegments)
		{}

		SectPx_SectionShape
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::vector<std::shared_ptr<SectPx_TopoSegment>>& theSegments
		)
			: SectPx_Shape(theIndex, theName)
			, theSegments_(theSegments)
		{}


		const auto& Segments() const
		{
			return theSegments_;
		}

		void SetProfiles
		(
			const std::vector<std::shared_ptr<SectPx_TopoSegment>>& theSegments
		)
		{
			theSegments_ = theSegments;
		}


		Standard_Boolean IsSection() const override;
	};
}

#endif // !_SectPx_SectionShape_Header
