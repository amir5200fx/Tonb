#include <Cad_CurveSplitter_Info.hxx>

#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>

const Standard_Integer tnbLib::Cad_CurveSplitter_Info::DEFAULT_MAX_LEVEL = 10;

const Standard_Real tnbLib::Cad_CurveSplitter_Info::DEFAULT_UR = 0.9;

const std::shared_ptr<tnbLib::Mesh_CurveOptmPoint_Correction_Info> tnbLib::Cad_CurveSplitter_Info::DEFAULT_CORR_INFO =
std::make_shared<tnbLib::Mesh_CurveOptmPoint_Correction_Info>();

const std::shared_ptr<tnbLib::NumAlg_NewtonSolver_Info> tnbLib::Cad_CurveSplitter_Info::DEFAULT_NEWTON_INFO =
std::make_shared<tnbLib::NumAlg_NewtonSolver_Info>();

const std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Cad_CurveSplitter_Info::DEFAULT_OVERALL_LENGTH_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

const std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Cad_CurveSplitter_Info::DEFAULT_ITER_INTEG_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

namespace tnbLib
{

	class CurveSplitterInfoRunTimeSetup
	{
		
		/*Private Data*/

	public:

		CurveSplitterInfoRunTimeSetup()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

static const tnbLib::CurveSplitterInfoRunTimeSetup myCurveSplitterInfoRunTimeSetupObj;

void tnbLib::CurveSplitterInfoRunTimeSetup::SetInfo()
{
	{
		auto& myInfo = *Cad_CurveSplitter_Info::DEFAULT_CORR_INFO;

		myInfo.SetMaxLevel(5);
		myInfo.SetTolerance(1.0E-4);
		myInfo.SetUnderRelaxation(0.85);
	}

	{
		auto& myInfo = *Cad_CurveSplitter_Info::DEFAULT_ITER_INTEG_INFO;

		myInfo.SetMaxNbIterations(50);
		myInfo.SetNbInitIterations(4);
		myInfo.SetTolerance(1.0E-6);
	}

	{
		auto& myInfo = *Cad_CurveSplitter_Info::DEFAULT_NEWTON_INFO;

		myInfo.SetMaxIterations(100);
		myInfo.SetSmall(1.0E-6);
		myInfo.SetTolerance(1.0E-6);
		myInfo.SetUnderRelaxation(0.85);
		myInfo.SetZero(1.0E-10);
	}

	{
		auto& myInfo = *Cad_CurveSplitter_Info::DEFAULT_OVERALL_LENGTH_INFO;

		myInfo.SetMaxNbIterations(200);
		myInfo.SetNbInitIterations(8);
		myInfo.SetTolerance(1.0E-8);
	}
}