#pragma once
#ifndef _STLpoint_Header
#define _STLpoint_Header

#include <point.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class STLpoint Declaration
	\*---------------------------------------------------------------------------*/

	class STLpoint
		: public Vector<float>
	{

	public:

		// Constructors

			//- Construct null
		inline STLpoint();

		//- Construct from components
		inline STLpoint(float x, float y, float z);

		//- Construct from point
		inline STLpoint(const point&);

		//- Construct from istream
		inline STLpoint(Istream&);


		// Member Operators

		inline operator point() const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <STLpointI.hxx>

#endif // !_STLpoint_Header
