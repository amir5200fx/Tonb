#pragma once
#ifndef _Merge2d_QuadMesh_Header
#define _Merge2d_QuadMesh_Header

#include <Entity2d_QuadMesh.hxx>
#include <Merge_StaticData.hxx>

namespace tnbLib
{

	typedef  Merge_StaticData<Entity2d_QuadMesh, Merge_PntAlg_Mean>
		Merge2d_QuadMesh;
}

#endif
