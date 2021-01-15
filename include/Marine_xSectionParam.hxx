#pragma once
#ifndef _Marine_xSectionParam_Header
#define _Marine_xSectionParam_Header

#include <Standard_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	namespace marineLib
	{

		struct xSectionParam
		{
			Standard_Real x;
			Standard_Real value;
		};
	}

	typedef std::vector<marineLib::xSectionParam> xSectParList;
}

#endif // !_Marine_xSectionParam_Header
