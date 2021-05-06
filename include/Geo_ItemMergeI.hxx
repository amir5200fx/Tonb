#pragma once
#include <Merge2d_Pnt.hxx>
#include <Merge3d_Pnt.hxx>
template<class T, class Point>
inline std::vector<Point> 
tnbLib::Geo_ItemMerge<T, Point>::GetCoordinates() const
{
	std::vector<Point> points;
	points.reserve(theItems_.size());
	for (const auto& x : theItems_)
	{
		auto pt = theCoordinateFun_(x);
		points.push_back(std::move(pt));
	}
	return std::move(points);
}

template<class T, class Point>
inline void tnbLib::Geo_ItemMerge<T, Point>::Perform()
{
	const auto points = GetCoordinates();

	Merge_Pnt<Point, Stl_Vector, Merge_PntAlg_Mean> mergAlg;
	mergAlg.SetCoords(points);
	mergAlg.Perform();
	Debug_If_Condition_Message(NOT mergAlg.IsDone(), "the algorithm is not performed!");

	auto indices = mergAlg.CompactIndices();
	theCompact_.reserve(indices.size());

	for (size_t i = 1; i <= indices.size() - 1; i++)
	{
		if (indices[i] IS_EQUAL i)
		{
			theCompact_.push_back(theItems_[Index_Of(indices[i])]);
		}
	}
}