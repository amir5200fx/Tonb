#pragma once
#ifndef _STLtriangle_Header
#define _STLtriangle_Header

#include <STLpoint.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class STLtriangle Declaration
	\*---------------------------------------------------------------------------*/

	class STLtriangle
	{
		// Private data

		STLpoint normal_, a_, b_, c_;
		unsigned short region_;


	public:

		// Constructors

			//- Construct null
		inline STLtriangle();

		//- Construct from components
		inline STLtriangle
		(
			const STLpoint& normal,
			const STLpoint& a,
			const STLpoint& b,
			const STLpoint& c,
			unsigned short region
		);

		//- Construct from istream (read binary)
		inline STLtriangle(istream&);


		// Member Functions

			// Access

		inline const STLpoint& a() const;
		inline const STLpoint& b() const;
		inline const STLpoint& c() const;
		inline unsigned short region() const;

		// Read

			//- Read from istream (binary)
		inline void read(istream&);

		// Write

			//- Write to istream (binary)
		inline void write(ostream&);


		// Ostream operator

		inline friend Ostream& operator<<(Ostream&, const STLtriangle&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <STLtriangleI.hxx>

#endif // !_STLtriangle_Header
