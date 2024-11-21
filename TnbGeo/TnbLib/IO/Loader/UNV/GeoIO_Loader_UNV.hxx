#pragma once
#ifndef _GeoIO_Loader_UNV_Header
#define _GeoIO_Loader_UNV_Header

#include <Global_TypeDef.hxx>
#include <OFstream.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [9/4/2023 aamir]
	class GeoIO_UNVElement;
	class GeoIO_UNVPoint;

	class GeoIO_Loader_UNV
	{

		/*Private Data*/


		// Private Functions and operators [9/4/2023 aamir]

		void ReadHeader();
		void Read2411(OFstream&);  // Read the coordinates [9/4/2023 aamir]
		void Read2412();
		void Read2467();

	public:

		// default constructor [9/4/2023 aamir]

		GeoIO_Loader_UNV()
		{}

		// constructors [9/4/2023 aamir]

		// Public functions and operators [9/4/2023 aamir]

		

	};
}

#endif // !_GeoIO_Loader_UNV_Header
