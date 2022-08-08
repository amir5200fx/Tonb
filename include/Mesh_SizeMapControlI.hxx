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