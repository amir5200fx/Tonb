#pragma once
#ifndef _primitiveMesh_Header
#define _primitiveMesh_Header

#include <dynamicLabelList.hxx>
#include <edgeList.hxx>
#include <pointField.hxx>
#include <SubField.hxx>
#include <SubList.hxx>
#include <faceList.hxx>
#include <cellList.hxx>
#include <cellShapeList.hxx>
#include <labelList.hxx>
#include <boolList.hxx>
#include <HashSet.hxx>
#include <Map.hxx>
#include <EdgeMap.hxx>
#include <tolerancesSwitch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class primitiveMesh Declaration
	\*---------------------------------------------------------------------------*/

	class primitiveMesh
	{
		// Permanent data

			// Primitive size data

				//- Number of points
		label nPoints_;

		//- Number of edges
		mutable label nEdges_;

		//- Number of internal faces
		label nInternalFaces_;

		//- Number of faces
		label nFaces_;

		//- Number of cells
		label nCells_;


		// Shapes

			//- Cell shapes
		mutable cellShapeList* cellShapesPtr_;

		//- Edges are ordered in upper triangular order
		//  Note: inconsistency with 1.6.x to re-instate
		//  parallelisation of point-based operations
		// HJ, 9/Jul/2010
		mutable edgeList* edgesPtr_;


		// Connectivity

			//- Cell-cells
		mutable labelListList* ccPtr_;

		//- Edge-cells
		mutable labelListList* ecPtr_;

		//- Point-cells
		mutable labelListList* pcPtr_;

		//- Cell-faces
		mutable cellList* cfPtr_;

		//- Edge-faces
		mutable labelListList* efPtr_;

		//- Point-faces
		mutable labelListList* pfPtr_;

		//- Cell-edges
		mutable labelListList* cePtr_;

		//- Face-edges
		mutable labelListList* fePtr_;

		//- Point-edges
		mutable labelListList* pePtr_;

		//- Point-points
		mutable labelListList* ppPtr_;

		//- Cell-points
		mutable labelListList* cpPtr_;


		// On-the-fly edge addresing storage

			//- Temporary storage for addressing.
		mutable dynamicLabelList labels_;

		//- Temporary storage for addressing
		mutable labelHashSet labelSet_;


		// Geometric data

			//- Cell centres
		mutable vectorField* cellCentresPtr_;

		//- Face centres
		mutable vectorField* faceCentresPtr_;

		//- Cell volumes
		mutable scalarField* cellVolumesPtr_;

		//- Face areas
		mutable vectorField* faceAreasPtr_;


		// Private member functions

			//- Disallow construct as copy
		primitiveMesh(const primitiveMesh&);

		//- Disallow default bitwise assignment
		void operator=(const primitiveMesh&);


		// Topological calculations

			//- Calculate cell shapes
		void calcCellShapes() const;

		//- Calculate cell-cell addressing
		void calcCellCells() const;

		//- Calculate point-cell addressing
		void calcPointCells() const;

		//- Calculate cell-face addressing
		void calcCells() const;

		//- Calculate edge list
		void calcCellEdges() const;

		//- Calculate point-edge addressing
		void calcPointEdges() const;

		//- Calculate point-point addressing
		void calcPointPoints() const;

		//- Calculate edges, pointEdges and faceEdges
		void calcEdges() const;

		//- During edge calculation, a larger set of data is assembled.
		// Create and destroy as a set, using clearOutEdges()
		void clearOutEdges();

		//- Helper:
		//  return (after optional creation) edge between two points
		static label getEdge
		(
			List<dynamicLabelList >&,
			DynamicList<edge>&,
			const label,
			const label
		);
		//- For on-the-fly addressing calculation
		static label findFirstCommonElementFromSortedLists
		(
			const labelList&,
			const labelList&
		);


		// Geometrical calculations

			//- Calculate face centres and areas
		void calcFaceCentresAndAreas() const;

		void makeFaceCentresAndAreas
		(
			const pointField& p,
			vectorField& fCtrs,
			vectorField& fAreas
		) const;

		//- Calculate cell centres and volumes
		void calcCellCentresAndVols() const;
		void makeCellCentresAndVols
		(
			const vectorField& fCtrs,
			const vectorField& fAreas,
			vectorField& cellCtrs,
			scalarField& cellVols
		) const;

		//- Calculate edge vectors
		void calcEdgeVectors() const;


		// Helper functions for mesh checking

			//- Check if all points on face are shared with another face.
		bool checkDuplicateFaces
		(
			const label,
			const Map<label>&,
			label& nBaffleFaces,
			labelHashSet*
		) const;

		//- Check that shared points are in consecutive order.
		bool checkCommonOrder
		(
			const label,
			const Map<label>&,
			labelHashSet*
		) const;


	protected:

		//- Construct null
		primitiveMesh();


	public:

		// Static data

		ClassName("primitiveMesh");


		// Static mesh analysis data

				//- Estimated number of cells per edge
		static const unsigned cellsPerEdge_ = 4;

		//- Estimated number of cells per point
		static const unsigned cellsPerPoint_ = 8;

		//- Estimated number of faces per cell
		static const unsigned facesPerCell_ = 6;

		//- Estimated number of faces per edge
		static const unsigned facesPerEdge_ = 4;

		//- Estimated number of faces per point
		static const unsigned facesPerPoint_ = 12;

		//- Estimated number of edges per cell
		static const unsigned edgesPerCell_ = 12;

		//- Estimated number of edges per cell
		static const unsigned edgesPerFace_ = 4;

		//- Estimated number of edges per point
		static const unsigned edgesPerPoint_ = 6;

		//- Estimated number of points per cell
		static const unsigned pointsPerCell_ = 8;

		//- Estimated number of points per face
		static const unsigned pointsPerFace_ = 4;

		//- Static data to control mesh checking

			//- Cell closedness warning threshold
			//  set as the fraction of un-closed area to closed area
		static const debug::tolerancesSwitch closedThreshold_;

		//- Aspect ratio warning threshold
		static const debug::tolerancesSwitch aspectThreshold_;

		//- Non-orthogonality warning threshold in deg
		static tnbLib::debug::tolerancesSwitch nonOrthThreshold_;

		//- Skewness warning threshold
		static const debug::tolerancesSwitch skewThreshold_;

		//- Face angle threshold
		static tnbLib::debug::tolerancesSwitch faceAngleThreshold_;

		//- Face flatness threshold
		static const debug::tolerancesSwitch faceFlatnessThreshold_;


		// Constructors

			//- Construct from components
		primitiveMesh
		(
			const label nPoints,
			const label nInternalFaces,
			const label nFaces,
			const label nCells
		);


		// Destructor

		virtual ~primitiveMesh();


		// Member Functions

			//- Reset this primitiveMesh given the primitive array sizes
		void reset
		(
			const label nPoints,
			const label nInternalFaces,
			const label nFaces,
			const label nCells
		);

		//- Reset this primitiveMesh given the primitive array sizes and cells
		void reset
		(
			const label nPoints,
			const label nInternalFaces,
			const label nFaces,
			const label nCells,
			cellList& cells
		);


		//- Reset this primitiveMesh given the primitive array sizes and cells
		void reset
		(
			const label nPoints,
			const label nInternalFaces,
			const label nFaces,
			const label nCells,
			const Xfer<cellList>& cells
		);


		// Access

			// Mesh size parameters

		label nPoints() const;
		label nEdges() const;
		label nInternalFaces() const;
		label nFaces() const;
		label nCells() const;


		// Primitive mesh data

			//- Return mesh points
		virtual const pointField& points() const = 0;

		//- Return faces
		virtual const faceList& faces() const = 0;

		//- Face face-owner addresing
		virtual const labelList& faceOwner() const = 0;

		//- Face face-neighbour addressing
		virtual const labelList& faceNeighbour() const = 0;

		//- Return old points for mesh motion
		virtual const pointField& oldPoints() const = 0;


		// Derived mesh data

			//- Return cell shapes
		const cellShapeList& cellShapes() const;

		//- Return mesh edges. Uses calcEdges.
		const edgeList& edges() const;

		//- Helper function to calculate cell-face addressing from
		//  face-cell addressing. If nCells is not provided it will
		//  scan for the maximum.
		static void calcCells
		(
			cellList&,
			const unallocLabelList& own,
			const unallocLabelList& nei,
			const label nCells = -1
		);

		// Removed calcPointOrder - garbage.  HJ, 27/Aug/2010


		// Return mesh connectivity

		const labelListList& cellCells() const;
		// faceCells given as owner and neighbour
		const labelListList& edgeCells() const;
		const labelListList& pointCells() const;

		const cellList& cells() const;
		// faceFaces considered unnecessary
		const labelListList& edgeFaces() const;
		const labelListList& pointFaces() const;

		const labelListList& cellEdges() const;
		const labelListList& faceEdges() const;
		// edgeEdges considered unnecessary
		const labelListList& pointEdges() const;
		const labelListList& pointPoints() const;
		const labelListList& cellPoints() const;


		// Geometric data (raw!)

		const vectorField& cellCentres() const;
		const vectorField& faceCentres() const;
		const scalarField& cellVolumes() const;
		const vectorField& faceAreas() const;


		// Mesh motion

			//- Move points, returns volumes swept by faces in motion
		tmp<scalarField> movePoints
		(
			const pointField& p,
			const pointField& oldP
		);


		//- Return true if given face label is internal to the mesh
		bool isInternalFace(const label faceIndex) const;


		// Topological checks

			//- Check cell zip-up
		bool checkCellsZipUp
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check uniqueness of face vertices
		bool checkFaceVertices
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check face-face connectivity
		bool checkFaceFaces
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check face ordering
		bool checkUpperTriangular
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;


		// Geometric checks

			//- Check boundary for closedness
		bool checkClosedBoundary(const bool report = false) const;

		//- Check cells for closedness
		bool checkClosedCells
		(
			const bool report = false,
			labelHashSet* setPtr = NULL,
			labelHashSet* highAspectSetPtr = NULL
		) const;

		//- Check for negative face areas
		bool checkFaceAreas
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check for negative cell volumes
		bool checkCellVolumes
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check for non-orthogonality
		bool checkFaceOrthogonality
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check face pyramid volume
		bool checkFacePyramids
		(
			const bool report = false,
			const scalar minPyrVol = -SMALL,
			labelHashSet* setPtr = NULL
		) const;

		//- Check face skewness
		bool checkFaceSkewness
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check face angles
		bool checkFaceAngles
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check face warpage: decompose face and check ratio between
		//  magnitude of sum of triangle areas and sum of magnitude of
		//  triangle areas.
		bool checkFaceFlatness
		(
			const bool report,
			labelHashSet* setPtr
		) const;

		//- Check edge alignment for 1D/2D cases
		bool checkEdgeAlignment
		(
			const bool report,
			const Vector<label>& directions,
			labelHashSet* setPtr = NULL
		) const;

		//- Check for unused points
		bool checkPoints
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;

		//- Check for point-point-nearness,
		//  e.g. colocated points which may be part of baffles.
		bool checkPointNearness
		(
			const bool report,
			const scalar reportDistSqr,
			labelHashSet* setPtr = NULL
		) const;

		//- Check edge length
		bool checkEdgeLength
		(
			const bool report,
			const scalar minLenSqr,
			labelHashSet* setPtr = NULL
		) const;

		//- Check cell determinant
		bool checkCellDeterminant
		(
			const bool report = false,
			labelHashSet* setPtr = NULL
		) const;


		//- Check mesh topology for correctness.
		//  Returns false for no error.
		bool checkTopology(const bool report = false) const;

		//- Check mesh geometry (& implicitly topology) for correctness.
		//  Returns false for no error.
		bool checkGeometry(const bool report = false) const;

		//- Check mesh for correctness. Returns false for no error.
		bool checkMesh(const bool report = false) const;

		//- Check mesh motion for correctness given motion points
		bool checkMeshMotion
		(
			const pointField& newPoints,
			const bool report = false
		) const;


		// Useful derived info

			//- Is the point in the cell bounding box
		bool pointInCellBB(const point& p, label celli) const;

		//- Is the point in the cell
		bool pointInCell(const point& p, label celli) const;

		//- Find the cell with the nearest cell centre to location
		label findNearestCell(const point& location) const;

		//- Find cell enclosing this location (-1 if not in mesh)
		label findCell(const point& location) const;


		//  Storage management

			//- Print a list of all the currently allocated mesh data
		void printAllocated() const;

		// Per storage whether allocated
		bool hasCellShapes() const;
		bool hasEdges() const;
		bool hasCellCells() const;
		bool hasEdgeCells() const;
		bool hasPointCells() const;
		bool hasCells() const;
		bool hasEdgeFaces() const;
		bool hasPointFaces() const;
		bool hasCellEdges() const;
		bool hasFaceEdges() const;
		bool hasPointEdges() const;
		bool hasPointPoints() const;
		bool hasCellPoints() const;
		bool hasCellCentres() const;
		bool hasFaceCentres() const;
		bool hasCellVolumes() const;
		bool hasFaceAreas() const;

		// On-the-fly addressing calculation. These functions return either
		// a reference to the full addressing (if already calculated) or
		// a reference to the supplied storage. The one-argument ones
		// use member DynamicList labels_ so be careful when not storing
		// result.

		//- cellCells using cells.
		const labelList& cellCells
		(
			const label cellI,
			dynamicLabelList&
		) const;

		const labelList& cellCells(const label cellI) const;

		//- cellPoints using cells
		const labelList& cellPoints
		(
			const label cellI,
			dynamicLabelList&
		) const;

		const labelList& cellPoints(const label cellI) const;

		//- pointCells using pointFaces
		const labelList& pointCells
		(
			const label pointI,
			dynamicLabelList&
		) const;

		const labelList& pointCells(const label pointI) const;

		//- pointPoints using edges, pointEdges
		const labelList& pointPoints
		(
			const label pointI,
			dynamicLabelList&
		) const;

		const labelList& pointPoints(const label pointI) const;

		//- faceEdges using pointFaces, edges, pointEdges
		const labelList& faceEdges
		(
			const label faceI,
			dynamicLabelList&
		) const;

		const labelList& faceEdges(const label faceI) const;

		//- edgeFaces using pointFaces, edges, pointEdges
		const labelList& edgeFaces
		(
			const label edgeI,
			dynamicLabelList&
		) const;

		const labelList& edgeFaces(const label edgeI) const;

		//- edgeCells using pointFaces, edges, pointEdges
		const labelList& edgeCells
		(
			const label edgeI,
			dynamicLabelList&
		) const;

		const labelList& edgeCells(const label edgeI) const;

		//- cellEdges using cells, pointFaces, edges, pointEdges
		const labelList& cellEdges
		(
			const label cellI,
			dynamicLabelList&
		) const;

		const labelList& cellEdges(const label cellI) const;


		//- Clear geometry
		void clearGeom();

		//- Clear topological data
		void clearAddressing();

		//- Clear all geometry and addressing unnecessary for CFD
		void clearOut();
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <primitiveMeshI.hxx>

#endif // !_primitiveMesh_Header
