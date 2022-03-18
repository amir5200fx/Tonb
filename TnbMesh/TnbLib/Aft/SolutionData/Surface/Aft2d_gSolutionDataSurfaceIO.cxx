#include <Aft2d_gSolutionDataSurface.hxx>

#include <Cad_GModel.hxx>
#include <GModel_Plane.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Aft2d_OptNodeSurface_Calculator.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_gSolutionDataSurface)
{
	ar & theShape_;

	ar & theSizeFun_;

	ar & theMetricPrcsrInfo_;
	ar & theMetricPrcsrMethod_;

	ar & theMetricFunMethod_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_gSolutionDataSurface)
{
	ar & theShape_;

	ar & theSizeFun_;

	ar & theMetricPrcsrInfo_;
	ar & theMetricPrcsrMethod_;

	ar & theMetricFunMethod_;
}