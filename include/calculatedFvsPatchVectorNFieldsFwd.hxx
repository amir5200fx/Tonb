#pragma once
#ifndef _calculatedFvsPatchVectorNFieldsFwd_Header
#define _calculatedFvsPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class calculatedFvsPatchField;

#define doMakeTypedef(type, Type, args)                                  \
    typedef calculatedFvsPatchField<type > calculatedFvsPatch##Type##Field;

	typedef calculatedFvsPatchField<vector2> calculatedFvsPatchVector2Field;
	typedef calculatedFvsPatchField<vector3> calculatedFvsPatchVector3Field;
	typedef calculatedFvsPatchField<vector4> calculatedFvsPatchVector4Field;
	typedef calculatedFvsPatchField<vector6> calculatedFvsPatchVector6Field;
	typedef calculatedFvsPatchField<vector8> calculatedFvsPatchVector8Field;

		
	typedef calculatedFvsPatchField<tensor2> calculatedFvsPatchTensor2Field;
	typedef calculatedFvsPatchField<tensor3> calculatedFvsPatchTensor3Field;
	typedef calculatedFvsPatchField<tensor4> calculatedFvsPatchTensor4Field;
	typedef calculatedFvsPatchField<tensor6> calculatedFvsPatchTensor6Field;
	typedef calculatedFvsPatchField<tensor8> calculatedFvsPatchTensor8Field;

		
	typedef calculatedFvsPatchField<diagTensor2> calculatedFvsPatchDiagTensor2Field;
	typedef calculatedFvsPatchField<diagTensor3> calculatedFvsPatchDiagTensor3Field;
	typedef calculatedFvsPatchField<diagTensor4> calculatedFvsPatchDiagTensor4Field;
	typedef calculatedFvsPatchField<diagTensor6> calculatedFvsPatchDiagTensor6Field;
	typedef calculatedFvsPatchField<diagTensor8> calculatedFvsPatchDiagTensor8Field;

		
	typedef calculatedFvsPatchField<sphericalTensor2> calculatedFvsPatchSphericalTensor2Field;
	typedef calculatedFvsPatchField<sphericalTensor3> calculatedFvsPatchSphericalTensor3Field;
	typedef calculatedFvsPatchField<sphericalTensor4> calculatedFvsPatchSphericalTensor4Field;
	typedef calculatedFvsPatchField<sphericalTensor6> calculatedFvsPatchSphericalTensor6Field;
	typedef calculatedFvsPatchField<sphericalTensor8> calculatedFvsPatchSphericalTensor8Field;

#undef doMakeTypedef


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_calculatedFvsPatchVectorNFieldsFwd_Header
