#pragma once
#ifndef _IndexedItem_Header
#define _IndexedItem_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>

namespace tnbLib
{
	template<class T>
	class IndexedItem
	{

		/*Private Data*/

		Standard_Integer theIndex_;

		T theItem_;


		/*private functions and operators*/

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theIndex_;
			ar & theItem_;
		}

	public:

		typedef typename T::ptType ptType;

		IndexedItem()
		{}

		IndexedItem(const Standard_Integer theIndex, const T& theItem)
			: theIndex_(theIndex)
			, theItem_(theItem)
		{}

		IndexedItem(const Standard_Integer theIndex, T&& theItem)
			: theIndex_(theIndex)
			, theItem_(std::move(theItem))
		{}

		Standard_Integer Index() const
		{
			return theIndex_;
		}

		const T& Item() const
		{
			return theItem_;
		}

		void SetIndex(const Standard_Integer theIndex)
		{
			theIndex_ = theIndex;
		}

		void SetItem(const T& theItem)
		{
			theItem_ = theItem;
		}

		void SetItem(T&& theItem)
		{
			theItem_ = std::move(theItem);
		}
	};
}

#include <IndexedItemIO.hxx>

#endif // !_IndexedItem_Header
