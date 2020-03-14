#pragma once
#ifndef _meshOctreeSlot_Header
#define _meshOctreeSlot_Header

#include <VRWGraph.hxx>
#include <FRWGraph.hxx>
#include <meshOctreeCube.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Struct meshOctreeSlot Declaration
	\*---------------------------------------------------------------------------*/

	class meshOctreeSlot
	{
	public:

		// Public data
			//- List of octree cubes
		LongList<meshOctreeCube> cubes_;

		//- Pointers to child cubes
		FRWGraph<meshOctreeCube*, 8> childCubes_;

		//- surface triangles contained in an octree cube
		VRWGraph containedTriangles_;

		//- feature edges contained in an octree cube
		VRWGraph containedEdges_;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_meshOctreeSlot_Header
