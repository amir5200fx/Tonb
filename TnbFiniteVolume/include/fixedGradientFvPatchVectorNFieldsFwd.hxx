#pragma once
#ifndef _fixedGradientFvPatchVectorNFieldsFwd_Header
#define _fixedGradientFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class fixedGradientFvPatchField;

#define makeTypedef(type, Type, args)                                \
    typedef fixedGradientFvPatchField<type> fixedGradientFvPatch##Type##Field;

	forAllVectorNTypes(makeTypedef)

		forAllTensorNTypes(makeTypedef)

		forAllDiagTensorNTypes(makeTypedef)

		forAllSphericalTensorNTypes(makeTypedef)

#undef makeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedGradientFvPatchVectorNFieldsFwd_Header
