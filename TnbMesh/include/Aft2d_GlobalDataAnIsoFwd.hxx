#pragma once
#ifndef _Aft2d_GlobalDataAnIsoFwd_Header
#define _Aft2d_GlobalDataAnIsoFwd_Header

#include <Aft2d_ElementAnIsoFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class ElementType> 
	class Mesh_GlobalData;

	typedef Mesh_GlobalData<Aft2d_ElementAnIso> Aft2d_GlobalDataAnIso;
}

#endif // !_Aft2d_GlobalDataAnIsoFwd_Header
