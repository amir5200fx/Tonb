#pragma once
#ifndef _Aft2d_GlobalDataSurfaceFwd_Header
#define _Aft2d_GlobalDataSurfaceFwd_Header

#include <Aft2d_ElementSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/9/2022 Amir]
	template<class ElementType> 
	class Mesh_GlobalData;

	typedef Mesh_GlobalData<Aft2d_ElementSurface> Aft2d_GlobalDataSurface;
}

#endif // !_Aft2d_GlobalDataSurfaceFwd_Header
