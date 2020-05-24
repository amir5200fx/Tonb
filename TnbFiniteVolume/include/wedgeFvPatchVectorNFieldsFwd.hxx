#pragma once
#ifndef _wedgeFvPatchVectorNFieldsFwd_Header
#define _wedgeFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class wedgeFvPatchField;

#define makeTypedef(type, Type, args)                                \
    typedef wedgeFvPatchField<type> wedgeFvPatch##Type##Field;

	forAllVectorNTypes(makeTypedef)

		forAllTensorNTypes(makeTypedef)

		forAllDiagTensorNTypes(makeTypedef)

		forAllSphericalTensorNTypes(makeTypedef)

#undef makeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_wedgeFvPatchVectorNFieldsFwd_Header
