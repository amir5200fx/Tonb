#include <Cad_CurveLength_Info.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

const std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Cad_CurveLength_Info::DEFAULT_INTEG_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

const Standard_Integer tnbLib::Cad_CurveLength_Info::DEFAULT_MAX_LEVEL(10);

namespace tnbLib
{

	class CadCurveLengthRunTimeInfo
	{

		/*Private Data*/

	public:

		// default constructor [1/16/2022 Amir]

		CadCurveLengthRunTimeInfo()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

static const tnbLib::CadCurveLengthRunTimeInfo myCadCurveLengthRunTimeInfoObj;

void tnbLib::CadCurveLengthRunTimeInfo::SetInfo()
{
	const auto& myInfo = Cad_CurveLength_Info::DEFAULT_INTEG_INFO;
	myInfo->SetTolerance(1.0E-6);
	myInfo->SetMaxNbIterations(200);
	myInfo->SetNbInitIterations(8);
}