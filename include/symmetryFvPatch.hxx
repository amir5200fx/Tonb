#pragma once
#ifndef _symmetryFvPatch_Header
#define _symmetryFvPatch_Header

#include <fvPatch.hxx>
#include <symmetryPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class symmetryFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class symmetryFvPatch
		: public fvPatch
	{

	protected:

		// Protected Member Functions

			//- Make patch face non-orthogonality correction vectors
		virtual void makeCorrVecs(vectorField&) const;


	public:

		//- Runtime type information
		TypeName(symmetryPolyPatch::typeName_());


		// Constructors

			//- Construct from polyPatch
		symmetryFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			fvPatch(patch, bm)
		{}


		// Destructor

		virtual ~symmetryFvPatch()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_symmetryFvPatch_Header
