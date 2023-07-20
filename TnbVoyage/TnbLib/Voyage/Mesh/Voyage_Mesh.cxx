#include <Voyage_Mesh.hxx>

#include <VoyageGeo_Path.hxx>
#include <VoyageField_Earth.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


void tnbLib::Voyage_Mesh::Perform()
{

	const auto& refPath = Path();
	auto stagePars = refPath->Discrete(SizeFun(), MetricFun());
	for (auto xs : stagePars)
	{
		auto stage = refPath->Value(xs);

	}
}