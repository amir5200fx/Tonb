#pragma once
#ifndef _helperFunctionsStringConversion_Header
#define _helperFunctionsStringConversion_Header

#include <word.hxx>
#include <label.hxx>
#include <scalar.hxx>

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Namespace help functions Declaration
	\*---------------------------------------------------------------------------*/

	namespace help
	{

		//- convert the text to scalar
		scalar textToScalar(const word& w);

		//- convert the text to label
		label textToLabel(const word& w);

		//- convert the scalar value into text
		word scalarToText(const scalar s);

		//- convert the integer value into text
		word labelToText(const label l);

	} // End namespace help

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_helperFunctionsStringConversion_Header
