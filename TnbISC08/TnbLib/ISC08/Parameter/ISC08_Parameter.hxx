#pragma once
#ifndef _ISC08_Parameter_Header
#define _ISC08_Parameter_Header

#include <Marine_DimensionedParam.hxx>

namespace tnbLib
{

	class ISC08_Parameter
		: public Marine_DimensionedParam<Standard_Real>
	{

		/*Private Data*/

	protected:

		ISC08_Parameter
		(
			const word& theName,
			const dimensionSet& theDim,
			const Standard_Real theValue
		)
			: Marine_DimensionedParam<Standard_Real>(theName, theDim, theValue)
		{}

	public:


	};
}

#include <ISC08_Parameters.hxx>

#endif // !_ISC08_Parameter_Header
