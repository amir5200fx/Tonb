#include <Mesh_SizeMapControl_Info.hxx>

#include <GeoMesh_Background_Info.hxx>

const Standard_Integer tnbLib::Mesh_SizeMapControl_Info::DEFAULT_MAX_UNBALANCING(2);
const Standard_Real tnbLib::Mesh_SizeMapControl_Info::DEFAULT_TOLERANCE(1.0E-6);

const std::shared_ptr<tnbLib::GeoMesh_Background_SmoothingHvCorrection_Info> tnbLib::Mesh_SizeMapControl_Info::DEFAULT_HV_CORR_INFO =
std::make_shared<tnbLib::GeoMesh_Background_SmoothingHvCorrection_Info>();

namespace tnbLib
{

	class Mesh_SizeMapControl_InfoRunTimeSettings
	{

		/*Private Data*/

	public:

		// default constructor [7/18/2022 Amir]

		Mesh_SizeMapControl_InfoRunTimeSettings()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::Mesh_SizeMapControl_InfoRunTimeSettings::SetInfo()
{
	const auto& myInfo = tnbLib::Mesh_SizeMapControl_Info::DEFAULT_HV_CORR_INFO;

	myInfo->SetFactor(0.85);
	myInfo->SetMaxNbIters(5);
}

static const tnbLib::Mesh_SizeMapControl_InfoRunTimeSettings Mesh_SizeMapControl_InfoRunTimeSettingsObj;