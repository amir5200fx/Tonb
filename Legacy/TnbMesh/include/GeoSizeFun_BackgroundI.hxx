#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

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