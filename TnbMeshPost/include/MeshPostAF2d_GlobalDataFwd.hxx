#pragma once
#ifndef _MeshPostAF2d_GlobalDataFwd_Header
#define _MeshPostAF2d_GlobalDataFwd_Header

namespace tnbLib
{

	// Forward Declarations [9/1/2023 aamir]
	template<class ElementType>
	class Mesh_GlobalData;

	class MeshPostAF2d_Element;

	typedef Mesh_GlobalData<MeshPostAF2d_Element> MeshPostAF2d_GlobalData;
	
}

#endif // !_MeshPostAF2d_GlobalDataFwd_Header
