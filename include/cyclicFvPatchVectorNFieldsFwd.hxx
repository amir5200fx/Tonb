#pragma once
#ifndef _cyclicFvPatchVectorNFieldsFwd_Header
#define _cyclicFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class cyclicFvPatchField;

#define makeTypedef(type, Type, args)                                \
    typedef cyclicFvPatchField<type> cyclicFvPatch##Type##Field;

	typedef cyclicFvPatchField<vector2> cyclicFvPatchVector2Field;
	typedef cyclicFvPatchField<vector3> cyclicFvPatchVector3Field;
	typedef cyclicFvPatchField<vector4> cyclicFvPatchVector4Field;
	typedef cyclicFvPatchField<vector6> cyclicFvPatchVector6Field;
	typedef cyclicFvPatchField<vector8> cyclicFvPatchVector8Field;

#undef makeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cyclicFvPatchVectorNFieldsFwd_Header
