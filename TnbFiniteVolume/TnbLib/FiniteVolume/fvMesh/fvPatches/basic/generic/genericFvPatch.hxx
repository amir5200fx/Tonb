#pragma once
#ifndef _genericFvPatch_Header
#define _genericFvPatch_Header

#include <fvPatch.hxx>
#include <genericPolyPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class genericFvPatch Declaration
	\*---------------------------------------------------------------------------*/

	class genericFvPatch
		: public fvPatch
	{

	public:

		//- Runtime type information
		TypeName(genericPolyPatch::typeName_());


		// Constructors

			//- Construct from components
		genericFvPatch(const polyPatch& patch, const fvBoundaryMesh& bm)
			:
			fvPatch(patch, bm)
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_genericFvPatch_Header
