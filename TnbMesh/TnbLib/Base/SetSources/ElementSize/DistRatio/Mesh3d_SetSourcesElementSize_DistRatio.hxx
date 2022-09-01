#pragma once
#ifndef _Mesh3d_SetSourcesElementSize_DistRatio_Header
#define _Mesh3d_SetSourcesElementSize_DistRatio_Header

#include <Mesh3d_SetSourcesElementSize.hxx>

namespace tnbLib
{

	class Mesh3d_SetSourcesElementSize_DistRatio
		: public Mesh3d_SetSourcesElementSize
	{

		/*Private Data*/

	public:

		// default constructor [8/18/2022 Amir]

		Mesh3d_SetSourcesElementSize_DistRatio()
		{}


		// constructors [8/18/2022 Amir]


		// public functions and operators [8/18/2022 Amir]

		TnbMesh_EXPORT Standard_Real 
			CalcElementSize
			(
				const std::shared_ptr<Mesh3d_SizeMapTool>& theSizeMap,
				const Standard_Real theRadius, 
				const Pnt3d& theCoord,
				const Pnt3d& theSource
			) const override;

		static TnbMesh_EXPORT Standard_Real 
			CalcElementSize
			(
				const Standard_Real theBase,
				const Standard_Real theTarget, 
				const Standard_Real theRadius,
				const Pnt3d& theSource,
				const Pnt3d& theCoord
			);
	};
}

#endif // !_Mesh3d_SetSourcesElementSize_DistRatio_Header
