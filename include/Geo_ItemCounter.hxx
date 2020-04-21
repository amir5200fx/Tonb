#pragma once
#ifndef _Geo_ItemCounter_Header
#define _Geo_ItemCounter_Header

#include <Geo_PriorityList.hxx>

namespace tnbLib
{

	class Geo_ItemCounter
	{

		typedef Geo_PriorityList<Standard_Integer> counterList;

		/*Private Data*/

		Standard_Integer theNbItems_;

		counterList theItems_;


		void ReSize();

	public:

		static const Standard_Integer DEFAULT_SIZE;

		Geo_ItemCounter();

		Standard_Integer RetrieveIndex();

		void ReturnToCounter(const Standard_Integer theIndex);

	};
}

#endif // !_Geo_ItemCounter_Header
