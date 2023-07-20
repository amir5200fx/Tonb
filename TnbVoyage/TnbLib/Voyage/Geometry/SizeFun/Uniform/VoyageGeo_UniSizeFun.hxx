#pragma once
#ifndef _VoyageGeo_UniSizeFun_Header
#define _VoyageGeo_UniSizeFun_Header

#include <VoyageGeo_SizeFun.hxx>

namespace tnbLib
{

	class VoyageGeo_UniSizeFun
		: public VoyageGeo_SizeFun
	{

		/*Private Data*/

		Standard_Real theSize_;

	public:

		// default constructor [7/10/2023 Payvand]


		// constructors [7/10/2023 Payvand]

		VoyageGeo_UniSizeFun(const Standard_Real theSize)
			: theSize_(theSize)
		{}

		// Public functions and operators [7/10/2023 Payvand]

		Standard_Real Value(const Pnt2d& theCoord) const override { return theSize_; }

	};

}

#endif // !_VoyageGeo_UniSizeFun_Header
