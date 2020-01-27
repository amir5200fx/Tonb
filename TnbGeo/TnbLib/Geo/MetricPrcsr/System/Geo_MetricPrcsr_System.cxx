#include <Geo_MetricPrcsr_System.hxx>

#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>

namespace tnbLib
{

	std::shared_ptr<NumAlg_AdaptiveInteg_Info> sysLib::gl_geo_metric_processor_integration_info =
		std::make_shared<NumAlg_AdaptiveInteg_Info>();

	std::shared_ptr<Geo_MetricPrcsrAnIso_Info> sysLib::gl_geo_metric_processor_aniso_info =
		std::make_shared<Geo_MetricPrcsrAnIso_Info>();
}

void tnbLib::sysLib::init_gl_geo_metric_processor_run_time_info()
{
	auto& intg = *gl_geo_metric_processor_integration_info;
	intg.SetMaxNbIterations(100);
	intg.SetNbInitIterations(2);
	intg.SetTolerance(1.0E-4);


	auto& inf = *gl_geo_metric_processor_aniso_info;
	inf.OverrideIntegInfo(gl_geo_metric_processor_integration_info);
	inf.SetNbSamples(3);
}