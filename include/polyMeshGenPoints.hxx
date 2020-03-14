#pragma once
#ifndef _polyMeshGenPoints_Header
#define _polyMeshGenPoints_Header

#include <objectRegistry.hxx>
#include <tnbTime.hxx>
#include <meshSubset.hxx>
#include <pointFieldPMG.hxx>
#include <DynList.hxx>

#include <map>

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	class polyMeshGenPoints
	{
	protected:

		// Protected data
			//- reference to the Time registry
		const Time& runTime_;

		//- list of vertices
		pointFieldPMG points_;

		//- map of point subsets
		std::map<label, meshSubset> pointSubsets_;

		// Disallow bitwise assignment
		void operator=(const polyMeshGenPoints&);

		polyMeshGenPoints(const polyMeshGenPoints&);

	public:

		friend class polyMeshGenModifier;

		// Constructors
			//- Null constructor
		polyMeshGenPoints(const Time&);

		//- Construct from components without the boundary
		polyMeshGenPoints
		(
			const Time&,
			const pointField& points
		);

		// Destructor
		~polyMeshGenPoints();

		// Member functions
			//- access to Time
		inline const Time& returnTime() const;

		//- access to points
		inline const pointFieldPMG& points() const;

		//- non-const access to points
		inline pointFieldPMG& points();

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

		// Read mesh
		void read();

		// Write mesh
		void write() const;
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <polyMeshGenPointsI.hxx>

#endif // !_polyMeshGenPoints_Header
