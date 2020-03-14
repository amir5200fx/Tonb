#pragma once
# ifdef USE_OMP
#include <omp.h>
# endif

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline const VRWGraph& triSurfAddressing::pointFacets() const
	{
		if (!pointFacetsPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const VRWGraph& triSurfAddressing::pointFacets() const"
				) << "Cannot calculate pointFacets" << abort(FatalError);
# endif

			calculatePointFacets();
		}

		return *pointFacetsPtr_;
	}

	inline const edgeLongList& triSurfAddressing::edges() const
	{
		if (!edgesPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const edgeLongList& triSurfAddressing::edges() const"
				) << "Cannot calculate edges" << abort(FatalError);
# endif

			calculateEdges();
		}

		return *edgesPtr_;
	}

	inline const VRWGraph& triSurfAddressing::facetEdges() const
	{
		if (!facetEdgesPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const VRWGraph& triSurfAddressing::facetEdges() const"
				) << "Cannot calculate facetEdges" << abort(FatalError);
# endif

			calculateFacetEdges();
		}

		return *facetEdgesPtr_;
	}

	inline const VRWGraph& triSurfAddressing::edgeFacets() const
	{
		if (!edgeFacetsPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const VRWGraph& triSurfAddressing::edgeFacets() const"
				) << "Cannot calculate edgeFacets" << abort(FatalError);
# endif

			calculateEdgeFacets();
		}

		return *edgeFacetsPtr_;
	}

	inline const VRWGraph& triSurfAddressing::pointEdges() const
	{
		if (!pointEdgesPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const VRWGraph& triSurfAddressing::pointEdges() const"
				) << "Cannot calculate pointEdges" << abort(FatalError);
# endif

			calculatePointEdges();
		}

		return *pointEdgesPtr_;
	}

	inline const VRWGraph& triSurfAddressing::facetFacets() const
	{
		if (!facetFacetsEdgesPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const VRWGraph& triSurfAddressing::facetFacets() const"
				) << "Cannot calculate facetFacets" << abort(FatalError);
# endif

			calculateFacetFacetsEdges();
		}

		return *facetFacetsEdgesPtr_;
	}

	inline const vectorField& triSurfAddressing::pointNormals() const
	{
		if (!pointNormalsPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const vectorField&"
					" triSurfAddressing::pointNormals() const"
				) << "Cannot calculate pointNormals" << abort(FatalError);
# endif

			calculatePointNormals();
		}

		return *pointNormalsPtr_;
	}

	inline const vectorField& triSurfAddressing::facetNormals() const
	{
		if (!facetNormalsPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const vectorField&"
					" triSurfAddressing::facetNormals() const"
				) << "Cannot calculate facetNormals" << abort(FatalError);
# endif

			calculateFacetNormals();
		}

		return *facetNormalsPtr_;
	}

	inline const vectorField& triSurfAddressing::facetCentres() const
	{
		if (!facetCentresPtr_)
		{
# ifdef USE_OMP
			if (omp_in_parallel())
				FatalErrorIn
				(
					"inline const vectorField&"
					" triSurfAddressing::facetCentres() const"
				) << "Cannot calculate facetCentres" << abort(FatalError);
# endif

			calculateFacetCentres();
		}

		return *facetCentresPtr_;
	}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
