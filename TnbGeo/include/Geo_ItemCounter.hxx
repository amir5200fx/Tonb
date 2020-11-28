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

		friend boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & theNbItems_;
			ar & theItems_;
		}

		//TNB_SERIALIZATION(TnbGeo_EXPORT);

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

		TnbGeo_EXPORT void ReSize();

	public:

		static TnbGeo_EXPORT const Standard_Integer DEFAULT_SIZE;

		TnbGeo_EXPORT Geo_ItemCounter();

		TnbGeo_EXPORT Standard_Integer RetrieveIndex();

		TnbGeo_EXPORT void ReturnToCounter(const Standard_Integer theIndex);

	};
}

#endif // !_Geo_ItemCounter_Header
