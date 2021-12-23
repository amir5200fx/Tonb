#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class BackMeshData>
	GeoSizeFun_Background<BackMeshData>::GeoSizeFun_Background
	(
		const Standard_Integer theIndex,
		const word & theName,
		const std::shared_ptr<BackMeshData>& theBackMesh
	)
		: GeoSizeFun_nonUniform<typename BackMeshData::ptType>(theIndex, theName)
		, theBackMesh_(theBackMesh)
	{
	}

	template<class BackMeshData>
	Standard_Real
		GeoSizeFun_Background<BackMeshData>::Value
		(
			const Point & theCoord
		) const
	{
		Debug_Null_Pointer(theBackMesh_);

		return theBackMesh_->InterpolateAt(theCoord);
	}
}