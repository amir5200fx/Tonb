#pragma once
#ifndef _Merge2d_CmpMesh_Header
#define _Merge2d_CmpMesh_Header

#include <Entity2d_CmpMesh.hxx>
#include <Merge_StaticData.hxx>

namespace tnbLib
{

	typedef Merge_StaticData<Entity2d_CmpMesh, Merge_PntAlg_Mean>
		Merge2d_CmpMesh;
}

#endif