#pragma once
#include <Mesh_CurveLength.hxx>
#include <Mesh_CurveEntity.hxx>
#include <Global_Macros.hxx>
#include <Geo_CurveLength.hxx>

#include <opencascade/gp.hxx>

namespace tnbLib
{

	template<class gCurveType, class MetricPrcsrType>
	void Mesh_CurveOptmPoint_Correction<gCurveType, MetricPrcsrType>::Perform()
	{
		static auto calcLength = [](const Mesh_CurveEntity<gCurveType, MetricPrcsrType>& theEntity, const Standard_Real theLower, const Standard_Real theUpper, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			try
			{
				return Mesh_CurveLength::Length(theEntity, theLower, theUpper, *theInfo);
			}
			catch (const ConvError&)
			{
				return theInfo->Result();
			}
		};

		//const auto& map = Entity().SizeMap();
		const auto& curve = Entity().Curve();

		const auto nbLevels = Info().MaxLevel();
		const auto tol = Info().Tolerance();
		const auto underRelaxation = Info().UnderRelaxation();

		auto Correct = Guess();
		auto P0 = curve.Value(U0());

		auto Umin = U0();
		auto Umax = Entity().LastParameter();

		if (Correct < Umin) Correct = Umin;
		if (Correct > Umax) Correct = Umax;

		Debug_If_Condition(Len() <= gp::Resolution());
		forThose(Iter, 1, nbLevels)
		{
			//auto dis = map.CalcUnitDistance(P0, curve.Value(Correct)) / Len();
			auto dis = calcLength(Entity(), U0(), Correct, IntegInfo()) / Len();
			auto du = (Correct - Umin) / dis;

			//Correct = Umin + underRelaxation*du;
			Correct = Umin + du;

			if (Correct < Umin) Correct = Umin;
			if (Correct > Umax) Correct = Umax;

			if (ABS(1.0 - dis) < tol) break;
		}
		// check the corrected value [5/11/2022 Amir]
		//const auto dis = map.CalcUnitDistance(P0, curve.Value(Correct)) / Len();
		auto dis = calcLength(Entity(), U0(), Correct, IntegInfo()) / Len();
		if (std::abs(1.0 - dis) > 0.15)
		{
			FatalConvErrorIn(FunctionSIG, nbLevels, tol)
				<< "the optm. point algorithm has not been converged!" << endl
				<< abort(FatalConvError);
		}
		ChangeCorrected() = Correct;
		Change_IsDone() = Standard_True;
	}


	//template<class gCurveType>
	//void Mesh_CurveOptmPoint_Correction<gCurveType, void>::Perform()
	//{
	//	auto& integInfo = *IntegInfo();
	//	const auto s = 1.0 / Entity().Size();
	//	const auto& curve = Entity().Curve();

	//	const auto nbLevels = Info().MaxLevel();
	//	const auto tol = Info().Tolerance();
	//	const auto underRelaxation = Info().UnderRelaxation();

	//	auto Correct = Guess();

	//	auto Umin = U0();
	//	auto Umax = Entity().LastParameter();

	//	Geo_CurveIntegrand<gCurveType> integrand(curve);
	//	forThose(Iter, 1, nbLevels)
	//	{
	//		auto dis = s * geoLib::CalcCurveLength<gCurveType>::_(integrand, Umin, Correct, integInfo) / Len();
	//		auto du = (Correct - Umin) / dis;
	//		//Correct = Umin + underRelaxation*du;
	//		Correct = Umin + du;

	//		if (Correct < Umin) Correct = Umin;
	//		if (Correct > Umax) Correct = Umax;

	//		if (ABS(1.0 - dis) < tol) break;
	//	}

	//	ChangeCorrected() = Correct;
	//	Change_IsDone() = Standard_True;
	//}
}