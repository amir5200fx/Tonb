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

	class SectPx_BndPoleAdaptor
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Segment> theSegment_;

		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

		SectPx_BndPoleAdaptor()
		{}

	public:

		const auto& Segment() const
		{
			return theSegment_;
		}

		void SetSegment(const std::shared_ptr<SectPx_Segment>& theSegment)
		{
			theSegment_ = theSegment;
		}
	};
}

#endif // !_SectPx_BndPoleAdaptor_Header