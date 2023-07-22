#include <MeshBase_Tools.hxx>

#include <GeoMesh2d_MetricBackground.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Geo2d_DelTri.hxx>
#include <Geo_BoxTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::shared_ptr<tnbLib::GeoMesh2d_Background> 
tnbLib::MeshBase_Tools::MakeBakground
(
	const std::vector<Pnt2d>& theCoords,
	const std::vector<Standard_Real>& theValues,
	const Standard_Real theTol
)
{
	auto mesh = std::make_shared<Geo2d_DelTri>(theCoords);
	Debug_Null_Pointer(mesh);
	mesh->Triangulate();
	Debug_If_Condition_Message(NOT mesh->IsDone(), "the application is not performed.");
	const auto& tris = mesh->Data();

	auto meshData = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(meshData);
	meshData->Construct(*tris);

	const auto bMesh = std::make_shared<GeoMesh2d_SingleBackground>();
	Debug_Null_Pointer(bMesh);

	auto domain = Geo_BoxTools::GetBox(theCoords, 0);
	auto d = domain.Diameter();
	domain.Expand(d * theTol);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(domain));
	bMesh->Sources().resize(tris->NbPoints());

	size_t k = 0;
	for (auto& x : bMesh->Sources())
	{
		x = theValues.at(k++);
	}
	return std::move(bMesh);
}

std::shared_ptr<tnbLib::GeoMesh2d_MetricBackground> 
tnbLib::MeshBase_Tools::MakeBackground
(
	const std::vector<Pnt2d>& theCoords,
	const std::vector<Entity2d_Metric1>& theValues,
	const Standard_Real theTol
)
{
	auto mesh = std::make_shared<Geo2d_DelTri>(theCoords);
	Debug_Null_Pointer(mesh);
	mesh->Triangulate();
	Debug_If_Condition_Message(NOT mesh->IsDone(), "the application is not performed.");
	const auto& tris = mesh->Data();

	auto meshData = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(meshData);
	meshData->Construct(*tris);

	const auto bMesh = std::make_shared<GeoMesh2d_SingleMetricBackground>();
	Debug_Null_Pointer(bMesh);

	auto domain = Geo_BoxTools::GetBox(theCoords, 0);
	auto d = domain.Diameter();
	domain.Expand(d * theTol);

	bMesh->LoadData(std::move(meshData));

	// initiate the current element [8/1/2022 Amir]
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(domain));
	bMesh->Sources().resize(tris->NbPoints());

	size_t k = 0;
	for (auto& x : bMesh->Sources())
	{
		x = theValues.at(k++);
	}
	return std::move(bMesh);
}