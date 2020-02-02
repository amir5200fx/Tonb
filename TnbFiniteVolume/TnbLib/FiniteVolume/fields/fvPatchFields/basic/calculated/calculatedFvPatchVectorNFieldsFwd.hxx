#pragma once
#ifndef _calculatedFvPatchVectorNFieldsFwd_Header
#define _calculatedFvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class calculatedFvPatchField;

#define makeTypedef(type, Type, args)                                    \
    typedef calculatedFvPatchField<type> calculatedFvPatch##Type##Field;

	typedef calculatedFvPatchField<vector2> calculatedFvPatchVector2Field;
	typedef calculatedFvPatchField<vector3> calculatedFvPatchVector3Field;
	typedef calculatedFvPatchField<vector4> calculatedFvPatchVector4Field;
	typedef calculatedFvPatchField<vector6> calculatedFvPatchVector6Field;
	typedef calculatedFvPatchField<vector8> calculatedFvPatchVector8Field;

		
	typedef calculatedFvPatchField<tensor2> calculatedFvPatchTensor2Field;
	typedef calculatedFvPatchField<tensor3> calculatedFvPatchTensor3Field;
	typedef calculatedFvPatchField<tensor4> calculatedFvPatchTensor4Field;
	typedef calculatedFvPatchField<tensor6> calculatedFvPatchTensor6Field;
	typedef calculatedFvPatchField<tensor8> calculatedFvPatchTensor8Field;

		
	typedef calculatedFvPatchField<diagTensor2> calculatedFvPatchDiagTensor2Field;
	typedef calculatedFvPatchField<diagTensor3> calculatedFvPatchDiagTensor3Field;
	typedef calculatedFvPatchField<diagTensor4> calculatedFvPatchDiagTensor4Field;
	typedef calculatedFvPatchField<diagTensor6> calculatedFvPatchDiagTensor6Field;
	typedef calculatedFvPatchField<diagTensor8> calculatedFvPatchDiagTensor8Field;

		
	typedef calculatedFvPatchField<sphericalTensor2> calculatedFvPatchSphericalTensor2Field;
	typedef calculatedFvPatchField<sphericalTensor3> calculatedFvPatchSphericalTensor3Field;
	typedef calculatedFvPatchField<sphericalTensor4> calculatedFvPatchSphericalTensor4Field;
	typedef calculatedFvPatchField<sphericalTensor6> calculatedFvPatchSphericalTensor6Field;
	typedef calculatedFvPatchField<sphericalTensor8> calculatedFvPatchSphericalTensor8Field;

#undef makeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif
