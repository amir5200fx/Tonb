#pragma once
#ifndef _fvsPatchVectorNFieldsFwd_Header
#define _fvsPatchVectorNFieldsFwd_Header

#include <VectorNFieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class fvsPatchField;

	typedef fvsPatchField<vector2> fvsPatchVector2Field;
	typedef fvsPatchField<vector3> fvsPatchVector3Field;
	typedef fvsPatchField<vector4> fvsPatchVector4Field;
	typedef fvsPatchField<vector6> fvsPatchVector6Field;
	typedef fvsPatchField<vector8> fvsPatchVector8Field;

	typedef fvsPatchField<tensor2> fvsPatchTensor2Field;
	typedef fvsPatchField<tensor3> fvsPatchTensor3Field;
	typedef fvsPatchField<tensor4> fvsPatchTensor4Field;
	typedef fvsPatchField<tensor6> fvsPatchTensor6Field;
	typedef fvsPatchField<tensor8> fvsPatchTensor8Field;

	typedef fvsPatchField<diagTensor2> fvsPatchDiagTensor2Field;
	typedef fvsPatchField<diagTensor3> fvsPatchDiagTensor3Field;
	typedef fvsPatchField<diagTensor4> fvsPatchDiagTensor4Field;
	typedef fvsPatchField<diagTensor6> fvsPatchDiagTensor6Field;
	typedef fvsPatchField<diagTensor8> fvsPatchDiagTensor8Field;

	typedef fvsPatchField<sphericalTensor2> fvsPatchSphericalTensor2Field;
	typedef fvsPatchField<sphericalTensor3> fvsPatchSphericalTensor3Field;
	typedef fvsPatchField<sphericalTensor4> fvsPatchSphericalTensor4Field;
	typedef fvsPatchField<sphericalTensor6> fvsPatchSphericalTensor6Field;
	typedef fvsPatchField<sphericalTensor8> fvsPatchSphericalTensor8Field;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fvsPatchVectorNFieldsFwd_Header
