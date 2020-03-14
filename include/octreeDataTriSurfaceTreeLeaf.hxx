#pragma once
#ifndef _octreeDataTriSurfaceTreeLeaf_Header
#define _octreeDataTriSurfaceTreeLeaf_Header 

#include <treeLeaf.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of classes
	class octreeDataTriSurface;

	template<>
	bool treeLeaf<octreeDataTriSurface>::findNearest
	(
		const octreeDataTriSurface& shapes,
		const point& sample,
		treeBoundBox& tightest,
		label& tightestI,
		scalar& tightestDist
	) const;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_octreeDataTriSurfaceTreeLeaf_Header
