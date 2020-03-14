#pragma once
#ifndef _VRWGraphList_Header
#define _VRWGraphList_Header

#include <VRWGraph.hxx>
#include <subGraph.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class VRWGraphList Declaration
	\*---------------------------------------------------------------------------*/

	class VRWGraphList
	{

		// Private data
			//- graph containing the data
		VRWGraph data_;

		//- number of rows
		LongList<rowElement> rows_;

		// Private member functions
			//- check index
		inline void checkIndex
		(
			const label i,
			const label j,
			const label k
		) const;

	public:

		// Constructors

			//- Construct null
		inline VRWGraphList();

		//- Copy contructor
		inline VRWGraphList(const VRWGraphList&);

		// Destructor

		inline ~VRWGraphList();

		// Member Functions

			// Access

				//- Returns the number of graphs
		inline label size() const;

		//- Returns the number of rows in the graph at that position
		inline label sizeOfGraph(const label posI) const;

		//- Return the number of element in the row at the given position
		inline label sizeOfRow(const label posI, const label rowI) const;

		//- Clear the graph
		inline void clear();

		// Member Operators

			//- Append a graph at the end of the graphList
		template<class GraphType>
		inline void appendGraph(const GraphType& l);

		//- get and set operators
		inline label operator()
			(
				const label i,
				const label j,
				const label k
				) const;

		inline label& operator()(const label i, const label j, const label k);

		inline const subGraph<const VRWGraph> operator[](const label i) const;

		//- Assignment operator
		inline void operator=(const VRWGraphList&);


		// IOstream operators

			// Write VRWGraphList to Ostream.
		friend Ostream& operator<<(Ostream&, const VRWGraphList&);

		//- Read from Istream, discarding contents of existing VRWGraphList.
/*        friend Istream& operator>> <T, width>
		(
			Istream&,
			VRWGraphList<T, width>&
		);
*/
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <VRWGraphListI.hxx>

#endif // !_VRWGraphList_Header
