#pragma once
#ifndef _Geo_ItemMerge_Header
#define _Geo_ItemMerge_Header

#include <Global_Done.hxx>

#include <vector>

namespace tnbLib
{

	template<class T, class Point>
	class Geo_ItemMerge
		: public Global_Done
	{

		/*Private Data*/

		const std::vector<T>& theItems_;
		Point (*theCoordinateFun_)(const T&);

		std::vector<T> theCompact_;

		//- private functions and operators

		std::vector<Point> GetCoordinates() const;

	public:

		Geo_ItemMerge(const std::vector<T>& theItems, Point(*theCoordinateFun)(const T&))
			: theItems_(theItems)
			, theCoordinateFun_(theCoordinateFun)
		{}

		const auto& CompactItems() const
		{
			return theCompact_;
		}

		void Perform();
	};
}

#include <Geo_ItemMergeI.hxx>

#endif // !_Geo_ItemMerge_Header
