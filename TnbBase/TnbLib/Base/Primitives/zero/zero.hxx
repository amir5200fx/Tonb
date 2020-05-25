#pragma once
#ifndef _zero_Header
#define _zero_Header

#include <label.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class zero Declaration
	\*---------------------------------------------------------------------------*/

	class zero
	{
	public:

		typedef zero value_type;

		// Constructors

			//- Construct null
		zero()
		{}


		// Member Operators

			//- Return 0 for bool
		inline operator bool() const
		{
			return 0;
		}

		//- Return 0 for label
		inline operator label() const
		{
			return 0;
		}

		//- Return 0 for float
		inline operator float() const
		{
			return 0;
		}

		//- Return 0 for double
		inline operator double() const
		{
			return 0;
		}

		//- Return 0 for double
		inline operator long double() const
		{
			return 0;
		}
	};


	// Global zero
	static const zero Zero;


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <zeroI.hxx>

#endif // !_zero_Header
