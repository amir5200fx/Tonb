#pragma once
#ifndef _subGraph_Header
#define _subGraph_Header

#include <bool.hxx>
#include <Ostream.hxx>
#include <error.hxx>
#include <graphRow.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class graphType> class subGraph;
	template<class graphType>
	Ostream& operator<<(Ostream&, const subGraph<graphType>&);

	/*---------------------------------------------------------------------------*\
							   Class subGraph Declaration
	\*---------------------------------------------------------------------------*/

	template<class graphType>
	class subGraph
	{
		// Private data
			//- reference to the graph
		graphType& data_;

		//- starts at row
		const label start_;

		//- number of rows in the subGraph
		const label size_;

		// Private member functions
			//- check index
		inline void checkIndex(const label i) const;

	public:

		// Constructors

			//- Construct from graph and start row and size
		inline subGraph(graphType&, const label, const label);

		//- Copy contructor
		inline subGraph(const subGraph<graphType>&);

		// Destructor

		inline ~subGraph();

		// Member Functions

			//- Returns the number of rows
		inline label size() const;

		//- Returns the size of a given row
		inline label sizeOfRow(const label rowI) const;

		// Member Operators

			//- Append an element to the given row
		inline void append(const label rowI, const label);

		//- Append an element to the given row if it does not exist there
		inline void appendIfNotIn(const label rowI, const label);

		//- check if the element is in the given row (takes linear time)
		inline bool contains(const label rowI, const label e) const;
		inline label containsAtPosition(const label rowI, const label e) const;

		//- set and get operators
		inline label operator()(const label i, const label j) const;
		inline label& operator()(const label i, const label j);
		inline const graphRow<const graphType> operator[](const label) const;
		inline graphRow<graphType> operator[](const label);

		// IOstream operators

			// Write subGraph to Ostream.
		friend Ostream& operator<< <graphType>
			(
				Ostream&,
				const subGraph<graphType>&
				);
	};

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <subGraphI.hxx>

#endif // !_subGraph_Header
