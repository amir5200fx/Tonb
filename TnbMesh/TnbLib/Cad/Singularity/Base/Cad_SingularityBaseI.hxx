#pragma once
#include <Cad_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class CurveType>
	inline std::vector<std::shared_ptr<CurveType>> 
		Cad_SingularityBase<CurveType>::LineHorizonCurves_Dangle
		(
			const Entity2d_Box & theBox, 
			const Standard_Integer s0
		)
	{
		const auto& p0 = theBox.P0();
		const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
		const auto& p2 = theBox.P1();
		const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

		std::vector<std::shared_ptr<CurveType>> curves;
		curves.reserve(3);

		if (s0 IS_EQUAL 1)
		{
			curves.push_back(ParametricCurve_Line(p0, p3));
			curves.push_back(ParametricCurve_Pole(p3, p2));
			curves.push_back(ParametricCurve_Line(p2, p1));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 2)
		{
			curves.push_back(ParametricCurve_Line(p1, p0));
			curves.push_back(ParametricCurve_Pole(p0, p3));
			curves.push_back(ParametricCurve_Line(p3, p2));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 3)
		{
			curves.push_back(ParametricCurve_Line(p2, p1));
			curves.push_back(ParametricCurve_Pole(p1, p0));
			curves.push_back(ParametricCurve_Line(p0, p3));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 4)
		{
			curves.push_back(ParametricCurve_Line(p3, p2));
			curves.push_back(ParametricCurve_Pole(p2, p1));
			curves.push_back(ParametricCurve_Line(p1, p0));

			return std::move(curves);
		}

		FatalErrorIn(FunctionSIG)
			<< "unspecified situation has been detected!" << endl
			<< abort(FatalError);
		return curves;
	}

	template<class CurveType>
	inline std::vector<std::shared_ptr<CurveType>> 
		Cad_SingularityBase<CurveType>::LineHorizonCurves_Corner
		(
			const Entity2d_Box & theBox,
			const Standard_Integer s0, 
			const Geom_Surface & theSurface, 
			const Standard_Real theTol
		)
	{
		const auto& p0 = theBox.P0();
		const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
		const auto& p2 = theBox.P1();
		const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

		std::vector<std::shared_ptr<CurveType>> curves;
		curves.reserve(2);
		if (s0 IS_EQUAL 1)
		{
			const auto d0 = Cad_Tools::CalcSegmentLength(p3, p2, theSurface);
			const auto d1 = Cad_Tools::CalcSegmentLength(p0, p3, theSurface);

			if (d0 <= tol AND d1 <= tol)
			{
				FatalErrorIn(FunctionSIG)
					<< abort(FatalError);
			}

			if (d0 <= tol)
			{
				curves.push_back(ParametricCurve_Pole(p3, p2));
				curves.push_back(ParametricCurve_Line(p0, p3));
			}
			else
			{
				curves.push_back(ParametricCurve_Line(p3, p2));
				curves.push_back(ParametricCurve_Pole(p0, p3));
			}

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 2)
		{
			const auto d0 = Cad_Tools::CalcSegmentLength(p1, p0, theSurface);
			const auto d1 = Cad_Tools::CalcSegmentLength(p0, p3, theSurface);

			if (d0 <= tol AND d1 <= tol)
			{
				FatalErrorIn(FunctionSIG)
					<< abort(FatalError);
			}

			if (d0 <= tol)
			{
				curves.push_back(ParametricCurve_Pole(p1, p0));
				curves.push_back(ParametricCurve_Line(p0, p3));
			}
			else
			{
				curves.push_back(ParametricCurve_Line(p1, p0));
				curves.push_back(ParametricCurve_Pole(p0, p3));
			}

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 3)
		{
			const auto d0 = Cad_Tools::CalcSegmentLength(p2, p1, theSurface);
			const auto d1 = Cad_Tools::CalcSegmentLength(p1, p0, theSurface);

			if (d0 <= tol AND d1 <= tol)
			{
				FatalErrorIn(FunctionSIG)
					<< abort(FatalError);
			}

			if (d0 <= tol)
			{
				curves.push_back(ParametricCurve_Pole(p2, p1));
				curves.push_back(ParametricCurve_Line(p1, p0));
			}
			else
			{
				curves.push_back(ParametricCurve_Line(p2, p1));
				curves.push_back(ParametricCurve_Pole(p1, p0));
			}

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 4)
		{
			const auto d0 = Cad_Tools::CalcSegmentLength(p3, p2, theSurface);
			const auto d1 = Cad_Tools::CalcSegmentLength(p2, p1, theSurface);

			if (d0 <= tol AND d1 <= tol)
			{
				FatalErrorIn(FunctionSIG)
					<< abort(FatalError);
			}

			if (d0 <= tol)
			{
				curves.push_back(ParametricCurve_Pole(p3, p2));
				curves.push_back(ParametricCurve_Line(p2, p1));
			}
			else
			{
				curves.push_back(ParametricCurve_Line(p3, p2));
				curves.push_back(ParametricCurve_Pole(p2, p1));
			}

			return std::move(curves);
		}
		FatalErrorIn(FunctionSIG)
			<< abort(FatalError);
		return std::move(curves);
	}

	template<class CurveType>
	inline std::vector<std::shared_ptr<CurveType>> 
		Cad_SingularityBase<CurveType>::LineHorizonCurves_WholeSide
		(
			const Entity2d_Box & theBox, 
			const Standard_Integer s0
		)
	{
		const auto& p0 = theBox.P0();
		const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
		const auto& p2 = theBox.P1();
		const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

		std::vector<std::shared_ptr<CurveType>> curves;
		curves.reserve(1);

		if (s0 IS_EQUAL 1)
		{
			curves.push_back(ParametricCurve_Line(p0, p3));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 2)
		{
			curves.push_back(ParametricCurve_Line(p1, p0));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 3)
		{
			curves.push_back(ParametricCurve_Line(p2, p1));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 4)
		{
			curves.push_back(ParametricCurve_Line(p3, p2));

			return std::move(curves);
		}

		FatalErrorIn(FunctionSIG)
			<< abort(FatalError);
		return std::move(curves);
	}

	template<class CurveType>
	inline std::vector<std::shared_ptr<CurveType>> 
		Cad_SingularityBase<CurveType>::LineHorizonCurves_Loop
		(
			const Entity2d_Box & theBox
		)
	{
		const auto& p0 = theBox.P0();
		const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
		const auto& p2 = theBox.P1();
		const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

		std::vector<std::shared_ptr<CurveType>> curves;
		curves.reserve(4);

		curves.push_back(ParametricCurve_Line(p0, p3));
		curves.push_back(ParametricCurve_Line(p3, p2));
		curves.push_back(ParametricCurve_Line(p2, p1));
		curves.push_back(ParametricCurve_Line(p1, p0));

		return std::move(curves);
	}

	template<class CurveType>
	inline std::vector<std::shared_ptr<CurveType>> 
		Cad_SingularityBase<CurveType>::LineHorizonCurves_TwoSided
		(
			const Entity2d_Box & theBox,
			const Standard_Integer s0
		)
	{
		const auto& p0 = theBox.P0();
		const auto p1 = theBox.Corner(Box2d_PickAlgorithm_SE);
		const auto& p2 = theBox.P1();
		const auto p3 = theBox.Corner(Box2d_PickAlgorithm_NW);

		std::vector<std::shared_ptr<CurveType>> curves;
		curves.reserve(2);

		if (s0 IS_EQUAL 1 OR s0 IS_EQUAL 3)
		{
			curves.push_back(ParametricCurve_Line(p0, p3));
			curves.push_back(ParametricCurve_Line(p2, p1));

			return std::move(curves);
		}
		else if (s0 IS_EQUAL 2 OR s0 IS_EQUAL 4)
		{
			curves.push_back(ParametricCurve_Line(p3, p2));
			curves.push_back(ParametricCurve_Line(p1, p0));

			return std::move(curves);
		}

		FatalErrorIn(FunctionSIG)
			<< abort(FatalError);
		return std::move(curves);
	}
}