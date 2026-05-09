#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class GeomType>
inline const std::shared_ptr<typename tnbLib::Mesh_SizeMapControl<GeomType>::backMeshType>& 
tnbLib::Mesh_SizeMapControl<GeomType>::BackgroundMesh() const
{
	CheckDone((*this));
	return theBackground_;
}

template<class GeomType>
inline Standard_Boolean 
tnbLib::Mesh_SizeMapControl<GeomType>::HasSizeMap(const word & theName)
{
	auto iter = theBoundaries_.find(theName);
	if (iter IS_EQUAL theBoundaries_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

namespace tnbLib
{

	template<class GeomType>
	inline void Mesh_SizeMapControl<GeomType>::Import
	(
		const word & theName,
		const std::shared_ptr<sizeMapTool>& theSizeMap
	)
	{
		auto paired = std::make_pair(theName, theSizeMap);
		auto insert = theBoundaries_.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data!" << endl
				<< abort(FatalError);
		}
	}
}

template<class GeomType>
inline void tnbLib::Mesh_SizeMapControl<GeomType>::Remove(const word & theName)
{
	auto iter = theBoundaries_.find(theName);
	if (iter IS_EQUAL theBoundaries_.end())
	{
		Info << "- the list of size maps:" << endl;
		for (const auto& x : theBoundaries_)
		{
			Info << " - " << x.first << endl;
		}
		FatalErrorIn(FunctionSIG)
			<< "no such a size map has been found." << endl
			<< " - the size map requested: " << theName << endl
			<< abort(FatalError);
	}
	theBoundaries_.erase(iter);
}