#pragma once
#ifndef _emptyFvsPatchVectorNFieldsFwd_Header
#define _emptyFvsPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class emptyFvsPatchField;

#define doMakeTypedef(type, Type, args)                                  \
    typedef emptyFvsPatchField<type > emptyFvsPatch##Type##Field;

	forAllVectorNTypes(doMakeTypedef)

		forAllTensorNTypes(doMakeTypedef)

		forAllDiagTensorNTypes(doMakeTypedef)

		forAllSphericalTensorNTypes(doMakeTypedef)

#undef doMakeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_emptyFvsPatchVectorNFieldsFwd_Header
