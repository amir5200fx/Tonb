#pragma once
#ifndef _wedgeFvsPatchVectorNFieldsFwd_Header
#define _wedgeFvsPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class wedgeFvsPatchField;

#define doMakeTypedef(type, Type, args)                                  \
    typedef wedgeFvsPatchField<type > wedgeFvsPatch##Type##Field;

	forAllVectorNTypes(doMakeTypedef)

		forAllTensorNTypes(doMakeTypedef)

		forAllDiagTensorNTypes(doMakeTypedef)

		forAllSphericalTensorNTypes(doMakeTypedef)

#undef doMakeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvsPatchVectorNFieldsFwd_Header
