#include <Aft2d_AltrOptNodeSurface.hxx>

#include <Aft2d_ElementSurface.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface)
{
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theFront_;
	ar& theMetricMap_;
	ar& theP0_;
	ar& theSize_;

	ar& theCorrected_;
	ar& IsConverged_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_AltrOptNodeSurface)
{
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theFront_;
	ar& theMetricMap_;
	ar& theP0_;
	ar& theSize_;

	ar& theCorrected_;
	ar& IsConverged_;
}