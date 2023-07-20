#pragma once
#ifndef _VoyageGeo_SizeFun_Header
#define _VoyageGeo_SizeFun_Header

#include <Pnt2d.hxx>

namespace tnbLib
{

	class VoyageGeo_SizeFun
	{

		/*Private Data*/

	protected:

		// default constructor [7/10/2023 Payvand]

		VoyageGeo_SizeFun()
		{}

		// constructors [7/10/2023 Payvand]

	public:


		// Public functions  [7/10/2023 Payvand]

		virtual Standard_Real Value(const Pnt2d& theCoord) const = 0;

	};

}

#endif // !_VoyageGeo_SizeFun_Header

