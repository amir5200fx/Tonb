#include <Cad_ApprxMetricInfo.hxx>

#include <Geo2d_SamplePoints_5Pts.hxx>
#include <Cad_ApprxMetricCriterion_MinMax.hxx>

const std::string tnbLib::Cad_ApprxMetricInfo::extension = ".aprxmetricinfo";

const Standard_Integer tnbLib::Cad_ApprxMetricInfo::DEFAULT_MIN_LEVEL(2);
const Standard_Integer tnbLib::Cad_ApprxMetricInfo::DEFAULT_MAX_LEVEL(6);
const Standard_Integer tnbLib::Cad_ApprxMetricInfo::DEFAULT_UNBALANCING(2);


const std::shared_ptr<tnbLib::Geo2d_SamplePoints> tnbLib::Cad_ApprxMetricInfo::DEFAULT_SAMPLES =
std::make_shared<tnbLib::Geo2d_SamplePoints_5Pts>();

const std::shared_ptr<tnbLib::Cad_ApprxMetricCriterion> tnbLib::Cad_ApprxMetricInfo::DEFAULT_CRITERION =
std::make_shared<tnbLib::cadLib::ApprxMetricCriterion_MinMax>();

tnbLib::Cad_ApprxMetricInfo::Cad_ApprxMetricInfo()
	: theMinLevel_(DEFAULT_MIN_LEVEL)
	, theMaxLevel_(DEFAULT_MAX_LEVEL)
	, theUnbalancing_(DEFAULT_UNBALANCING)
	, theSamples_(DEFAULT_SAMPLES)
	, theCriterion_(DEFAULT_CRITERION)
{
	// empty body [12/30/2021 Amir]
}