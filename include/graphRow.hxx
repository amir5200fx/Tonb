#pragma once
#ifndef _graphRow_Header
#define _graphRow_Header

#include <bool.hxx>
#include <Ostream.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class VRWGraph;

	template<class graphType> class graphRow;
	template<class graphType>
	Ostream& operator<<(Ostream&, const graphRow<graphType>&);

	/*---------------------------------------------------------------------------*\
							   Class graphRow Declaration
	\*---------------------------------------------------------------------------*/

	template<class graphType>
	class graphRow
	{
		// Private data
			//- reference to the graph
		graphType& data_;

		//- row number
		const label rowI_;

		// Private member functions
			//- check index
		inline void checkIndex(const label i) const;

	public:

		// Constructors

			//- Construct from graph and row number
		inline graphRow(graphType&, const label);

		//- Copy contructor
		inline graphRow(const graphRow<graphType>&);

		// Destructor

		inline ~graphRow();

		// Member Functions

			//- Returns the number of rows
		inline label size() const;

		//- Reset the number of rows
		inline void setSize(const label size);

		//- Clear the graph
		inline void clear();

		// Member Operators

			//- Append an element to the given row
		inline void append(const label);

		//- Append an element to the given row if it does not exist there
		inline void appendIfNotIn(const label);

		//- check if the element is in the given row (takes linear time)
		inline bool contains(const label e) const;
		inline label containsAtPosition(const label e) const;

		//- set and get operators
		inline label operator[](const label) const;
		inline label& operator[](const label);

		//- Assignment operator
		inline void operator=(const graphRow<graphType>&);
		template<class listType>
		inline void operator=(const listType&);

		// IOstream operators

			// Write graphRow to Ostream.
		friend Ostream& operator<< <graphType>
			(
				Ostream&,
				const graphRow<graphType>&
				);

		//- Read from Istream, discarding contents of existing graphRow.
/*        friend Istream& operator>> <T, width>
		(
			Istream&,
			graphRow<T, width>&
		);
*/
	};

	typedef const graphRow<const VRWGraph> constRow;
	typedef graphRow<VRWGraph> row;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <graphRowI.hxx>

#endif // !_graphRow_Header
