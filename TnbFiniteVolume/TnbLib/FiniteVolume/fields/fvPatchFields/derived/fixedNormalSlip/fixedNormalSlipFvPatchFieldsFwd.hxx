#pragma once
#ifndef _fixedNormalSlipFvPatchFieldsFwd_Header
#define _fixedNormalSlipFvPatchFieldsFwd_Header

#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class fixedNormalSlipFvPatchField;

	typedef fixedNormalSlipFvPatchField<vector> fixedNormalSlipFvPatchVectorField;
	typedef fixedNormalSlipFvPatchField<tensor> fixedNormalSlipFvPatchTensorField;

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_fixedNormalSlipFvPatchFieldsFwd_Header
