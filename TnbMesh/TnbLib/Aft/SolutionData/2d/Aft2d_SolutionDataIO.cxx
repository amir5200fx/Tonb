#include <Aft2d_SolutionData.hxx>

#include <Aft_MetricPrcsr_Info.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Entity2d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_SolutionData)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theGlobalMetricInfo_;

	ar & theBoundaryInfo_;

	ar & theMetric_;
	ar & theRegion_;

	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_SolutionData)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theGlobalMetricInfo_;

	ar & theBoundaryInfo_;

	ar & theMetric_;
	ar & theRegion_;

	ar & theEdges_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SolutionData);