#pragma once
#ifndef _ISC08_Table_Header
#define _ISC08_Table_Header

#include <Standard_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	struct ISC08_Table
	{
		std::vector<Standard_Real> Spans;
		std::vector<Standard_Real> Values;
	};

}

#include <ISC08_Tables.hxx>

#endif // !_ISC08_Table_Header
