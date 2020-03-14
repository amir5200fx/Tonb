#pragma once
#ifndef _LongList_Header
#define _LongList_Header

#include <label.hxx>
#include <bool.hxx>
#include <IOstreams.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * Forward declaration of template friend fuctions * * * * * * * //

	template<class T, label Offset>
	class LongList;

	template<class T, label Offset>
	Ostream& operator<<
		(
			Ostream&,
			const LongList<T, Offset>&
			);
	template<class T, label Offset>
	Istream& operator>>
		(
			Istream&,
			LongList<T, Offset>&
			);

	/*---------------------------------------------------------------------------*\
							   Class LongList Declaration
	\*---------------------------------------------------------------------------*/

	template<class T, label Offset = 19>
	class LongList
	{
		// Private data
			//- number of allocated elements
		label N_;

		//- number of elements in the list
		label nextFree_;

		//- number of used blocks of data
		label numBlocks_;

		//- maximum number of blocks that can be allocated
		//- without reallocating the list containing pointers
		//- to the chunks of data
		label numAllocatedBlocks_;

		//- size of blocks is calculated by powers of 2
		//- and therefore the access can be done using shift and mask
		label shift_;
		label mask_;

		//- array of pointers to the blocks of data, each of the size WIDTH
		T** dataPtr_;

		// Private member functions
			//- check index
		void checkIndex(const label i) const;

		//- initialize width and mask
		void initializeParameters();

		//- Allocate memory for the list
		void allocateSize(const label);

		//- delete all elements
		void clearOut();

	public:

		// Constructors

			//- Construct null
		inline LongList();

		//- Construct given size
		explicit inline LongList(const label size);

		//- Construct to given size and initialize
		explicit inline LongList(const label size, const T& t);

		//- Copy contructor
		inline LongList(const LongList<T, Offset>&);

		// Destructor

		inline ~LongList();

		// Member Functions

			// Access

				//- Size of the active part of the list.
		inline label size() const;

		//- Return the binary size in number of characters of the UList
		//  if the element is a primitive type
		//  i.e. contiguous<T>() == true
		inline label byteSize() const;

		// Edit

			//- Reset size of List.
		void setSize(const label);

		//- Clear the list, i.e. set next free to zero.
		//  Allocated size does not change
		void clear();

		//- Shrink the list to the number of elements used
		inline LongList<T, Offset>& shrink();

		//- transfer the list from another one without allocating it
		inline void transfer(LongList<T, Offset>&);


		// Member Operators

			//- Append an element at the end of the list
		inline void append(const T& e);

		//- Append an element at the end of the list if it is not yet
		//- present in the list (takes linear time)
		inline void appendIfNotIn(const T& e);

		//- check if the element is in the list (takes linear time)
		inline bool contains(const T& e) const;
		inline label containsAtPosition(const T& e) const;

		//- Return and remove the element
		inline T remove(const label i);
		inline T removeLastElement();

		//- get and set operators
		inline const T& operator[](const label i) const;
		inline T& operator[](const label i);

		//- Return non-const access to an element,
		//  resizing the list if necessary
		inline T& operator()(const label);

		//- return a non-const access to an element,
		// resize the list if necessary
		inline T& newElmt(const label);

		//- Assignment of all entries to the given value
		inline void operator=(const T&);

		//- Assignment operator
		inline void operator=(const LongList<T, Offset>&);


		// IOstream operators
			//- Read from stream and append to the current content
		void appendFromStream(Istream&);

		//- Write as a dictionary entry.
		void writeEntry(Ostream& os) const;

		//- Write as a dictionary entry with keyword.
		void writeEntry(const word& keyword, Ostream& os) const;

		// Write LongList to Ostream.
		friend Ostream& operator<< <T, Offset>
			(
				Ostream&,
				const LongList<T, Offset>&
				);

		//- Read from Istream, discarding contents of existing LongList.
		friend Istream& operator>> <T, Offset>
			(
				Istream&,
				LongList<T, Offset>&
				);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <LongListI.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include <LongList.cxx>
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_LongList_Header
