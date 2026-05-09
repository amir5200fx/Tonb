#include <Cad_ApprxMetricSubdivider.hxx>

#include <Cad_ApprxMetricCriterion_MinMax.hxx>
#include <Geo2d_SamplePoints_5Pts.hxx>
#include <Geo2d_SamplePoints.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom_Surface.hxx>

const std::shared_ptr<tnbLib::Cad_ApprxMetricCriterion> tnbLib::Cad_ApprxMetricSubdivider::DEFAULT_CRITERION =
std::make_shared<tnbLib::cadLib::ApprxMetricCriterion_MinMax>();

const std::shared_ptr<tnbLib::Geo2d_SamplePoints> tnbLib::Cad_ApprxMetricSubdivider::DEFAULT_SAMPLES =
std::make_shared<tnbLib::Geo2d_SamplePoints_5Pts>();

Standard_Boolean 
tnbLib::Cad_ApprxMetricSubdivider::Subdivide
(
	const Entity2d_Box & theDomain,
	const Cad_ApprxMetricSubdivider * theAlg
)
{
	Debug_Null_Pointer(theAlg);
	Debug_Null_Pointer(theAlg->Criterion());
	Debug_Null_Pointer(theAlg->Samples());
	Debug_Null_Pointer(theAlg->Geometry());

	const auto& criterion = theAlg->Criterion();

	return criterion->Subdivide(theDomain, theAlg->Samples(), theAlg->Geometry());
}