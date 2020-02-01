#pragma once
#ifndef _fvPatchFieldMapper_Header
#define _fvPatchFieldMapper_Header

#include <primitiveFields.hxx>
#include <FieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class fvPatchFieldMapper Declaration
	\*---------------------------------------------------------------------------*/

	class fvPatchFieldMapper
		:
		public FieldMapper
	{

	public:

		// Constructors

			//- Null constructor
		fvPatchFieldMapper()
		{}
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvPatchFieldMapper_Header
