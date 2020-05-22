#pragma once
#ifndef _timeVaryingUniformInletOutletFvPatchFieldsFwd_Header
#define _timeVaryingUniformInletOutletFvPatchFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class timeVaryingUniformInletOutletFvPatchField;

	makePatchTypeFieldTypedefs(timeVaryingUniformInletOutlet);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_timeVaryingUniformInletOutletFvPatchFieldsFwd_Header
