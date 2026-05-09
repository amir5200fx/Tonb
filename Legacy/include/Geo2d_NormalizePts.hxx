#pragma once
#ifndef _Geo2d_NormalizePts_Header
#define _Geo2d_NormalizePts_Header

#include <Geo_NormalizePts.hxx>
#include <Geo2d_NormalizePtsFwd.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT void Geo2d_NormalizePts::Perform();
}

#endif // !_Geo2d_NormalizePts_Header
