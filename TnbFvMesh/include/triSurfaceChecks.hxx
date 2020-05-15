#pragma once
#ifndef _triSurfaceChecks_Header
#define _triSurfaceChecks_Header

#include <labelLongList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class triSurf;
	class boundBox;

	/*---------------------------------------------------------------------------*\
						Namespace triSurfaceChecka Declaration
	\*---------------------------------------------------------------------------*/

	namespace triSurfaceChecks
	{

		//- check the angles of triangles. Triangles wth the smallest angle below
		//- the given threshold are marked as bad-quality triangles
		label checkAngles
		(
			const triSurf&,
			labelLongList&,
			const scalar angleTol = 5.0
		);

		label checkAngles
		(
			triSurf&,
			const word subsetName = "smallAngles",
			const scalar angleTol = 5.0
		);

		//- check for existence of boudary and non-manifold edges
		label checkSurfaceManifolds(const triSurf&, labelLongList&triangleInManifold);
		label checkSurfaceManifolds(triSurf&, const word subsetPrefix = "manifold_");

		//- check for existence of holes in the surface mesh
		label checkForHoles(const triSurf&, labelLongList&);
		label checkForHoles(triSurf&, const word subsetName = "holes");

		//- check for existence of non-manifold edges
		label checkForNonManifoldEdges(const triSurf&, labelLongList&);
		label checkForNonManifoldEdges
		(
			triSurf&,
			const word subsetPrefix = "nonManifold_"
		);

		//- check orientation of triangles
		label checkOrientation(const triSurf&, labelLongList& triangleInGroup);
		label checkOrientation(triSurf&, const word subsetPrefix = "orientation_");

		//- check for disconnected surface parts
		label checkDisconnectedParts(const triSurf&, labelLongList& triangleInRegion);
		label checkDisconnectedParts(triSurf&, const word subsetPrefix = "region_");

		//- calculate bounding box of the surface mesh
		void calculateBoundingBox(const triSurf&, boundBox&);

		//- check existence of collocated points
		label checkCollocatedPoints
		(
			const triSurf&,
			labelLongList&,
			const scalar distTol = 1e-6
		);
		label checkCollocatedPoints
		(
			triSurf&,
			const word subsetName = "collocatedPoints",
			const scalar distTol = 1e-6
		);

		//- check if there exist any self-intersections
		label checkSelfIntersections
		(
			const triSurf&,
			labelLongList&,
			const scalar tol = 1e-6
		);
		label checkSelfIntersections
		(
			triSurf&,
			const word subsetName = "selfIntersect",
			const scalar tol = 1e-6
		);

		//- check if there exist any overlaps
		label checkOverlaps
		(
			const triSurf&,
			labelLongList&,
			const scalar tol = 1e-6,
			const scalar angleTol = 5.0
		);
		label checkOverlaps
		(
			triSurf&,
			const word subsetName = "overlappingTriangles",
			const scalar tol = 1e-6,
			const scalar angleTol = 5.0
		);

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace triSurfaceChecks

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_triSurfaceChecks_Header
