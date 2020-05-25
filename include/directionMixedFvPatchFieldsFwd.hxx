#pragma once
#ifndef _directionMixedFvPatchFieldsFwd_Header
#define _directionMixedFvPatchFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class directionMixedFvPatchField;

	makePatchTypeFieldTypedefs(directionMixed)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_directionMixedFvPatchFieldsFwd_Header
