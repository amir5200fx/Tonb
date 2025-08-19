#pragma once
#ifndef _Airfoil_Tools_Header
#define _Airfoil_Tools_Header

#include <Airfoil_Module.hxx>
#include <Geo_xDistb.hxx>
#include <Dir2d.hxx>
#include <Pnt2d.hxx>
#include <Standard_TypeDef.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{

	// Forward Declarations [4/25/2023 Payvand]
	class Pln_Curve;
	
	class Airfoil_Tools
	{

	public:

		static TnbAirfoil_EXPORT std::vector<Standard_Real> 
			CalcSpans(const std::vector<std::shared_ptr<Pln_Curve>>&);

		static TnbAirfoil_EXPORT std::shared_ptr<Pln_Curve> 
			RetrieveCurve
			(
				const Standard_Real x,
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const std::vector<Standard_Real>& theSpans
			);

		// the first is value and the second is parameter of the profile [4/26/2023 Payvand]
		static TnbAirfoil_EXPORT std::pair<Standard_Real, Standard_Real>
			xValue
			(
				const Standard_Real x,
				const std::shared_ptr<Pln_Curve>&
			);



		static TnbAirfoil_EXPORT std::pair<Standard_Real, Standard_Real> 
			xValue
			(
				const Standard_Real x, 
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
				const std::vector<Standard_Real>& theSpans
			);

		// the first real list is xs and the second one is ys [4/25/2023 Payvand]
		static TnbAirfoil_EXPORT std::tuple
			<
			std::vector<Standard_Real>, 
			std::vector<Standard_Real>, 
			std::vector<Dir2d>
			>
			CalcCamberPoints
			(
				const Geo_xDistb&,
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
				const std::vector<Standard_Real>& theSpans
			);

		// the first real list is xs and the second one is ys [4/25/2023 Payvand]
		static TnbAirfoil_EXPORT std::vector<Standard_Real>
			CalcThicknessPoints
			(
				const Geo_xDistb&, 
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
				const std::vector<Standard_Real>& theSpans
			);

		static TnbAirfoil_EXPORT std::vector<Pnt2d>
			CalcUpperOffsets
			(
				const std::vector<Standard_Real>& theXs,
				const std::vector<Standard_Real>& theYs,
				const std::vector<Standard_Real>& theThick, 
				const std::vector<Dir2d>& theTan
			);

		static TnbAirfoil_EXPORT std::vector<Pnt2d>
			CalcLowerOffsets
			(
				const std::vector<Standard_Real>& theXs,
				const std::vector<Standard_Real>& theYs,
				const std::vector<Standard_Real>& theThick,
				const std::vector<Dir2d>& theTan
			);
	};
}

#endif // !_Airfoil_Tools_Header
