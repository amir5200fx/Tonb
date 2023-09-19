#pragma once
#ifndef _Merge2d_Triangulation_Header
#define _Merge2d_Triangulation_Header

#include <Merge_StaticData.hxx>
#include <Entity2d_Triangulation.hxx>

namespace tnbLib
{
	
	typedef Merge_StaticData<Entity2d_Triangulation, Merge_PntAlg_Mean>
		Merge2d_Triangulation;
}

#endif
