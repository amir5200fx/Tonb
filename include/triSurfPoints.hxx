#pragma once
#ifndef _triSurfPoints_Header
#define _triSurfPoints_Header

#include <meshSubset.hxx>
#include <pointField.hxx>
#include <DynList.hxx>
#include <Map.hxx>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class triSurfPoints
	{
	protected:

		// Protected data
			//- list of vertices
		pointField points_;

		//- map of point subsets
		Map<meshSubset> pointSubsets_;

		// Disallow bitwise assignment
		void operator=(const triSurfPoints&);

		triSurfPoints(const triSurfPoints&);

	public:

		// Constructors
			//- Null constructor
		triSurfPoints();

		//- Construct from vertices
		triSurfPoints(const pointField& points);

		// Destructor
		~triSurfPoints();

		// Member functions
			//- return the number of points
		inline label nPoints() const;

		//- access to points
		inline const pointField& points() const;

		//- append a vertex to the end of the list
		inline void appendVertex(const point& p);

		//- point subsets
		label addPointSubset(const word&);
		void removePointSubset(const label);
		word pointSubsetName(const label) const;
		label pointSubsetIndex(const word&) const;
		inline void addPointToSubset(const label, const label);
		inline void removePointFromSubset(const label, const label);
		inline void pointInSubsets(const label, DynList<label>&) const;
		inline void pointSubsetIndices(DynList<label>&) const;
		template<class ListType>
		inline void pointsInSubset(const label, ListType&) const;
		template<class ListType>
		inline void updatePointSubsets(const ListType&);
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <triSurfPointsI.hxx>

#endif // !_triSurfPoints_Header
