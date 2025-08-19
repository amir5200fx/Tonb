#pragma once
#ifndef _Aft3d_GlobalDataFwd_Header
#define _Aft3d_GlobalDataFwd_Header

#include <Aft3d_ElementFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/14/2022 Payvand]

	template<class ElementType> class Mesh_GlobalData;

	typedef Mesh_GlobalData<Aft3d_Element> Aft3d_GlobalData;
}

#endif // !_Aft3d_GlobalDataFwd_Header
