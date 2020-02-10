#pragma once
#ifndef _emptyFvPatchVectorNFieldsFwd_Header
#define _emptyFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class emptyFvPatchField;

#define makeTypedef(type, Type, args)                                \
    typedef emptyFvPatchField<type> emptyFvPatch##Type##Field;

	forAllVectorNTypes(makeTypedef)

		forAllTensorNTypes(makeTypedef)

		forAllDiagTensorNTypes(makeTypedef)

		forAllSphericalTensorNTypes(makeTypedef)

#undef makeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyFvPatchVectorNFieldsFwd_Header
