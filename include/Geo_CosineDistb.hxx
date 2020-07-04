#pragma once
#ifndef _Geo_CosineDistb_Header
#define _Geo_CosineDistb_Header

#include <Geo_xDistb.hxx>

namespace tnbLib
{

	class Geo_CosineDistb
		: public Geo_xDistb
	{

		/*Private Data*/

		Standard_Integer theSize_;

	public:

		Geo_CosineDistb(const Standard_Integer theSize)
			: theSize_(theSize)
		{}

		void Perform();
	};
}

#endif // !_Geo_CosineDistb_Header
