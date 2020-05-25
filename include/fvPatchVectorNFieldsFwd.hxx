#pragma once
#ifndef _fvPatchVectorNFieldsFwd_Header
#define _fvPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class fvPatchField;

#define doMakeTypedef(type, Type, args)                      \
    typedef fvPatchField<type > fvPatch##Type##Field;

	typedef fvPatchField<vector2> fvPatchVector2Field;
	typedef fvPatchField<vector3> fvPatchVector3Field;
	typedef fvPatchField<vector4> fvPatchVector4Field;
	typedef fvPatchField<vector6> fvPatchVector6Field;
	typedef fvPatchField<vector8> fvPatchVector8Field;

		
	typedef fvPatchField<tensor2> fvPatchTensor2Field;
	typedef fvPatchField<tensor3> fvPatchTensor3Field;
	typedef fvPatchField<tensor4> fvPatchTensor4Field;
	typedef fvPatchField<tensor6> fvPatchTensor6Field;
	typedef fvPatchField<tensor8> fvPatchTensor8Field;

		
	typedef fvPatchField<diagTensor2> fvPatchDiagTensor2Field;
	typedef fvPatchField<diagTensor3> fvPatchDiagTensor3Field;
	typedef fvPatchField<diagTensor4> fvPatchDiagTensor4Field;
	typedef fvPatchField<diagTensor6> fvPatchDiagTensor6Field;
	typedef fvPatchField<diagTensor8> fvPatchDiagTensor8Field;

		
	typedef fvPatchField<sphericalTensor2> fvPatchSphericalTensor2Field;
	typedef fvPatchField<sphericalTensor3> fvPatchSphericalTensor3Field;
	typedef fvPatchField<sphericalTensor4> fvPatchSphericalTensor4Field;
	typedef fvPatchField<sphericalTensor6> fvPatchSphericalTensor6Field;
	typedef fvPatchField<sphericalTensor8> fvPatchSphericalTensor8Field;

#undef doMakeTypedef

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvPatchVectorNFieldsFwd_Header
