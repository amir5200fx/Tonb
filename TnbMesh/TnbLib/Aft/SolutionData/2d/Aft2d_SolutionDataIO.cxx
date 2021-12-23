#include <Aft2d_SolutionData.hxx>

#include <Aft_MetricPrcsr_Info.hxx>
#include <Aft2d_BoundaryOfPlane_Info.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_RegionPlane.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_OptNode_Calculator.hxx>
#include <Aft2d_Element.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Entity2d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_SolutionData)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theGlobalMetricInfo_;

	ar & theNodeCalculator_;

	ar & theBoundaryInfo_;

	ar & theMetric_;
	ar & theRegion_;

	ar & theEdges_;

	ar & theElements_;

	//ar & theSizeFun_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_SolutionData)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theGlobalMetricInfo_;

	ar & theNodeCalculator_;

	ar & theBoundaryInfo_;

	ar & theMetric_;
	ar & theRegion_;

	ar & theEdges_;

	ar & theElements_;

	//ar & theSizeFun_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SolutionData);