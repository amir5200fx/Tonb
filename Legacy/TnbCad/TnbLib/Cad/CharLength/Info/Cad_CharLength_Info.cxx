#include <Cad_CharLength_Info.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>

const Standard_Integer tnbLib::Cad_CharLength_Info::DEFAULT_NB_U = 5;
const Standard_Integer tnbLib::Cad_CharLength_Info::DEFAULT_NB_V = 5;

const std::shared_ptr<tnbLib::NumAlg_AdaptiveInteg_Info> tnbLib::Cad_CharLength_Info::DEFAULT_INFO =
std::make_shared<tnbLib::NumAlg_AdaptiveInteg_Info>();

namespace tnbLib
{
	class Cad_CharLength_IntegInfoRunTimeSettings
	{

		/*Private Data*/

	public:

		// default constructor [6/4/2022 Amir]

		Cad_CharLength_IntegInfoRunTimeSettings()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::Cad_CharLength_IntegInfoRunTimeSettings::SetInfo()
{
	const auto& myInfo = tnbLib::Cad_CharLength_Info::DEFAULT_INFO;

	myInfo->SetMaxNbIterations(200);
	myInfo->SetNbInitIterations(4);
	myInfo->SetTolerance(1.0E-4);
}

static tnbLib::Cad_CharLength_IntegInfoRunTimeSettings Cad_CharLength_IntegInfoRunTimeSettingsObj;