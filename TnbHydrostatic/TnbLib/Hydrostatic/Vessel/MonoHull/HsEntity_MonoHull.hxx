#pragma once
#ifndef _HsEntity_MonoHull_Header
#define _HsEntity_MonoHull_Header

#include <HsEntity_Vessel.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class MonoHull_Section;

	class HsEntity_MonoHull
		: public HsEntity_Vessel
	{

		/*Private Data*/


	public:

		HsEntity_MonoHull();

		HsEntity_MonoHull(const Standard_Integer theIndex);

		HsEntity_MonoHull(const Standard_Integer theIndex, const word &theName);

	public:


		

		

	};
}

#endif // !_HsEntity_MonoHull_Header
