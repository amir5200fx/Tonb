#pragma once
#ifndef _Mesh3d_ReferenceValuesFwd_Header
#define _Mesh3d_ReferenceValuesFwd_Header

#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/11/2021 Amir]

	template<class Box>
	class Mesh_ReferenceValues;

	typedef Mesh_ReferenceValues<Entity3d_Box> Mesh3d_ReferenceValues;
}

#endif // !_Mesh3d_ReferenceValuesFwd_Header
