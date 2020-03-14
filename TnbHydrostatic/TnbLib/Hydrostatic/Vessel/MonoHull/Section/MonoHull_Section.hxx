#pragma once
#ifndef _MonoHull_Section_Header
#define _MonoHull_Section_Header

#include <HsEntity_Section.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HsSection_Dry;
	class HsSection_WaterLine;
	class HsSection_UnderWater;

	class MonoHull_Section
		: public HsEntity_Section
	{

		/*Private Data*/

		

	public:

		MonoHull_Section();

		MonoHull_Section(const Standard_Integer theIndex);

		MonoHull_Section(const Standard_Integer theIndex, const word &theName);

		
	};
}

#endif // !_MonoHull_Section_Header
