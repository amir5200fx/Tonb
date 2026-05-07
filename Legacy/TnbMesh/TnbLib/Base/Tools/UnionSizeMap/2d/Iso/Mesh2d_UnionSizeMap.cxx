#include <Mesh2d_UnionSizeMap.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo2d_ApprxSpace.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoMesh2d_Data.hxx>

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

template<>
Standard_Boolean tnbLib::Mesh2d_UnionSizeMap::TreeObject::Subdivide(const Entity2d_Box& b) const
{
	const auto h1 = ElementSize(b.P0());
	const auto h2 = ElementSize(b.Corner(Box2d_PickAlgorithm_SE));
	const auto h3 = ElementSize(b.P1());
	const auto h4 = ElementSize(b.Corner(Box2d_PickAlgorithm_NW));

	const auto tol = Tolerance() * b.Diameter();

	if (TOLERANCE(h1, h2) > tol)
		return Standard_True;

	if (TOLERANCE(h1, h3) > tol)
		return Standard_True;

	if (TOLERANCE(h1, h4) > tol)
		return Standard_True;

	if (TOLERANCE(h2, h3) > tol)
		return Standard_True;

	if (TOLERANCE(h2, h4) > tol)
		return Standard_True;

	if (TOLERANCE(h3, h4) > tol)
		return Standard_True;

	return Standard_False;
}

template<>
Standard_Boolean tnbLib::Mesh2d_UnionSizeMap::TreeObject::Subdivider
(
	const Entity2d_Box& b,
	const TreeObject* t
)
{
	Debug_Null_Pointer(t);
	const auto& obj = *t;

	if (obj.Subdivide(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW)))
		return Standard_True;
	if (obj.Subdivide(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE)))
		return Standard_True;
	if (obj.Subdivide(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE)))
		return Standard_True;
	if (obj.Subdivide(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW)))
		return Standard_True;
	return Standard_False;
}

template<>
void tnbLib::Mesh2d_UnionSizeMap::Perform()
{
	const auto& sizeMaps = SizeMaps();
	if (sizeMaps.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size map has been found!" << endl
			<< abort(FatalError);
	}

	if (sizeMaps.size() IS_EQUAL 1)
	{
		auto iter = sizeMaps.begin();
		theBackMesh_ = *iter;
	}

	const auto boundingBox = CalcBoundingBox(sizeMaps);

	TreeObject object(sizeMaps, Tolerance());
	std::vector<Entity2d_Box> boxes;
	{ // space scope [5/30/2021 Amir]
		Geo2d_ApprxSpace<TreeObject> tree;

		tree.SetDomain(boundingBox);

		tree.SetMinLevel(MinSubdivision());
		tree.SetMaxLevel(MaxSubdivision());
	
		tree.SetObject(&object);
		tree.SetSubdivider(&TreeObject::Subdivider);

		tree.Init();
		tree.Perform();

		tree.RetrieveBoxesTo(boxes);
	}

	Entity2d_Triangulation tri;
	Geo_BoxTools::GetTriangulation(boxes, tri);
	
	auto backMeshData = std::make_shared<GeoMesh2d_Data>();
	Debug_Null_Pointer(backMeshData);

	backMeshData->Construct(tri);

	// free memory [5/30/2021 Amir]
	tri.Clear();

	auto backMesh = std::make_shared<GeoMesh2d_SingleBackground>();
	Debug_Null_Pointer(backMesh);

	backMesh->LoadData(std::move(backMeshData));
	backMesh->InitiateCurrentElement();
	backMesh->SetBoundingBox(std::move(boundingBox));

	auto& sources = backMesh->Sources();

	std::vector<std::shared_ptr<Mesh2d_Node>> nodes;
	backMesh->Mesh()->RetrieveNodesTo(nodes);

	sources.reserve(nodes.size());
	for (const auto& x : nodes)
	{
		auto id = x->Index();
		sources[Index_Of(id)] = object.ElementSize(x->Coord());
	}

	theBackMesh_ = std::move(backMesh);

	Change_IsDone() = Standard_True;
}