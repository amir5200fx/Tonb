#pragma once
#ifndef _Mesh2d_ReferenceValuesFwd_Header
#define _Mesh2d_ReferenceValuesFwd_Header

#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{
	// Forward Declarations [12/11/2021 Amir]

	template<class Box>
	class Mesh_ReferenceValues;

	typedef Mesh_ReferenceValues<Entity2d_Box> Mesh2d_ReferenceValues;
}

#endif // !_Mesh2d_ReferenceValuesFwd_Header
