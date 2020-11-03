#pragma once
#ifndef _Geo_ItemCounter_Header
#define _Geo_ItemCounter_Header

#include <Global_Serialization.hxx>
#include <Geo_PriorityList.hxx>
#include <Geo_Module.hxx>

namespace tnbLib
{

	class Geo_ItemCounter
	{

		typedef Geo_PriorityList<Standard_Integer> counterList;

		/*Private Data*/

		Standard_Integer theNbItems_;

		counterList theItems_;


		/*private functions and operators*/
		DECLARE_SAVE_LOAD_HEADER(TnbGeo_EXPORT);

		auto NbItems() const
		{
			return theNbItems_;
		}

		auto& ChangeNbItems()
		{
			return theNbItems_;
		}

		const auto& Items() const
		{
			return theItems_;
		}

		auto& ChangeItems()
		{
			return theItems_;
		}

		void ReSize();

	public:

		static const Standard_Integer DEFAULT_SIZE;

		Geo_ItemCounter();

		Standard_Integer RetrieveIndex();

		void ReturnToCounter(const Standard_Integer theIndex);

	};
}

#endif // !_Geo_ItemCounter_Header
