#pragma once
#ifndef _cyclicFvPatchFieldsFwd_Header
#define _cyclicFvPatchFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class cyclicFvPatchField;

	makePatchTypeFieldTypedefs(cyclic)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicFvPatchFieldsFwd_Header
