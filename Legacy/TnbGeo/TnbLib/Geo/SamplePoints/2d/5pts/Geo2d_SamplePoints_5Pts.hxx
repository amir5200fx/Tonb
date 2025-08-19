#pragma once
#ifndef _Geo2d_SamplePoints_5Pts_Header
#define _Geo2d_SamplePoints_5Pts_Header

#include <Geo2d_SamplePoints.hxx>

namespace tnbLib
{

	class Geo2d_SamplePoints_5Pts
		: public Geo2d_SamplePoints
	{

		/*Private Data*/

	public:

		static TnbGeo_EXPORT const Standard_Integer nbPts;

		const Pnt2d P0;
		const Pnt2d P1;
		const Pnt2d P2;
		const Pnt2d P3;
		const Pnt2d P4;

		// default constructor [12/26/2021 Amir]

		TnbGeo_EXPORT Geo2d_SamplePoints_5Pts();


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

#endif // !_Geo2d_SamplePoints_5Pts_Header
