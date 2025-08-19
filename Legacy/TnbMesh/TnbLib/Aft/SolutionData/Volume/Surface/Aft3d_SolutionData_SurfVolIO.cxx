#include <Aft3d_SolutionData_SurfVol.hxx>

#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Cad_Volume.hxx>
#include <Entity3d_Triangulation.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft3d_SolutionData_SurfVol)
{
	ar& theVolume_;
	ar& theSizeFun_;
	ar& theCurveInfo_;
	ar& theMetricProcessor_;

	ar& theTris_;
	ar& theMerged_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft3d_SolutionData_SurfVol)
{
	ar& theVolume_;
	ar& theSizeFun_;
	ar& theCurveInfo_;
	ar& theMetricProcessor_;

	ar& theTris_;
	ar& theMerged_;
}