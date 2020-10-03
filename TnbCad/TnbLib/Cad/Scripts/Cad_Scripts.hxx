#pragma once
#ifndef _Cad_Scripts_Header
#define _Cad_Scripts_Header

#include <memory>

namespace chaiscript
{
	class ChaiScript;
}

namespace tnbLib
{

	namespace script
	{

		void load_cad(chaiscript::ChaiScript&);
	}
}

#endif // !_Cad_Scripts_Header
