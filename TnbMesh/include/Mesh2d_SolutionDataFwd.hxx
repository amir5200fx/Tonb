#pragma once
#ifndef _Mesh2d_SolutionDataFwd_Header
#define _Mesh2d_SolutionDataFwd_Header

namespace tnbLib
{

	//- Forward Declarations
	template<class GeomType>
	class Mesh_SolutionData;

	class Cad2d_Plane;

	typedef Mesh_SolutionData<Cad2d_Plane> Mesh2d_SolutionData;
}

#endif // !_Mesh2d_SolutionDataFwd_Header
