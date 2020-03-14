#pragma once
#ifndef _triSurfFacets_Header
#define _triSurfFacets_Header

#include <meshSubset.hxx>
#include <geometricSurfacePatchList.hxx>
#include <LongList.hxx>
#include <labelledTri.hxx>
#include <DynList.hxx>
#include <Map.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class triSurfFacets
	{
	protected:

		// Protected data
			//- list of triangles
		LongList<labelledTri> triangles_;

		//- list of boundary patches and their properties
		geometricSurfacePatchList patches_;

		//- map of point subsets
		Map<meshSubset> facetSubsets_;

		// Disallow bitwise assignment
		void operator=(const triSurfFacets&);

		triSurfFacets(const triSurfFacets&);

	public:

		// Constructors
			//- Null constructor
		triSurfFacets();

		//- Construct from components without the boundary
		triSurfFacets(const LongList<labelledTri>& triangles);

		//- Construct from components
		triSurfFacets
		(
			const LongList<labelledTri>& triangles,
			const geometricSurfacePatchList& patches
		);

		// Destructor
		~triSurfFacets();

		// Member functions
			//- return the number of triangles
		inline label size() const;

		//- access to facets
		inline const LongList<labelledTri>& facets() const;

		//- access to patches
		inline const geometricSurfacePatchList& patches() const;

		//- return list of patches in the boundary
		wordList patchNames() const;

		//- return a list of patch indices corresponding to the given
		// name, expanding regular expressions
		labelList findPatches(const word& patchName) const;

		//- append a triangle to the end of the list
		inline void appendTriangle(const labelledTri& tria);

		//- point subsets
		label addFacetSubset(const word&);
		void removeFacetSubset(const label);
		word facetSubsetName(const label) const;
		label facetSubsetIndex(const word&) const;
		inline void addFacetToSubset(const label, const label);
		inline void removeFacetFromSubset(const label, const label);
		inline void facetInSubsets(const label, DynList<label>&) const;
		inline void facetSubsetIndices(DynList<label>&) const;
		template<class ListType>
		inline void facetsInSubset(const label, ListType&) const;
		template<class ListType>
		inline void updateFacetsSubsets(const ListType&);

		// Operators

			//- access to a triangle
		inline const labelledTri& operator[](const label) const;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <triSurfFacetsI.hxx>

#endif // !_triSurfFacets_Header
