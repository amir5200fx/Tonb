#pragma once
#ifndef _SectPx_BndPoleAdaptor_Header
#define _SectPx_BndPoleAdaptor_Header

#include <Global_Serialization.hxx>
#include <SectPx_Module.hxx>


#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Segment;
	class SectPx_TopoSegment;

	class SectPx_BndPoleAdaptor
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Segment> theSegment_;
		std::weak_ptr<SectPx_TopoSegment> theTopoSegment_;

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:

		SectPx_BndPoleAdaptor()
		{}

	public:

		const auto& Segment() const
		{
			return theSegment_;
		}

		const auto& TopoSegment() const
		{
			return theTopoSegment_;
		}

		void SetSegment
		(
			const std::shared_ptr<SectPx_Segment>& theSegment
		)
		{
			theSegment_ = theSegment;
		}

		void SetTopoSegment
		(
			const std::shared_ptr<SectPx_TopoSegment>& theSegment
		)
		{
			theTopoSegment_ = theSegment;
		}
	};
}

#endif // !_SectPx_BndPoleAdaptor_Header