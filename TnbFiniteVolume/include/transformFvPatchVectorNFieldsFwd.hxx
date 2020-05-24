#pragma once
#ifndef _transformFvPatchVectorNFieldsFwd_Header
#define _transformFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class Type> class transformFvPatchField;

#define makeTypedef(type, Type, args)                                \
    typedef transformFvPatchField<type> transformFvPatch##Type##Field;

	forAllVectorNTypes(makeTypedef)

		forAllTensorNTypes(makeTypedef)

		forAllDiagTensorNTypes(makeTypedef)

		forAllSphericalTensorNTypes(makeTypedef)

#undef makeTypedef

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_transformFvPatchVectorNFieldsFwd_Header
