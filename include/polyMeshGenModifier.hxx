#pragma once
#ifndef _polyMeshGenModifier_Header
#define _polyMeshGenModifier_Header

#include <polyMeshGen.hxx>
#include <boolList.hxx>
#include <VRWGraph.hxx>
#include <demandDrivenData.hxx>

namespace tnbLib
{

	// Forward declarations
	class VRWGraphList;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class polyMeshGenModifier
	{
		// Private data
			//- reference to the mesh
		polyMeshGen& mesh_;

		//- helper data for adding cells
		VRWGraph* pointFacesPtr_;

		// Private member functions
			//- calculate and return point faces
		inline void calculatePointFaces()
		{
			const faceListPMG& faces = mesh_.faces();

			pointFacesPtr_ = new VRWGraph();
			VRWGraph& pointFaces = *pointFacesPtr_;

			pointFaces.reverseAddressing(mesh_.points().size(), faces);
		};

		//- re-order positions of processor boundary faces
		//- they should comea immediately after the internal faces
		void reorderProcBoundaryFaces();

	protected:

		VRWGraph& pointFaces()
		{
			if (!pointFacesPtr_)
				calculatePointFaces();

			return *pointFacesPtr_;
		};

	public:

		// Constructors
			//- Construct from the reference to the mesh
		polyMeshGenModifier(polyMeshGen& mesh)
			:
			mesh_(mesh),
			pointFacesPtr_(NULL)
		{
			//mesh_.clearOut();
		};

		// Destructor
		~polyMeshGenModifier()
		{
			this->clearOut();
		};

		// Member functions
			//- access to mesh points
		inline pointFieldPMG& pointsAccess()
		{
			return mesh_.points_;
		};

		//- access to mesh faces
		inline faceListPMG& facesAccess()
		{
			return mesh_.faces_;
		};

		//- access to cells
		inline cellListPMG& cellsAccess()
		{
			return mesh_.cells_;
		};

		//- access to processor boundary data
		inline PtrList<processorBoundaryPatch>& procBoundariesAccess()
		{
			return mesh_.procBoundaries_;
		}

		//- access to boundary data
		inline PtrList<boundaryPatch>& boundariesAccess()
		{
			return mesh_.boundaries_;
		}

		//- functions which change the mesh
		//- reorder boundary faces
		void reorderBoundaryFaces();

		//- remove unused vertices
		void removeUnusedVertices();

		//- remove faces
		void removeFaces(const boolList& removeFace);

		//- remove duplicate faces from the mesh
		void removeDuplicateFaces();

		//- remove cells
		void removeCells
		(
			const boolList& removeCell,
			const bool removeProcFaces = true
		);

		//- add cells (vertices must be added)
		void addCells(const LongList<faceList>& cellFaces);
		void addCells(const VRWGraphList& cellFaces);
		void addCell(const faceList& cellFaces);

		//- replace the boundary with new boundary faces
		void replaceBoundary
		(
			const wordList& patchNames,
			const VRWGraph& boundaryFaces,
			const labelLongList& faceOwners,
			const labelLongList& facePatches
		);

		//- add additional faces into processor patches
		void addProcessorFaces
		(
			const VRWGraph& procFaces,
			const labelLongList& facePatches
		);

		//- add new processor patch and return its label
		label addProcessorPatch(const label otherProcLabel);

		//- remove empty processor patch
		bool removeEmptyProcessorPatches();

		//- add buffer cells needed for exporting the mesh in the format
		//- required by some solvers
		void addBufferCells();

		//- zip up topologically open cells
		void zipUpCells();

		//- reorder the cells and faces to reduce the matrix bandwidth
		void renumberMesh();

		//- clear out unnecessary data (pointFacesPtr_);
		inline void clearOut()
		{
			deleteDemandDrivenData(pointFacesPtr_);
		}

		//- clear out all allocated data
		inline void clearAll()
		{
			clearOut();
			mesh_.clearOut();
		}
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyMeshGenModifier_Header
