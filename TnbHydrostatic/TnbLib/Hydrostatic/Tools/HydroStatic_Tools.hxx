#pragma once
#ifndef _HydroStatic_Tools_Header
#define _HydroStatic_Tools_Header

#include <Standard_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	namespace hsLib
	{

		struct xSection
		{
			Standard_Real x;
			Standard_Real value;
		};
	}

	class HydroStatic_Tools
	{

	public:

		static Standard_Real CalcArea(const std::vector<hsLib::xSection>& theQ);
	};
}

#endif // !_HydroStatic_Tools_Header
