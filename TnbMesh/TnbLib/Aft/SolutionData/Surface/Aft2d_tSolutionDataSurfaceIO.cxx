#include <Aft2d_tSolutionDataSurface.hxx>

#include <Cad_TModel.hxx>
#include <TModel_Plane.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Aft2d_OptNodeSurface_Calculator.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Entity3d_Triangulation.hxx>

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_tSolutionDataSurface)
{
	ar & theShape_;

	ar & theSizeFun_;

	ar & theGlobalCurveInfo_;
	ar & theCurveInfo_;

	ar & theMetricPrcsrInfo_;
	ar & theMetricPrcsrMethod_;

	ar & theMetricFunMethod_;

	ar & theTris_;
	ar & theMergedTris_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_tSolutionDataSurface)
{
	ar & theShape_;

	ar & theSizeFun_;

	ar & theGlobalCurveInfo_;
	ar & theCurveInfo_;

	ar & theMetricPrcsrInfo_;
	ar & theMetricPrcsrMethod_;

	ar & theMetricFunMethod_;

	ar & theTris_;
	ar & theMergedTris_;
}