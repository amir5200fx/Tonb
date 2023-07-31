#pragma once
#ifndef _VoyageGeo_GreateCircleNav_Header
#define _VoyageGeo_GreateCircleNav_Header

#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class VoyageGeo_GreateCircleNav
	{

		/*Private Data*/

		Pnt2d theP1_;
		Pnt2d theP2_;

		Standard_Real theAlpha0_;
		Standard_Real theAlpha1_;
		Standard_Real theAlpha2_;

		Standard_Real theSigma01_;
		Standard_Real theSigma02_;
		Standard_Real theSigma12_;

		Standard_Real theLanda01_;

		TnbVoyage_EXPORT void Init();

	public:

		// Default constructor [7/28/2023 Payvand]

		// constructors [7/28/2023 Payvand]

		VoyageGeo_GreateCircleNav(const Pnt2d& theP1, const Pnt2d& theP2)
			: theP1_(theP1)
			, theP2_(theP2)
		{
			Init();
		}



		// Public functions and operators [7/28/2023 Payvand]

		const auto& P1() const { return theP1_; }
		const auto& P2() const { return theP2_; }

		TnbVoyage_EXPORT Standard_Real Phi1() const;
		TnbVoyage_EXPORT Standard_Real Phi2() const;
		TnbVoyage_EXPORT Standard_Real Landa1() const;
		TnbVoyage_EXPORT Standard_Real Landa2() const;

		auto Sigma1() const { return theSigma01_; }
		auto Sigma2() const { return theSigma02_; }

		TnbVoyage_EXPORT Pnt2d CalcWayPoint(const Standard_Real theSigma) const;
		TnbVoyage_EXPORT std::vector<Pnt2d> CalcWayPoints(const std::vector<Standard_Real>&) const;

	};
}

#endif // !_VoyageGeo_GreateCircleNav_Header
