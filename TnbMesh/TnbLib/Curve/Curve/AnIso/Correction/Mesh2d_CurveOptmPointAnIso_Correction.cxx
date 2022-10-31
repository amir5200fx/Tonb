#ifdef MeshCurveAnIso_Debug
#include <Mesh2d_CurveOptmPointAnIso_Correction.hxx>

#include <Mesh_CurveLength.hxx>
#include <Mesh2d_CurveEntityAnIso.hxx>

template<>
void tnbLib::Mesh2d_CurveOptmPointAnIso_Correction::Perform()
{
	static auto calcLength = [](const Mesh2d_CurveEntityAnIso& theEntity, const Standard_Real theLower, const Standard_Real theUpper, const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
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

	const auto& curve = this->Entity().Curve();

	const auto nbLevels = this->Info().MaxLevel();
	const auto tol = this->Info().Tolerance();
	const auto underRelaxation = this->Info().UnderRelaxation();

	auto Correct = this->Guess();
	auto P0 = curve.Value(U0());

	auto Umin = this->U0();
	auto Umax = this->Entity().LastParameter();

	if (Correct < Umin) Correct = Umin;
	if (Correct > Umax) Correct = Umax;

	Debug_If_Condition(this->Len() <= gp::Resolution());
	forThose(Iter, 1, nbLevels)
	{
		//auto dis = map.CalcUnitDistance(P0, curve.Value(Correct)) / Len();
		auto dis = calcLength(this->Entity(), this->U0(), Correct, this->IntegInfo()) / this->Len();
		auto du = (Correct - Umin) / dis;

		//Correct = Umin + underRelaxation*du;
		Correct = Umin + du;

		if (Correct < Umin) Correct = Umin;
		if (Correct > Umax) Correct = Umax;

		if (ABS(1.0 - dis) < tol) break;
	}
	// check the corrected value [5/11/2022 Amir]
		//const auto dis = map.CalcUnitDistance(P0, curve.Value(Correct)) / Len();
	auto dis = calcLength(this->Entity(), this->U0(), Correct, this->IntegInfo()) / this->Len();
	if (std::abs(1.0 - dis) > 0.15)
	{
		FatalConvErrorIn(FunctionSIG, nbLevels, tol)
			<< "the optm. point algorithm has not been converged!" << endl
			<< abort(FatalConvError);
	}
	ChangeCorrected() = Correct;
	Change_IsDone() = Standard_True;
}
#endif // MeshCurveAnIso_Debug
