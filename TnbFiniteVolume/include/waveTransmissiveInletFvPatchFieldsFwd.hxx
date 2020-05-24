#pragma once
#ifndef _waveTransmissiveInletFvPatchFieldsFwd_Header
#define _waveTransmissiveInletFvPatchFieldsFwd_Header

#include <fvPatchField.hxx>
#include <fieldTypes.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class Type> class waveTransmissiveInletFvPatchField;

	makePatchTypeFieldTypedefs(waveTransmissiveInlet)

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_waveTransmissiveInletFvPatchFieldsFwd_Header
