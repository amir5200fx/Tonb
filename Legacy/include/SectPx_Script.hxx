#pragma once
#ifndef _SectPx_Script_Header
#define _SectPx_Script_Header

#include <SectPx_Pars.hxx>

#include <memory>

namespace chaiscript
{
	class ChaiScript;
}

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Frame;

	namespace script
	{

		struct SectPx
		{
			std::shared_ptr<SectPx_Frame> newFrame() const;
		};

		void load_sectpx(chaiscript::ChaiScript&);
	}
}

#endif // !_SectPx_Script_Header
