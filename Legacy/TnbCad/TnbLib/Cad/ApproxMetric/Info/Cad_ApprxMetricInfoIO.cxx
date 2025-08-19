#include <Cad_ApprxMetricInfo.hxx>

#include <Geo2d_SamplePoints_5Pts.hxx>
#include <Cad_ApprxMetricCriterion_MinMax.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Cad_ApprxMetricInfo)
{
	ar & theMinLevel_;
	ar & theMaxLevel_;
	ar & theUnbalancing_;

	ar & theMergeInfo_;

	ar & theSamples_;
	ar & theCriterion_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Cad_ApprxMetricInfo)
{
	ar & theMinLevel_;
	ar & theMaxLevel_;
	ar & theUnbalancing_;

	ar & theMergeInfo_;

	ar & theSamples_;
	ar & theCriterion_;
}