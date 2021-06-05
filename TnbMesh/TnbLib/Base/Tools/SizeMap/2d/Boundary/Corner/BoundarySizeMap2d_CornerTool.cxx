#include <BoundarySizeMap2d_CornerTool.hxx>

#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Geo_BoxTools.hxx>
#include <Merge_StaticData.hxx>
#include <Pln_Vertex.hxx>
#include <Cad2d_Plane.hxx>
#include <GeoMesh2d_Background.hxx>
#include <MeshBase_Tools.hxx>
#include <BoundarySizeMap2d_CornerToolSystem.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

namespace tnbLib
{
	const Standard_Integer tnbLib::BoundarySizeMap2d_CornerTool::DEFAULT_BUCKETSIZE = 4;
	const Standard_Integer tnbLib::BoundarySizeMap2d_CornerTool::DEFAULT_MIN_SUBDIVISION = 2;
	const Standard_Integer tnbLib::BoundarySizeMap2d_CornerTool::DEFAULT_MAX_SUBDIVISION = 5;
}

tnbLib::BoundarySizeMap2d_CornerTool::BoundarySizeMap2d_CornerTool
(
	const std::shared_ptr<Mesh_ReferenceValues>& theRef,
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
	: Mesh2d_BoundarySizeMapTool(thePlane, theRef)
	, theBucketSize_(DEFAULT_BUCKETSIZE)
	, theMinSubdivision_(DEFAULT_MIN_SUBDIVISION)
	, theMaxSubdivision_(DEFAULT_MAX_SUBDIVISION)
{
	//- empty body
}

void tnbLib::BoundarySizeMap2d_CornerTool::SetBucketSize
(
	const Standard_Integer theSize
)
{
	theBucketSize_ = theSize;
}

void tnbLib::BoundarySizeMap2d_CornerTool::SetMinSubdivision
(
	const Standard_Integer nbLevels
)
{
	theMinSubdivision_ = nbLevels;
}

void tnbLib::BoundarySizeMap2d_CornerTool::SetMaxSubdivision
(
	const Standard_Integer nbLevels
)
{
	theMaxSubdivision_ = nbLevels;
}

namespace tnbLib
{

	namespace meshLib
	{

		inline Standard_Real CalcRadius
		(
			const Standard_Real growthRate, 
			const Standard_Real target,
			const Standard_Real base
		)
		{
			const auto H = base - target;
			Debug_If_Condition_Message(H < 0, "invalid element size");

			const auto theta = asin(growthRate);
			return H / tan(theta);
		}

		class BalancedQuadTreeObject
		{

		public:

			const std::vector<std::pair<Pnt2d, Standard_Real>>& Sources;

			Standard_Real Tolerance;

			Standard_Real Target;
			Standard_Real BaseSize;
			Standard_Real Radius2;

			BalancedQuadTreeObject(const std::vector<std::pair<Pnt2d, Standard_Real>>& s)
				: Sources(s)
			{}

			Standard_Real ElementSize(const Pnt2d&) const;

			static Standard_Boolean Subdivide(const Entity2d_Box&, const BalancedQuadTreeObject* t);
		};
	}
}

Standard_Real 
tnbLib::meshLib::BalancedQuadTreeObject::ElementSize
(
	const Pnt2d & coord
) const
{
	Debug_If_Condition(Sources.empty());

	const auto DH = BaseSize - Target;
	auto H = RealLast();
	Standard_Real h;
	for (const auto& x : Sources)
	{
		auto radius2 = coord.SquareDistance(x.first);
		if (radius2 > Radius2)
			h = BaseSize;
		else
			h = sqrt(radius2 / Radius2)*DH + Target;
		if (h < H)H = h;
	}
	return H;
}

Standard_Boolean 
tnbLib::meshLib::BalancedQuadTreeObject::Subdivide
(
	const Entity2d_Box & b, 
	const BalancedQuadTreeObject * t
)
{
	Debug_Null_Pointer(t);
	const auto& obj = *t;

	const auto tol = obj.Tolerance;

	const auto h1 = obj.ElementSize(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SW).CalcCentre());
	const auto h2 = obj.ElementSize(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_SE).CalcCentre());
	const auto h3 = obj.ElementSize(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NE).CalcCentre());
	const auto h4 = obj.ElementSize(b.SubDivide(Box2d_SubDivideAlgorithm_Quad_NW).CalcCentre());

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

#include <Entity2d_Triangulation.hxx>
#include <Geo_ItemMerge.hxx>
#include <Geo2d_ApprxSpace.hxx>

void tnbLib::BoundarySizeMap2d_CornerTool::Perform()
{
	auto corners = RetrieveCorners();
	if (corners.empty()) return;

	//! Retrieve sizes
	Standard_Real elemSize, minElemSize, spanAngle;
	RetrieveValues(elemSize, minElemSize, spanAngle);

	Standard_Real radius = 0;
	if (MeshConditions().CustomBoundaryGrowthRate()) 
		radius = ::tnbLib::meshLib::CalcRadius(Mesh_VariationRate::Rate(MeshValues().BoundaryGrowthRate()), elemSize, ReferenceValues()->BaseSize());
	else
		radius = ::tnbLib::meshLib::CalcRadius(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()), elemSize, ReferenceValues()->BaseSize());
	if (radius IS_EQUAL 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid radius value has been detected!" << endl
			<< abort(FatalError);
	}
	std::vector<std::pair<Pnt2d, Standard_Real>> compactItems;
	{
		std::vector<std::pair<Pnt2d, Standard_Real>> sources;
		sources.reserve(corners.size());
		for (const auto& x : corners)
		{
			Debug_Null_Pointer(x);
			auto paired = std::make_pair(x->Coord(), elemSize);
			sources.push_back(std::move(paired));
		}

		Geo_ItemMerge<std::pair<Pnt2d, Standard_Real>, Pnt2d>
			mergAlg(sources, [](const std::pair<Pnt2d, Standard_Real>& p)->auto {return p.first; });
		mergAlg.Perform();
		Debug_If_Condition_Message(NOT mergAlg.IsDone(), "the algorithm is not performed!");

		compactItems = mergAlg.CompactItems();
	}

	const auto b = Plane()->BoundingBox(0.0);
	const auto expB = b.Expanded(0.15*b.Diameter());

	std::vector<Entity2d_Box> boxes;
	{
		meshLib::BalancedQuadTreeObject obj(compactItems);
		if (MeshConditions().CustomBoundaryGrowthRate()) obj.Tolerance = Mesh_VariationRate::Rate(MeshValues().BoundaryGrowthRate());
		else obj.Tolerance = Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate());
		obj.Radius2 = radius * radius;
		obj.Target = elemSize;
		obj.BaseSize = ReferenceValues()->BaseSize();

		Geo2d_ApprxSpace<meshLib::BalancedQuadTreeObject> tree;

		tree.SetMinLevel(MinSubdivision());
		tree.SetMaxLevel(MaxSubdivision());

		tree.SetObject(&obj);
		tree.SetSubdivider(&meshLib::BalancedQuadTreeObject::Subdivide);
		tree.SetDomain(expB);

		tree.Init();
		tree.Perform();

		boxes = tree.RetrieveBoxes();
		tree.Clear();
	}

	const auto triangulation = Geo_BoxTools::GetTriangulation(boxes);

	const auto bMesh = std::make_shared<GeoMesh2d_Background>();
	Debug_Null_Pointer(bMesh);

	bMesh->Mesh()->Construct(triangulation);
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(expB));

	MeshBase_Tools::SetSourcesToMesh(compactItems, ReferenceValues()->BaseSize(), *bMesh);
	compactItems.clear();

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(sysLib::gl_background_hv_correction_info->MaxNbIters());

	if (MeshConditions().CustomBoundaryGrowthRate())
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->BoundaryGrowthRate()));
	else
		hvInfo->SetFactor(Mesh_VariationRate::Rate(ReferenceValues()->DefaultGrowthRate()));
	bMesh->HvCorrection(hvInfo);

	ChangeBackMesh() = std::move(bMesh);
	Change_IsDone() = Standard_True;
}