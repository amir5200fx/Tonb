#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
	\\  /    A nd           | Web:         http://www.foam-extend.org
	 \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
	This file is part of foam-extend.

	foam-extend is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation, either version 3 of the License, or (at your
	option) any later version.

	foam-extend is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::OSHA1stream

Description
	An output stream for calculating SHA1 digests.

SourceFiles
	OSHA1stream.C

\*---------------------------------------------------------------------------*/
#ifndef _OSHA1stream_Header
#define _OSHA1stream_Header

#include <OSstream.hxx>
#include <SHA1.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	class osha1stream;
	class OSHA1stream;

	/*---------------------------------------------------------------------------*\
							Class sha1streambuf Declaration
	\*---------------------------------------------------------------------------*/

	//- A streambuf class for calculating SHA1 digests
	class sha1streambuf
		:
		public std::streambuf
	{
		// Private data

		//- This does all the work and has its own buffering
		SHA1 sha1_;

		friend class osha1stream;

	public:

		// Constructors

			//- Construct null
		sha1streambuf()
		{}

		// Member Functions

		// Write

			//- Process unbuffered
		virtual std::streamsize xsputn(const char* str, std::streamsize n)
		{
			sha1_.append(str, n);
			return n;
		}
	};


	/*---------------------------------------------------------------------------*\
							 Class osha1stream Declaration
	\*---------------------------------------------------------------------------*/

	//- A basic output stream for calculating SHA1 digests
	class osha1stream
		:
		virtual public std::ios,
		public std::ostream
	{
		// Private data

		sha1streambuf sbuf_;

	public:

		// Constructors

			//- Construct null
		osha1stream()
			:
			std::ostream(&sbuf_)
		{}

		// Member Functions

		// Access

			//- This hides both signatures of std::basic_ios::rdbuf()
		sha1streambuf* rdbuf()
		{
			return &sbuf_;
		}

		//- Full access to the sha1
		SHA1& sha1()
		{
			return sbuf_.sha1_;
		}

	};


	/*---------------------------------------------------------------------------*\
							 Class OSHA1stream Declaration
	\*---------------------------------------------------------------------------*/

	//- The output stream for calculating SHA1 digests
	class OSHA1stream
		: public OSstream
	{

		// Private Member Functions

			//- Disallow default bitwise copy construct
		OSHA1stream(const OSHA1stream&);

		//- Disallow default bitwise assignment
		void operator=(const OSHA1stream&);

	public:

		// Constructors

			//- Construct and set stream status
		OSHA1stream
		(
			streamFormat format = ASCII,
			versionNumber version = currentVersion
		)
			:
			OSstream
			(
				*(new osha1stream),
				"OSHA1stream.sinkFile_",
				format,
				version
			)
		{}


		// Destructor

		~OSHA1stream()
		{
			delete &dynamic_cast<osha1stream&>(stream());
		}


		// Member functions

		// Access

			//- Full access to the sha1
		tnbLib::SHA1& sha1()
		{
			return dynamic_cast<osha1stream&>(stream()).sha1();
		}

		//- Return SHA1::Digest for the data processed until now
		tnbLib::SHA1Digest digest()
		{
			return sha1().digest();
		}

		// Edit

			//- Clear the SHA1 calculation
		void rewind()
		{
			sha1().clear();
		}

	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_OSHA1stream_Header
