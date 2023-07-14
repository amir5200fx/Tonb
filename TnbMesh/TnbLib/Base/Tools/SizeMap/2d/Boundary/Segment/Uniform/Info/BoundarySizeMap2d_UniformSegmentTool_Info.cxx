#include <BoundarySizeMap2d_UniformSegmentTool_Info.hxx>

#include <Geo_BasicApprxCurve_Info.hxx>

namespace tnbLib
{

	class BoundarySizeMap2d_UniformSegmentTool_RunTimeInfoSetting
	{

		/*Private Data*/

	public:

		// default constructor [8/25/2022 Amir]

		BoundarySizeMap2d_UniformSegmentTool_RunTimeInfoSetting()
		{
			SetInfo();
		}

		static void SetInfo();
	};
}

void tnbLib::BoundarySizeMap2d_UniformSegmentTool_RunTimeInfoSetting::SetInfo()
{
	const auto& info = BoundarySizeMap2d_UniformSegmentTool_Info::DEFAULT_INFO;
	info->SetInitNbSubdivision(4);
	info->SetMaxNbSubdivision(8);
	info->SetNbSamples(5);
}

static const tnbLib::BoundarySizeMap2d_UniformSegmentTool_RunTimeInfoSetting
BoundarySizeMap2d_UniformSegmentTool_RunTimeInfoSettingObj;

std::shared_ptr<tnbLib::Geo_BasicApprxCurve_Info>
tnbLib::BoundarySizeMap2d_UniformSegmentTool_Info::DEFAULT_INFO =
std::make_shared<tnbLib::Geo_BasicApprxCurve_Info>();

Standard_Boolean tnbLib::BoundarySizeMap2d_UniformSegmentTool_Info::POST_BALANCE = Standard_True;
Standard_Integer tnbLib::BoundarySizeMap2d_UniformSegmentTool_Info::DEFAULT_BUCKET_SIZE = 4;
Standard_Integer tnbLib::BoundarySizeMap2d_UniformSegmentTool_Info::DEFAULT_UNBALANCING = 2;