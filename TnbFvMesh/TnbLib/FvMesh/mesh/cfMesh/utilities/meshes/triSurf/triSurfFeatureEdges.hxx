#pragma once
#ifndef _triSurfFeatureEdges_Header
#define _triSurfFeatureEdges_Header

#include <edgeLongList.hxx>
#include <meshSubset.hxx>
#include <Map.hxx>
#include <DynList.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class triSurfFeatureEdges
	{
	protected:

		// Protected data
			//- list of feature edges
		edgeLongList featureEdges_;

		//- map of edge subsets
		Map<meshSubset> featureEdgeSubsets_;

		// Disallow bitwise assignment
		void operator=(const triSurfFeatureEdges&);

		triSurfFeatureEdges(const triSurfFeatureEdges&);

	public:

		// Constructors
			//- Null constructor
		triSurfFeatureEdges();

		//- Construct from feature edges
		triSurfFeatureEdges(const edgeLongList& triangles);

		// Destructor
		~triSurfFeatureEdges();

		// Member functions
			//- return the number of feature edges
		inline label nFeatureEdges() const;

		//- access to feature edges
		inline const edgeLongList& featureEdges() const;

		//- append an edge to the end of the list
		inline void appendFeatureEdge(const edge& e);

		//- point subsets
		label addEdgeSubset(const word&);
		void removeEdgeSubset(const label);
		word edgeSubsetName(const label) const;
		label edgeSubsetIndex(const word&) const;
		inline void addEdgeToSubset(const label, const label);
		inline void removeEdgeFromSubset(const label, const label);
		inline void edgeInSubsets(const label, DynList<label>&) const;
		inline void edgeSubsetIndices(DynList<label>&) const;
		template<class ListType>
		inline void edgesInSubset(const label, ListType&) const;
		template<class ListType>
		inline void updateEdgeSubsets(const ListType&);

		// Operators
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <triSurfFeatureEdgesI.hxx>

#endif // !_triSurfFeatureEdges_Header
