#pragma once
#ifndef _Aft2d_GlobalDataFwd_Header
#define _Aft2d_GlobalDataFwd_Header

#include <Aft2d_ElementFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations

	template<class ElementType> class Mesh_GlobalData;

	typedef Mesh_GlobalData<Aft2d_Element> Aft2d_GlobalData;
}

#endif // !_Aft2d_GlobalDataFwd_Header
