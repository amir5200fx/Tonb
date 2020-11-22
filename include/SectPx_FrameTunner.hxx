#pragma once
#ifndef _SectPx_FrameTunner_Header
#define _SectPx_FrameTunner_Header

#include <SectPx_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Frame;

	class SectPx_FrameTunner
		: public SectPx_Entity
	{

		/*Private Data*/

	public:

		SectPx_FrameTunner()
		{}

		void ImportFrame(const std::shared_ptr<SectPx_Frame>& theFrame);
	};
}

#endif // !_SectPx_FrameTunner_Header
