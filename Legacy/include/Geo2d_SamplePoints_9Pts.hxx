#pragma once
#ifndef _Geo2d_SamplePoints_9Pts_Header
#define _Geo2d_SamplePoints_9Pts_Header

#include <Geo2d_SamplePoints.hxx>

namespace tnbLib
{

	class Geo2d_SamplePoints_9Pts
		: public Geo2d_SamplePoints
	{

		/*Private Data*/


	public:

		static TnbGeo_EXPORT const Standard_Integer nbPts;

		static TnbGeo_EXPORT const Pnt2d P0;
		static TnbGeo_EXPORT const Pnt2d P1;
		static TnbGeo_EXPORT const Pnt2d P2;
		static TnbGeo_EXPORT const Pnt2d P3;
		static TnbGeo_EXPORT const Pnt2d P4;
		static TnbGeo_EXPORT const Pnt2d P5;
		static TnbGeo_EXPORT const Pnt2d P6;
		static TnbGeo_EXPORT const Pnt2d P7;
		static TnbGeo_EXPORT const Pnt2d P8;

		// default constructor [12/26/2021 Amir]

		Geo2d_SamplePoints_9Pts()
		{}

		// constructors [12/26/2021 Amir]


		// public functions and operators [12/26/2021 Amir]

		Standard_Integer NbPoints() const override
		{
			return nbPts;
		}

		TnbGeo_EXPORT Pnt2d CalcPoint
		(
			const Standard_Integer theIndex,
			const Entity2d_Box&
		) const override;

		TnbGeo_EXPORT std::vector<Pnt2d> RetrieveSamples() const override;
	};
}

#endif // !_Geo2d_SamplePoints_9Pts_Header
