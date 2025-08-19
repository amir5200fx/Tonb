#pragma once
#ifndef _Geo3d_AirfoilSectionFwd_Header
#define _Geo3d_AirfoilSectionFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/29/2022 Amir]
	template<class Point>
	class Geo_AirfoilSection;

	class Pnt3d;

	typedef Geo_AirfoilSection<Pnt3d> Geo3d_AirfoilSection;
}

#endif // !_Geo3d_AirfoilSectionFwd_Header
