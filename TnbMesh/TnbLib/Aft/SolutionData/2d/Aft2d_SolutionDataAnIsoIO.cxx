#include <Aft2d_SolutionDataAnIso.hxx>

#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_MetricPrcsrAnIso.hxx>
#include <Aft2d_RegionPlaneAnIso.hxx>
#include <Aft2d_SegmentEdgeAnIso.hxx>
#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Entity2d_Box.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Aft2d_SolutionDataAnIso)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theGlobalMetricInfo_;
	ar & theMetricFunction_;

	ar & theNodeCalculator_;

	ar & theBoundaryInfo_;

	ar & theMetric_;
	ar & theRegion_;

	ar & theEdges_;

	ar & theElements_;

	//ar & theSizeFun_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Aft2d_SolutionDataAnIso)
{
	ar & boost::serialization::base_object<Aft2d_SolutionDataBase>(*this);

	ar & theGlobalMetricInfo_;
	ar & theMetricFunction_;

	ar & theNodeCalculator_;

	ar & theBoundaryInfo_;

	ar & theMetric_;
	ar & theRegion_;

	ar & theEdges_;

	ar & theElements_;

	//ar & theSizeFun_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::Aft2d_SolutionDataAnIso);