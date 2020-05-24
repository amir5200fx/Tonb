#pragma once
#ifndef _genericFvPatchVectorNFields_Header
#define _genericFvPatchVectorNFields_Header

#include <genericFvPatchField.hxx>
#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#define doMakeTypedef(type, Type, args)                                \
    typedef genericFvPatchField<type > genericFvPatch##Type##Field;

	forAllVectorNTypes(doMakeTypedef)

		forAllTensorNTypes(doMakeTypedef)

		forAllDiagTensorNTypes(doMakeTypedef)

		forAllSphericalTensorNTypes(doMakeTypedef)

#undef doMakeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_genericFvPatchVectorNFields_Header
