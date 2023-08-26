#include <Voyage_PathDiscret_Info.hxx>

#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>

std::shared_ptr<tnbLib::Mesh_Curve_Info> tnbLib::Voyage_PathDiscret_Info::DEFAULT_CURV_INFO =
std::make_shared<tnbLib::Mesh_Curve_Info>();

std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Voyage_PathDiscret_Info::DEFAULT_INTEG_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

namespace tnbLib
{

	class Voyage_PathDiscret_InfoRunTime
	{

		/*Private Data*/

		// Private functions and operators [8/26/2023 Payvand]

		void SetConfigs();

	public:

		// default constructor [8/26/2023 Payvand]

		Voyage_PathDiscret_InfoRunTime()
		{
			SetConfigs();
		}

		// constructors [8/26/2023 Payvand]

		// Public functions and operators [8/26/2023 Payvand]



	};

	static const auto myOverallLenIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static const auto myIterIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static const auto myNewtonIterInfo = std::make_shared<NumAlg_NewtonSolver_Info>();
	static const auto myOptPointCorrInfo = std::make_shared<Mesh_CurveOptmPoint_Correction_Info>();
	static const auto myBisectCorrInfo = std::make_shared<NumAlg_BisectionSolver_Info>();
}

static const tnbLib::Voyage_PathDiscret_InfoRunTime myVoyage_PathDiscret_InfoRunTimeObj;

void tnbLib::Voyage_PathDiscret_InfoRunTime::SetConfigs()
{
	myOverallLenIntegInfo->SetMaxNbIterations(500);
	myOverallLenIntegInfo->SetNbInitIterations(6);
	myOverallLenIntegInfo->SetTolerance(1.0E-8);

	myIterIntegInfo->SetMaxNbIterations(50);
	myIterIntegInfo->SetNbInitIterations(3);
	myIterIntegInfo->SetTolerance(1.0E-4);

	myNewtonIterInfo->SetMaxIterations(50);
	myNewtonIterInfo->SetSmall(1.0E-6);
	myNewtonIterInfo->SetZero(1.0E-6);
	myNewtonIterInfo->SetTolerance(1.0E-6);
	myNewtonIterInfo->SetUnderRelaxation(0.9);

	myOptPointCorrInfo->SetMaxLevel(10);
	myOptPointCorrInfo->SetTolerance(1.0E-6);
	myOptPointCorrInfo->SetUnderRelaxation(0.9);

	myBisectCorrInfo->SetMaxIterations(10);
	myBisectCorrInfo->SetTolerance(1.0E-6);
	myBisectCorrInfo->SetDelta(1.0E-6);

	{
		auto myInfo = Voyage_PathDiscret_Info::DEFAULT_CURV_INFO;
		myInfo->SetIgnoreNonConvergency(Standard_True);

		myInfo->SetUnderRelaxation(0.85);
		myInfo->SetLengthCalcMaxLevel(10);

		myInfo->OverrideCorrAlgInfo(myOptPointCorrInfo);
		myInfo->OverrideNewtonIntgInfo(myIterIntegInfo);
		myInfo->OverrideNewtonIterInfo(myNewtonIterInfo);
		myInfo->OverrideOverallLengthIntgInfo(myOverallLenIntegInfo);
		myInfo->OverrideBisectAlgInfo(myBisectCorrInfo);
	}

	{
		auto myInfo = Voyage_PathDiscret_Info::DEFAULT_INTEG_INFO;
		myInfo->SetMaxNbIterations(50);
		myInfo->SetNbInitIterations(4);
		myInfo->SetTolerance(1.0E-4);
	}
}