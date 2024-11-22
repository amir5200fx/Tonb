#pragma once
#ifndef _Geo2d_TriangleQualityTools_Header
#define _Geo2d_TriangleQualityTools_Header

#include <Geo_Module.hxx>
#include <Global_TypeDef.hxx>

namespace tnbLib
{

	// Forward Declarations [9/18/2022 Amir]
	class Pnt2d;

	class Geo2d_TriangleQualityTools
	{

		/*Private Data*/

	public:

		static TnbGeo_EXPORT Standard_Real Vlrms2Ratio(const Pnt2d& theP0, const Pnt2d& theP1, const Pnt2d& theP2);
	};
}

#endif // !_Geo2d_TriangleQualityTools_Header
