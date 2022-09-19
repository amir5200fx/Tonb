#pragma once
#ifndef _MeshPost2d_LaplacianSmoothingSurface_AdjEdges_Header
#define _MeshPost2d_LaplacianSmoothingSurface_AdjEdges_Header

#include <MeshPost2d_LaplacianSmoothingSurface_AvgFun.hxx>

namespace tnbLib
{

	class MeshPost2d_LaplacianSmoothingSurface_AdjEdges
		: public MeshPost2d_LaplacianSmoothingSurface_AvgFun
	{

		/*Private Data*/

	public:

		// default constructor [9/19/2022 Amir]

		MeshPost2d_LaplacianSmoothingSurface_AdjEdges()
		{}

		// constructors [9/19/2022 Amir]


		// public functions and operators [9/19/2022 Amir]

		TnbMeshPost_EXPORT Pnt2d CalcAverage(const std::shared_ptr<Aft2d_NodeSurface>&) const override;
	};
}

#endif // !_MeshPost2d_LaplacianSmoothingSurface_AdjEdges_Header
