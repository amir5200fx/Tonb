#pragma once
#ifndef _VoyageMesh_GlobalDataFwd_Header
#define _VoyageMesh_GlobalDataFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	template<class ElementType>
	class Mesh_GlobalData;

	class VoyageMesh_Element;

	typedef Mesh_GlobalData<VoyageMesh_Element> VoyageMesh_GlobalData;
}

#endif // !_VoyageMesh_GlobalDataFwd_Header
