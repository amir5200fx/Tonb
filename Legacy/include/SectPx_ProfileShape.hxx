#pragma once
#ifndef _SectPx_ProfileShape_Header
#define _SectPx_ProfileShape_Header

#include <SectPx_Shape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoSegment;

	class SectPx_ProfileShape
		: public SectPx_Shape
	{

		/*Private Data*/

		std::shared_ptr<SectPx_TopoSegment> theSegment_;

	public:

		SectPx_ProfileShape()
		{}

		SectPx_ProfileShape(const Standard_Integer theIndex, const word& theName);

		SectPx_ProfileShape(const std::shared_ptr<SectPx_TopoSegment>& theSegment);

		SectPx_ProfileShape(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<SectPx_TopoSegment>& theSegment);


		const auto& Segment() const
		{
			return theSegment_;
		}

		void SetSegment(const std::shared_ptr<SectPx_TopoSegment>& theSegment)
		{
			theSegment_ = theSegment;
		}



		Standard_Boolean IsProfile() const override;
	};
}

#endif // !_SectPx_ProfileShape_Header
