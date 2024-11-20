#pragma once
#include <Geo_BoxTools.hxx>
#include <Global_Real.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class BackMeshData>
	inline Standard_Real Mesh_UnionSizeMap<BackMeshData>::TreeObject::ElementSize(const Point & coord) const
	{
		Standard_Real MinSize = RealLast();
		for (const auto& x : SizeMaps())
		{
			Debug_Null_Pointer(x);
			auto size = x->InterpolateAt(coord);
			if (size < MinSize)
				MinSize = size;
		}
		return MinSize;
	}
}

template<class BackMeshData>
inline tnbLib::Mesh_UnionSizeMap<BackMeshData>::Mesh_UnionSizeMap()
	: theTolerance_(DEFAULT_TOLERANCE)
	, theMinSubdivision_(DEFAULT_MIN_SUBDIVISION)
	, theMaxSubdivision_(DEFAULT_MAX_SUBDIVISION)
{
	//  [5/30/2021 Amir]
}

template<class BackMeshData>
inline void tnbLib::Mesh_UnionSizeMap<BackMeshData>::AddSizeMap(const std::shared_ptr<BackMeshData>& theMap)
{
	theSizeMaps_.push_back(theMap);
}

template<class BackMeshData>
inline void tnbLib::Mesh_UnionSizeMap<BackMeshData>::SetTolerance(const Standard_Real x)
{
	theTolerance_ = x;
}

template<class BackMeshData>
inline void tnbLib::Mesh_UnionSizeMap<BackMeshData>::SetMinSubdivision(const Standard_Integer n)
{
	theMinSubdivision_ = n;
}

template<class BackMeshData>
inline void tnbLib::Mesh_UnionSizeMap<BackMeshData>::SetMaxSubdivision(const Standard_Integer n)
{
	theMaxSubdivision_ = n;
}

template<class BackMeshData>
inline tnbLib::Entity_Box<typename tnbLib::Mesh_UnionSizeMap<BackMeshData>::Point> 
tnbLib::Mesh_UnionSizeMap<BackMeshData>::CalcBoundingBox
(
	const std::list<std::shared_ptr<BackMeshData>>& theMaps
)
{
	if (theMaps.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
	auto iter = theMaps.begin();
	auto box = (*iter)->BoundingBox();

	iter++;
	while (iter NOT_EQUAL theMaps.end())
	{
		const auto& b = (*iter)->BoundingBox();
		box = Geo_BoxTools::Union(box, b);

		iter++;
	}
	return std::move(box);
}