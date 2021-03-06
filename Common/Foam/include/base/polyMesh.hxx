#pragma once
#ifndef _polyMesh_Header
#define _polyMesh_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::polyMesh

Description
	Mesh consisting of general polyhedral cells.

SourceFiles
	polyMesh.C
	polyMeshInitMesh.C
	polyMeshClear.C
	polyMeshFromShapeMesh.C
	polyMeshIO.C
	polyMeshUpdate.C
	polyMeshCheck.C

\*---------------------------------------------------------------------------*/

#include <objectRegistry.hxx>
#include <primitiveMesh.hxx>
#include <pointField.hxx>
#include <faceList.hxx>
#include <cellList.hxx>
#include <cellShapeList.hxx>
#include <pointIOField.hxx>
#include <faceIOList.hxx>
#include <labelIOList.hxx>
#include <polyBoundaryMesh.hxx>
#include <boundBox.hxx>
#include <pointZoneMesh.hxx>
#include <faceZoneMesh.hxx>
#include <cellZoneMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class globalMeshData;
	class mapPolyMesh;
	class polyMeshTetDecomposition;
	class treeDataCell;
	template<class Type> class indexedOctree;

	/*---------------------------------------------------------------------------*\
							  Class polyMesh Declaration
	\*---------------------------------------------------------------------------*/

	class polyMesh
		:
		public objectRegistry,
		public primitiveMesh
	{

	public:

		// Public data types

			//- Enumeration defining the state of the mesh after a read update.
			//  Used for post-processing applications, where the mesh
			//  needs to update based on the files written in time
			//  directories
		enum readUpdateState
		{
			UNCHANGED,
			POINTS_MOVED,
			TOPO_CHANGE,
			TOPO_PATCH_CHANGE
		};

		//- Enumeration defining the decomposition of the cell for
		//  inside/outside test
		enum cellDecomposition
		{
			FACE_PLANES,      //- Faces considered as planes

			FACE_CENTRE_TRIS, //- Faces decomposed into triangles
							  //  using face-centre

							  FACE_DIAG_TRIS,   //- Faces decomposed into triangles diagonally

							  CELL_TETS         //- Cell decomposed into tets
		};


	private:

		// Permanent data

			// Primitive mesh data

				//- Points
		pointIOField points_;

		//- Faces
		faceCompactIOList faces_;

		//- Face owner
		labelIOList owner_;

		//- Face neighbour
		labelIOList neighbour_;

		//- Have the primitives been cleared
		bool clearedPrimitives_;


		//- Boundary mesh
		mutable polyBoundaryMesh boundary_;

		//- Mesh bounding-box.
		//  Created from points on construction, updated when the mesh moves
		boundBox bounds_;

		//- Communicator used for parallel communication
		label comm_;

		//- Vector of non-constrained directions in mesh
		//  defined according to the presence of empty and wedge patches
		mutable Vector<label> geometricD_;

		//- Vector of valid directions in mesh
		//  defined according to the presence of empty patches
		mutable Vector<label> solutionD_;

		//- Base point for face decomposition into tets
		mutable autoPtr<labelIOList> tetBasePtIsPtr_;

		//- Search tree to allow spatial cell searching
		mutable autoPtr<indexedOctree<treeDataCell>> cellTreePtr_;


		// Zoning information

			//- Point zones
		pointZoneMesh pointZones_;

		//- Face zones
		faceZoneMesh faceZones_;

		//- Cell zones
		cellZoneMesh cellZones_;


		//- Parallel info
		mutable autoPtr<globalMeshData> globalMeshDataPtr_;


		// Mesh motion related data

			//- Is the mesh moving
		bool moving_;

		//- Is the mesh topology changing
		bool topoChanging_;

		//- Current time index for mesh motion
		mutable label curMotionTimeIndex_;

		//- Old points (for the last mesh motion)
		mutable autoPtr<pointField> oldPointsPtr_;

		//- Old cell centres (for the last mesh motion)
		mutable autoPtr<pointField> oldCellCentresPtr_;

		//- Whether or not to store the old cell centres
		mutable bool storeOldCellCentres_;


		// Private Member Functions

			//- Initialise the polyMesh from the primitive data
		FoamBase_EXPORT void initMesh();

		//- Initialise the polyMesh from the given set of cells
		FoamBase_EXPORT void initMesh(cellList& c);

		//- Calculate the valid directions in the mesh from the boundaries
		FoamBase_EXPORT void calcDirections() const;

		//- Calculate the cell shapes from the primitive
		//  polyhedral information
		FoamBase_EXPORT void calcCellShapes() const;

		//- Read and return the tetBasePtIs
		FoamBase_EXPORT autoPtr<labelIOList> readTetBasePtIs() const;


		// Helper functions for constructor from cell shapes

		FoamBase_EXPORT labelListList cellShapePointCells(const cellShapeList&) const;

		FoamBase_EXPORT labelList facePatchFaceCells
		(
			const faceList& patchFaces,
			const labelListList& pointCells,
			const faceListList& cellsFaceShapes,
			const label patchID
		) const;

		FoamBase_EXPORT void setTopology
		(
			const cellShapeList& cellsAsShapes,
			const faceListList& boundaryFaces,
			const wordList& boundaryPatchNames,
			labelList& patchSizes,
			labelList& patchStarts,
			label& defaultPatchStart,
			label& nFaces,
			cellList& cells
		);


		// Geometry checks

			//- Check non-orthogonality
		FoamBase_EXPORT bool checkFaceOrthogonality
		(
			const vectorField& fAreas,
			const vectorField& cellCtrs,
			const bool report,
			const bool detailedReport,
			labelHashSet* setPtr
		) const;

		//- Check face skewness
		FoamBase_EXPORT bool checkFaceSkewness
		(
			const pointField& points,
			const vectorField& fCtrs,
			const vectorField& fAreas,
			const vectorField& cellCtrs,
			const bool report,
			const bool detailedReport,
			labelHashSet* setPtr
		) const;

		FoamBase_EXPORT bool checkEdgeAlignment
		(
			const pointField& p,
			const bool report,
			const Vector<label>& directions,
			labelHashSet* setPtr
		) const;

		FoamBase_EXPORT bool checkCellDeterminant
		(
			const vectorField& faceAreas,
			const bool report,
			labelHashSet* setPtr,
			const Vector<label>& meshD
		) const;

		FoamBase_EXPORT bool checkFaceWeight
		(
			const vectorField& fCtrs,
			const vectorField& fAreas,
			const vectorField& cellCtrs,
			const bool report,
			const scalar minWeight,
			labelHashSet* setPtr
		) const;

		FoamBase_EXPORT bool checkVolRatio
		(
			const scalarField& cellVols,
			const bool report,
			const scalar minRatio,
			labelHashSet* setPtr
		) const;

	public:

		// Public Typedefs

		typedef polyMesh Mesh;
		typedef polyBoundaryMesh BoundaryMesh;


		//- Runtime type information
		//TypeName("polyMesh");
		static const char* typeName_() { return "polyMesh"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };

		//- Return the default region name
		static FoamBase_EXPORT word defaultRegion;

		//- Return the mesh sub-directory name (usually "polyMesh")
		static FoamBase_EXPORT word meshSubDir;


		// Constructors

			//- Construct from IOobject
		FoamBase_EXPORT explicit polyMesh(const IOobject& io);

		//- Move construct from IOobject or from components.
		//  Boundary is added using addPatches() member function
		FoamBase_EXPORT polyMesh
		(
			const IOobject& io,
			pointField&& points,
			faceList&& faces,
			labelList&& owner,
			labelList&& neighbour,
			const bool syncPar = true
		);

		//- Move construct without boundary with cells rather than
		//  owner/neighbour.
		//  Boundary is added using addPatches() member function
		FoamBase_EXPORT polyMesh
		(
			const IOobject& io,
			pointField&& points,
			faceList&& faces,
			cellList&& cells,
			const bool syncPar = true
		);

		//- Move construct from cell shapes
		FoamBase_EXPORT polyMesh
		(
			const IOobject& io,
			pointField&& points,
			const cellShapeList& shapes,
			const faceListList& boundaryFaces,
			const wordList& boundaryPatchNames,
			const wordList& boundaryPatchTypes,
			const word& defaultBoundaryPatchName,
			const word& defaultBoundaryPatchType,
			const wordList& boundaryPatchPhysicalTypes,
			const bool syncPar = true
		);

		//- Move construct from cell shapes with patch information in dictionary
		//  format.
		FoamBase_EXPORT polyMesh
		(
			const IOobject& io,
			pointField&& points,
			const cellShapeList& shapes,
			const faceListList& boundaryFaces,
			const wordList& boundaryPatchNames,
			const PtrList<dictionary>& boundaryDicts,
			const word& defaultBoundaryPatchName,
			const word& defaultBoundaryPatchType,
			const bool syncPar = true
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT polyMesh(const polyMesh&);


		//- Destructor
		FoamBase_EXPORT virtual ~polyMesh();


		// Member Functions

			// Database

				//- Override the objectRegistry dbDir for a single-region case
		FoamBase_EXPORT virtual const fileName& dbDir() const;

		//- Return the local mesh directory (dbDir()/meshSubDir)
		FoamBase_EXPORT fileName meshDir() const;

		//- Return the current instance directory for points
		//  Used in the consruction of gemometric mesh data dependent
		//  on points
		FoamBase_EXPORT const fileName& pointsInstance() const;

		//- Return the current instance directory for faces
		FoamBase_EXPORT const fileName& facesInstance() const;

		//- Set the instance for mesh files
		FoamBase_EXPORT void setInstance(const fileName&);


		// Access

			//- Return raw points
		FoamBase_EXPORT virtual const pointField& points() const;

		//- Return true if io is up-to-date with points
		FoamBase_EXPORT virtual bool upToDatePoints(const regIOobject& io) const;

		//- Set io to be up-to-date with points
		FoamBase_EXPORT virtual void setUpToDatePoints(regIOobject& io) const;

		//- Return raw faces
		FoamBase_EXPORT virtual const faceList& faces() const;

		//- Return face owner
		FoamBase_EXPORT virtual const labelList& faceOwner() const;

		//- Return face neighbour
		FoamBase_EXPORT virtual const labelList& faceNeighbour() const;

		//- Return old points for mesh motion
		FoamBase_EXPORT virtual const pointField& oldPoints() const;

		//- Return old points for mesh motion
		FoamBase_EXPORT virtual const pointField& oldCellCentres() const;

		//- Return IO object for points0
		static FoamBase_EXPORT IOobject points0IO(const polyMesh& mesh);

		//- Return boundary mesh
		const polyBoundaryMesh& boundaryMesh() const
		{
			return boundary_;
		}

		//- Return mesh bounding box
		const boundBox& bounds() const
		{
			return bounds_;
		}

		//- Return the vector of geometric directions in mesh.
		//  Defined according to the presence of empty and wedge patches.
		//  1 indicates unconstrained direction and -1 a constrained
		//  direction.
		FoamBase_EXPORT const Vector<label>& geometricD() const;

		//- Return the number of valid geometric dimensions in the mesh
		FoamBase_EXPORT label nGeometricD() const;

		//- Return the vector of solved-for directions in mesh.
		//  Differs from geometricD in that it includes for wedge cases
		//  the circumferential direction in case of swirl.
		//  1 indicates valid direction and -1 an invalid direction.
		FoamBase_EXPORT const Vector<label>& solutionD() const;

		//- Return the number of valid solved-for dimensions in the mesh
		FoamBase_EXPORT label nSolutionD() const;

		//- Return the tetBasePtIs
		FoamBase_EXPORT const labelIOList& tetBasePtIs() const;

		//- Return the cell search tree
		FoamBase_EXPORT const indexedOctree<treeDataCell>& cellTree() const;

		//- Return point zone mesh
		const pointZoneMesh& pointZones() const
		{
			return pointZones_;
		}

		//- Return face zone mesh
		const faceZoneMesh& faceZones() const
		{
			return faceZones_;
		}

		//- Return cell zone mesh
		const cellZoneMesh& cellZones() const
		{
			return cellZones_;
		}

		//- Return parallel info
		FoamBase_EXPORT const globalMeshData& globalData() const;

		//- Return communicator used for parallel communication
		FoamBase_EXPORT label comm() const;

		//- Return communicator used for parallel communication
		FoamBase_EXPORT label& comm();

		//- Return the object registry
		const objectRegistry& thisDb() const
		{
			return *this;
		}


		// Mesh motion

			//- Is mesh dynamic
		virtual bool dynamic() const
		{
			return false;
		}

		//- Is mesh moving
		bool moving() const
		{
			return moving_;
		}

		//- Set the mesh to be moving
		bool moving(const bool m)
		{
			bool m0 = moving_;
			moving_ = m;
			return m0;
		}

		//- Is mesh topology changing
		bool topoChanging() const
		{
			return topoChanging_;
		}

		//- Set the mesh topology to be changing
		bool topoChanging(const bool c)
		{
			bool c0 = topoChanging_;
			topoChanging_ = c;
			return c0;
		}

		//- Is mesh changing (topology changing and/or moving)
		bool changing() const
		{
			return moving() || topoChanging();
		}

		//- Move points, returns volumes swept by faces in motion
		FoamBase_EXPORT virtual tmp<scalarField> movePoints(const pointField&);

		//- Reset motion
		FoamBase_EXPORT void resetMotion() const;


		// Topological change

			//- Return non-const access to the pointZones
		pointZoneMesh& pointZones()
		{
			return pointZones_;
		}

		//- Return non-const access to the faceZones
		faceZoneMesh& faceZones()
		{
			return faceZones_;
		}

		//- Return non-const access to the cellZones
		cellZoneMesh& cellZones()
		{
			return cellZones_;
		}

		//- Add boundary patches
		FoamBase_EXPORT void addPatches
		(
			const List<polyPatch*>&,
			const bool validBoundary = true
		);

		//- Add mesh zones
		FoamBase_EXPORT void addZones
		(
			const List<pointZone*>& pz,
			const List<faceZone*>& fz,
			const List<cellZone*>& cz
		);

		//- Add/insert single patch. If validBoundary the new situation
		//  is consistent across processors.
		FoamBase_EXPORT virtual void addPatch
		(
			const label insertPatchi,
			const polyPatch& patch,
			const dictionary& patchFieldDict,
			const word& defaultPatchFieldType,
			const bool validBoundary
		);

		//- Reorder and trim existing patches. If validBoundary the new
		//  situation is consistent across processors
		FoamBase_EXPORT virtual void reorderPatches
		(
			const labelUList& newToOld,
			const bool validBoundary
		);

		//- Update the mesh based on the mesh files saved in
		//  time directories
		FoamBase_EXPORT virtual readUpdateState readUpdate();

		//- Update the mesh corresponding to given map
		FoamBase_EXPORT virtual void updateMesh(const mapPolyMesh& mpm);

		//- Remove boundary patches
		FoamBase_EXPORT void removeBoundary();

		//- Reset mesh primitive data. Assumes all patch info correct
		//  (so does e.g. parallel communication). If not use
		//  validBoundary=false
		FoamBase_EXPORT void resetPrimitives
		(
			pointField&& points,
			faceList&& faces,
			labelList&& owner,
			labelList&& neighbour,
			const labelList& patchSizes,
			const labelList& patchStarts,
			const bool validBoundary = true
		);


		//  Storage management

			//- Clear geometry
		FoamBase_EXPORT void clearGeom();

		//- Clear addressing
		FoamBase_EXPORT void clearAddressing(const bool isMeshUpdate = false);

		//- Clear all geometry and addressing unnecessary for CFD
		FoamBase_EXPORT void clearOut();

		//- Clear primitive data (points, faces and cells)
		FoamBase_EXPORT void clearPrimitives();

		//- Clear tet base points
		FoamBase_EXPORT void clearTetBasePtIs();

		//- Clear cell tree data
		FoamBase_EXPORT void clearCellTree();

		//- Remove all files from mesh instance
		FoamBase_EXPORT void removeFiles(const fileName& instanceDir) const;

		//- Remove all files from mesh instance()
		FoamBase_EXPORT void removeFiles() const;


		// Geometric checks. Selectively override primitiveMesh functionality.

			//- Check non-orthogonality
		FoamBase_EXPORT virtual bool checkFaceOrthogonality
		(
			const bool report = false,
			labelHashSet* setPtr = nullptr
		) const;

		//- Check face skewness
		FoamBase_EXPORT virtual bool checkFaceSkewness
		(
			const bool report = false,
			labelHashSet* setPtr = nullptr
		) const;

		//- Check edge alignment for 1D/2D cases
		FoamBase_EXPORT virtual bool checkEdgeAlignment
		(
			const bool report,
			const Vector<label>& directions,
			labelHashSet* setPtr
		) const;

		FoamBase_EXPORT virtual bool checkCellDeterminant
		(
			const bool report,
			labelHashSet* setPtr
		) const;

		//- Check mesh motion for correctness given motion points
		FoamBase_EXPORT virtual bool checkMeshMotion
		(
			const pointField& newPoints,
			const bool report = false,
			const bool detailedReport = false
		) const;

		//- Check for face weights
		FoamBase_EXPORT virtual bool checkFaceWeight
		(
			const bool report,
			const scalar minWeight = 0.05,
			labelHashSet* setPtr = nullptr
		) const;

		//- Check for neighbouring cell volumes
		FoamBase_EXPORT virtual bool checkVolRatio
		(
			const bool report,
			const scalar minRatio = 0.01,
			labelHashSet* setPtr = nullptr
		) const;


		// Position search functions

			//- Find the cell, tetFacei and tetPti for point p
		FoamBase_EXPORT void findCellFacePt
		(
			const point& p,
			label& celli,
			label& tetFacei,
			label& tetPti
		) const;

		//- Find the tetFacei and tetPti for point p in celli.
		//  tetFacei and tetPtI are set to -1 if not found
		FoamBase_EXPORT void findTetFacePt
		(
			const label celli,
			const point& p,
			label& tetFacei,
			label& tetPti
		) const;

		//- Test if point p is in the celli
		FoamBase_EXPORT bool pointInCell
		(
			const point& p,
			label celli,
			const cellDecomposition = CELL_TETS
		) const;

		//- Find cell enclosing this location and return index
		//  If not found -1 is returned
		FoamBase_EXPORT label findCell
		(
			const point& p,
			const cellDecomposition = CELL_TETS
		) const;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const polyMesh&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_polyMesh_Header
