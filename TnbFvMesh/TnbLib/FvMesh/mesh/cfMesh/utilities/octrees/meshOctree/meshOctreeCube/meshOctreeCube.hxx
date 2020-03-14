#pragma once
#ifndef _meshOctreeCube_Header
#define _meshOctreeCube_Header

#include <DynList.hxx>
#include <LongList.hxx>
#include <boolList.hxx>
#include <meshOctreeCubeBasic.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class Ostream;
	class triSurf;
	class VRWGraph;
	class meshOctreeSlot;

	/*---------------------------------------------------------------------------*\
						Class meshOctreeCube Declaration
	\*---------------------------------------------------------------------------*/

	class meshOctreeCube
		: public meshOctreeCubeBasic
	{
		// Private data
			//- pointer the slot containing this cube
		meshOctreeSlot* activeSlotPtr_;

		//- pointer to the first child element
		meshOctreeCube** subCubesPtr_;

		//- position of the cube in the list of leaves
		mutable label cubeLabel_;

		//- label of the row which contains elements contained in the cube
		label containedElementsLabel_;

		//- labels of contained surface edges
		label containedEdgesLabel_;

		// Static data
			//- this data is needed to map the the current refinement pattern
			//- to the Hilbert space-filling curve in order to reduce the bandwidth
			//- in the list of leaves. The procedure is performed using the table
			//- published in (Campbell etal: Dynamic Octree Load Balancing Using
			//- Space-Filling Curves) which is adjusted to the current ref pattern
		static const label hOrder_[24][8];

		//- orientation of the Hilbert curve in the refined cubes of a cube
		//- with the ordering in the above table
		static const label hOrient_[24][8];

		// Private member functions
			//- find edges contained in the cube
		void findContainedEdges
		(
			const triSurf&,
			const boundBox&
		);

		//- store data which is contained in the child cube
		//- this is needed for parallel coarsening of the octree
		//inline void reclaimDataFromChild(const label scI);

		//- Disallow copy construct from meshOctreeCubeBasic
		meshOctreeCube(const meshOctreeCubeBasic&);

	public:

		// Constructors

			//- Default constructor
		inline meshOctreeCube();

		//- Copy construct
		inline meshOctreeCube(const meshOctreeCube&);

		//- Construct from coordinates
		meshOctreeCube(const meshOctreeCubeCoordinates&);

		//- Construct from coordinates and the number of surface triangles
		//- this constructor is used for the initial cube, only
		meshOctreeCube
		(
			const meshOctreeCubeCoordinates& cc,
			const label nElmts,
			meshOctreeSlot* slotPtr
		);

		// Destructor

		~meshOctreeCube();

		// Member Functions

			//- refine cube in two directions, it is used for generating quadtrees
		void refineCube2D
		(
			const triSurf&,
			const boundBox&,
			meshOctreeSlot* slotPtr = NULL
		);

		//- subdivide the octree cube
		void refineCube
		(
			const triSurf&,
			const boundBox&,
			meshOctreeSlot* slotPtr = NULL
		);

		//- create missing child cubes and refine them until the required
		//- cube is reached (this function is used for parallel octree creation)
		void refineMissingCube
		(
			const triSurf&,
			const boundBox&,
			const label scI,
			meshOctreeSlot* slotPtr = NULL
		);

		//- create missing child cubes and refine them until the required
		//- cube is reached (this function is used for parallel octree creation)
		//- contained elements and edges are provided as argument
		void refineMissingCube
		(
			const label scI,
			const label elementsRowI = -1,
			const label edgesRowI = -1,
			meshOctreeSlot* slotPtr = NULL
		);

		//- return the pointer to the slot containing the cube
		inline const meshOctreeSlot* slotPtr() const;

		//- position of the cube in the list of leaves
		inline label cubeLabel() const;

		//- check if the cube is a leaf
		inline bool isLeaf() const;

		//- return a pointer to a child cubes at given position
		inline meshOctreeCube* subCube(const label) const;

		//- return the pointers to the sons
		FixedList<meshOctreeCube*, 8> subCubes() const;

		//- check if this box has some contained triangles
		bool hasContainedTriangles
		(
			const triSurf&,
			const boundBox&,
			const VRWGraph& containedElements
		) const;

		//- return true if the box contains some triangles
		inline bool hasContainedElements() const;

		//- returns the list of contained surface elements
		//- this list is only allocated for cubes containing elements
		inline label containedElements() const;

		//- returns true if the box contains some edges
		inline bool hasContainedEdges() const;

		//- returns the list of contained surface edges
		//- this list is only allocated for cubes containing edges
		inline label containedEdges() const;

		// Recursive functions
			//- leaves contained in the given box
		void leavesInBox
		(
			const boundBox& rootBox,
			const boundBox& searchingBox,
			DynList<const meshOctreeCube*, 256>&
		) const;

		//- find leaves within a sphere
		void leavesInSphere
		(
			const boundBox& rootBox,
			const point&,
			const scalar,
			DynList<label>&
		) const;

		//- mark leaves within a sphere
		void markLeavesInSphere
		(
			const boundBox& rootBox,
			const point&,
			const scalar,
			labelList&,
			bool&
		) const;

		//- find leaves for a given cube
		void findLeaves
		(
			LongList<meshOctreeCube*>& leaves
		) const;

		//- find coordinates of cubes which are located on other processors
		void findCoordinatesOfMissingCubes
		(
			LongList<meshOctreeCubeCoordinates>& coordinates
		) const;

		//- count number of originating from this cube
		void countChildCubes(label& nCubes) const;

		//- delete boxes which are not local to the given processor
		bool purgeProcessorCubes(const short procNo);

		// Member operators

			//- assignment
		inline void operator=(const meshOctreeCube&);
		friend Ostream& operator<<(Ostream&, const meshOctreeCube&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <meshOctreeCubeI.hxx>

#endif // !_meshOctreeCube_Header
