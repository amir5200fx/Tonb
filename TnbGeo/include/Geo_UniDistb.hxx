#pragma once
#ifndef _Geo_UniDistb_Header
#define _Geo_UniDistb_Header

#include <Geo_xDistb.hxx>
#include <Geo_Module.hxx>

namespace tnbLib
{

	class Geo_UniDistb
		: public Geo_xDistb
	{

		/*Private Data*/

		Standard_Integer theSize_;


	public:

		Geo_UniDistb(const Standard_Integer theSize)
			: theSize_(theSize)
		{}

		TnbGeo_EXPORT void Perform();


	};
}

#endif // !_Geo_UniDistb_Header
