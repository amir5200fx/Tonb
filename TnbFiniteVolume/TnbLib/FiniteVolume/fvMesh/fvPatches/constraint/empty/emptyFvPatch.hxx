#pragma once
#ifndef _emptyFvPatch_Header
#define _emptyFvPatch_Header

#include <fvPatch.hxx>
#include <emptyPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class emptyFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class emptyFvPatch
		: public fvPatch
	{
		// Private data

			//- Dummy face-cell addressing
		const labelList::subList faceCells_;


	public:

		//- Runtime type information
		TypeName(emptyPolyPatch::typeName_());


		// Constructors

			//- Construct from polyPatch
		emptyFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm);


		// Member Functions

			// Access

		virtual label size() const
		{
			return 0;
		}

		//- Return faceCells of zero size
		virtual const unallocLabelList& faceCells() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyFvPatch_Header
