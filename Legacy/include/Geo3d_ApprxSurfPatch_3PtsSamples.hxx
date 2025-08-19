#pragma once
#ifndef _Geo3d_ApprxSurfPatch_3PtsSamples_Header
#define _Geo3d_ApprxSurfPatch_3PtsSamples_Header

#include <Geo3d_ApprxSurfPatch_Samples.hxx>

namespace tnbLib
{

	class Geo3d_ApprxSurfPatch_3PtsSamples
		: public Geo3d_ApprxSurfPatch_Samples
	{

		/*private Data*/

	public:

		static TnbMesh_EXPORT const Standard_Real twoPerThree;
		static TnbMesh_EXPORT const Standard_Real onePerSix;

		static TnbMesh_EXPORT const Standard_Integer nbPts;


		// default constructor [9/3/2022 Amir]

		Geo3d_ApprxSurfPatch_3PtsSamples()
		{}

		// constructors [9/3/2022 Amir]


		// public functions and operators [9/3/2022 Amir]

		Standard_Integer NbPoints() const override
		{
			return nbPts;
		}

		TnbMesh_EXPORT Pnt2d 
			CalcPoint
			(
				const Standard_Integer theIndex,
				const Entity_Triangle<const Pnt2d &>&
			) const override;

		TnbMesh_EXPORT std::vector<Pnt2d> 
			RetrieveSamples
			(
				const Entity_Triangle<const Pnt2d &>&
			) const override;
	};
}

#endif // !_Geo3d_ApprxSurfPatch_3PtsSamples_Header
