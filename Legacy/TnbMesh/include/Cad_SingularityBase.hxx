#pragma once
#ifndef _Cad_SingularityBase_Header
#define _Cad_SingularityBase_Header

#include <Entity2d_BoxFwd.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Global_TypeDef.hxx>

class Geom_Surface;

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class CurveType>
	class Cad_SingularityBase
	{

		/*Private Data*/

	protected:

		// default constructor [3/29/2022 Amir]

		Cad_SingularityBase()
		{}


		// static functions and operators [3/29/2022 Amir]

		static std::shared_ptr<CurveType> ParametricCurve_Pole(const Pnt2d& theP0, const Pnt2d& theP1);

		static std::shared_ptr<CurveType> ParametricCurve_Line(const Pnt2d& theP0, const Pnt2d& theP1);

		static std::vector<std::shared_ptr<CurveType>>
			LineHorizonCurves_Dangle
			(
				const Entity2d_Box& theBox,
				const Standard_Integer s0
			);

		static std::vector<std::shared_ptr<CurveType>>
			LineHorizonCurves_Corner
			(
				const Entity2d_Box& theBox,
				const Standard_Integer s0,
				const Geom_Surface& theSurface,
				const Standard_Real theTol
			);

		static std::vector<std::shared_ptr<CurveType>>
			LineHorizonCurves_WholeSide
			(
				const Entity2d_Box& theBox,
				const Standard_Integer s0
			);

		static std::vector<std::shared_ptr<CurveType>>
			LineHorizonCurves_Loop
			(
				const Entity2d_Box& theBox
			);

		static std::vector<std::shared_ptr<CurveType>>
			LineHorizonCurves_TwoSided
			(
				const Entity2d_Box& theBox,
				const Standard_Integer s0
			);
	};
}

#include <Cad_SingularityBaseI.hxx>

#endif // !_Cad_SingularityBase_Header
