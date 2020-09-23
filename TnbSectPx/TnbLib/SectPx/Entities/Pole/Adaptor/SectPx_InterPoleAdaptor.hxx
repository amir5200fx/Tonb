#pragma once
#ifndef _SectPx_InterPoleAdaptor_Header
#define _SectPx_InterPoleAdaptor_Header

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Segment;

	class SectPx_InterPoleAdaptor
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Segment> theBackward_;
		std::weak_ptr<SectPx_Segment> theForward_;

	protected:

		SectPx_InterPoleAdaptor()
		{}

	public:

		const auto& Backward() const
		{
			return theBackward_;
		}

		const auto& Forward() const
		{
			return theForward_;
		}

		void SetBackward(const std::shared_ptr<SectPx_Segment>& theSegment)
		{
			theBackward_ = theSegment;
		}

		void SetForward(const std::shared_ptr<SectPx_Segment>& theSegment)
		{
			theForward_ = theSegment;
		}
	};
}

#endif // !_SectPx_InterPoleAdaptor_Header
