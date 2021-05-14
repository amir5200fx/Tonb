#include <Aft2d_MetricPrcsrAnIso_System.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>

namespace tnbLib
{
	TnbMesh_EXPORT std::shared_ptr<NumAlg_AdaptiveInteg_Info> sysLib::gl_metric_prcsr_aniso_intg_info =
		std::make_shared<NumAlg_AdaptiveInteg_Info>();

	TnbMesh_EXPORT std::shared_ptr<Aft_MetricPrcsrAnIso_Info> sysLib::gl_aft_metric_prcsr_aniso_info =
		std::make_shared<Aft_MetricPrcsrAnIso_Info>();
}

void tnbLib::sysLib::init_gl_aft_metric_prcsr_aniso_info()
{
	auto& info = *gl_aft_metric_prcsr_aniso_info;
	info.OverrideIntegInfo(gl_metric_prcsr_aniso_intg_info);

	auto& intgInfo = *gl_metric_prcsr_aniso_intg_info;
	intgInfo.SetMaxNbIterations(50);
	intgInfo.SetNbInitIterations(2);
	intgInfo.SetTolerance(1.0E-4);
}

namespace tnbLib
{

	class RunInitMetricPrcsrAnIsoSystem
	{
	public:

		RunInitMetricPrcsrAnIsoSystem()
		{
			tnbLib::sysLib::init_gl_aft_metric_prcsr_aniso_info();
		}
	};

}

tnbLib::RunInitMetricPrcsrAnIsoSystem runIt;