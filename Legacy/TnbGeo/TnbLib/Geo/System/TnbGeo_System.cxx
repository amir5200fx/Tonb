#include <TnbGeo_System.hxx>

#include <Geo_ApprxCurve_System.hxx>
//#include <Geo_MetricPrcsr_System.hxx>

void tnbLib::sysLib::init_TnbGeo()
{
	sysLib::init_gl_approx_curve_info();
	//sysLib::init_gl_geo_metric_processor_run_time_info();
}