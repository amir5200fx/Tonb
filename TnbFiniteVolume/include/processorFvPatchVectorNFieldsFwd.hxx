#pragma once
#ifndef _processorFvPatchVectorNFieldsFwd_Header
#define _processorFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class processorFvPatchField;

#define makeTypedef(type, Type, args)                                \
    typedef processorFvPatchField<type> processorFvPatch##Type##Field;

	forAllVectorNTypes(makeTypedef)

#undef makeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_processorFvPatchVectorNFieldsFwd_Header
