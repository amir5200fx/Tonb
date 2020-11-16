#pragma once
#ifndef _SectPx_Offset_Header
#define _SectPx_Offset_Header

#include <Standard_TypeDef.hxx>
#include <SectPx_Module.hxx>

#include <memory>

namespace tnbLib
{

	class SectPx_Offset
	{

		/*Private Data*/

	protected:

		SectPx_Offset()
		{}

	public:

		virtual Standard_Real xCoord() const = 0;

		virtual Standard_Real yCoord() const = 0;


	};
}

#endif // !_SectPx_Offset_Header
