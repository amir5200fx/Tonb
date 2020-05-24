#pragma once
#ifndef _wallFvPatch_Header
#define _wallFvPatch_Header

#include <fvPatch.hxx>
#include <wallPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class wallFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class wallFvPatch
		: public fvPatch
	{
	protected:

		// Protected Member Functions

			//- Make patch face non-orthogonality correction vectors
		virtual void makeCorrVecs(vectorField&) const;


	public:

		//- Runtime type information
		TypeName(wallPolyPatch::typeName_());


		// Constructors

			//- Construct from components
		wallFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			fvPatch(patch, bm)
		{}


		// Destructor

		virtual ~wallFvPatch()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wallFvPatch_Header
