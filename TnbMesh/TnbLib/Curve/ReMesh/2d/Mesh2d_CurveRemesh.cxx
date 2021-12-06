#include <Mesh2d_CurveRemesh.hxx>

#include <Global_Timer.hxx>
#include <Pln_Curve.hxx>
#include <Cad2d_CmptLib.hxx>
#include <Mesh2d_Curve.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_AdTree.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Geo2d_ApprxSpace.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo_MetricPrcsr_System.hxx>
#include <GeoMetricFun2d_Background.hxx>
#include <GeoMesh_Background_System.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <Geo_MetricPrcsr_Info.hxx>
#include <MeshBase_Tools.hxx>
#include <Mesh_VariationRate.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <map>
#include <algorithm>

unsigned short tnbLib::Mesh2d_CurveRemesh::verbose(0);

namespace tnbLib
{

	struct DiscreteParameter
	{
		Standard_Real H;
		Standard_Real Parameter;
	};

	auto DiscreteCurve
	(
		const std::shared_ptr<Pln_Curve>& theCurve,
		const std::shared_ptr<Geo2d_MetricPrcsr>& theSizeMap, 
		const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
	{
		Debug_Null_Pointer(theCurve);
		const auto& geometry = theCurve->Geometry();

		auto alg = std::make_shared<Mesh_Curve<Geom2d_Curve, Geo2d_MetricPrcsr, true>>();
		Debug_Null_Pointer(alg);

		alg->LoadCurve(geometry, theCurve->FirstParameter(), theCurve->LastParameter());
		alg->LoadInfo(theInfo);
		alg->LoadMap(theSizeMap);

		const auto length = alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the algorithm was not performed!");

		const auto& chain = alg->Mesh();

		auto paired = std::make_tuple(chain, length);
		return std::move(paired);
	}

	auto DiscreteCurves
	(
		const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
		const std::shared_ptr<Geo2d_MetricPrcsr>& theSizeMap, 
		const std::shared_ptr<Mesh_Curve_Info>& theInfo
	)
	{
		std::map
			<
			Standard_Integer, 
			std::shared_ptr<Entity_Polygon<std::pair<Pnt2d, Standard_Real>>>
			> chainMap;
		
		Standard_Real sumLen = 0;
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);

			auto [chain, len] = DiscreteCurve(x, theSizeMap, theInfo);
			
			sumLen += len;

			auto paired = std::make_pair(x->Index(), std::move(chain));
			auto insert = chainMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "unable to insert the item into the map: duplicate data?" << endl
					<< abort(FatalError);
			}
		}
		auto paired = std::make_tuple(std::move(chainMap), sumLen);
		return std::move(paired);
	}

	auto CalcMaxCurvature
	(
		const std::shared_ptr<Pln_Curve>& theCurve, 
		const std::vector<Standard_Real>& xs
	)
	{
		const auto& geometry = theCurve->Geometry();
		Debug_Null_Pointer(geometry);

		auto maxCurvature = (Standard_Real)0.;
		for (auto x : xs)
		{
			auto curvature = Cad2d_CmptLib::Curvature(geometry, x);
			if (curvature > maxCurvature) maxCurvature = curvature;
		}
		return maxCurvature;
	}

	auto CalcParameters
	(
		const Standard_Real x0,
		const Standard_Real x1, 
		const Standard_Integer n
	)
	{
		if (n < 1)
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid nb. of segments has been detected!" << endl
				<< abort(FatalError);
		}
		std::vector<Standard_Real> xs;
		xs.reserve(n);

		const auto du = (x1 - x0) / (Standard_Real)n;
		for (size_t k = 0; k < n; k++)
		{
			xs.push_back(x0 + 0.5*k*du);
		}
		return std::move(xs);
	}

	void SmoothingH
	(
		std::vector<Standard_Real>& Hs,
		const Standard_Real underRelax,
		const Standard_Integer nbIters
	)
	{
		std::vector<Standard_Real> nHs(Hs.size() - 1, 0);
		for (size_t iter = 1; iter <= nbIters; iter++)
		{
			for (size_t i = 0; i < nHs.size(); i++)
			{
				nHs[i] = MEAN(Hs[i], Hs[i + 1]);
			}

			for (size_t i = 1; i < Hs.size() - 1; i++)
			{
				auto hm = MEAN(nHs[i - 1], nHs[i]);
				auto dh = hm - Hs[i];

				Hs[i] += underRelax * dh;
			}
		}
	}

	template<class T>
	auto FindItem
	(
		const Standard_Integer theIndex,
		const std::map<Standard_Integer, std::shared_ptr<T>>& theMap
	)
	{
		auto iter = theMap.find(theIndex);
		if (iter IS_EQUAL theMap.end())
		{
			FatalErrorIn(FunctionSIG)
				<< "the item is not in the map!" << endl
				<< abort(FatalError);
		}
		return iter->second;
	}

	auto CalcH
	(
		const std::shared_ptr<Entity_Polygon<std::pair<Pnt2d, Standard_Real>>>& thePolygon,
		const std::shared_ptr<Pln_Curve>& theCurve, 
		const Standard_Real sinSpanAngle, 
		const Standard_Real baseSize, 
		const Standard_Real minSize,
		const Standard_Integer nbSegments, 
		const Standard_Boolean randPts
	)
	{
		const auto& myCurve = *theCurve;
		const auto& points = thePolygon->Points();

		std::vector<Standard_Real> hs;
		hs.reserve(points.size() - 1);

		for (size_t k = 0; k < points.size() - 1; k++)
		{
			auto par0 = points[k].second;
			auto par1 = points[k + 1].second;

			auto xs = CalcParameters(par0, par1, nbSegments);

			auto hm = std::min(baseSize, std::max(2.0*sinSpanAngle / CalcMaxCurvature(theCurve, xs), minSize));
#ifdef _DEBUG
			if (hm <= gp::Resolution())
			{
				FatalErrorIn(FunctionSIG)
					<< "zero value in size has been detected!" << endl
					<< abort(FatalError);
			}
#endif // _DEBUG
			hs.push_back(hm);
		}

		std::vector<Standard_Real> Hs;
		Hs.reserve(points.size());

		Hs[0] = hs[0];
		for (size_t i = 1; i < hs.size() - 1; i++)
		{
			Hs[i] = MEAN(hs[i - 1], hs[i]);
		}
		Hs[Hs.size() - 1] = hs[hs.size() - 1];

		return std::move(Hs);
	}

	auto CalcH
	(
		const std::map
		<
		Standard_Integer, 
		std::shared_ptr<Entity_Polygon<std::pair<Pnt2d, Standard_Real>>>
		>& theChains,
		const std::map<Standard_Integer, std::shared_ptr<Pln_Curve>>& theCurves,
		const Standard_Real theSpanAngle,
		const Standard_Real baseSize, 
		const Standard_Real minSize,
		const Standard_Integer nbSegments,
		const Standard_Boolean randPts,
		const Standard_Real underRelax,
		const Standard_Integer nbIters
	)
	{
		const auto sinAngle = std::sin(theSpanAngle / 2.0);

		std::map<Standard_Integer, std::shared_ptr<std::vector<Standard_Real>>> hMap;
		for (const auto& x : theChains)
		{
			Debug_Null_Pointer(x.second);

			const auto& poly = x.second;
			auto curve = FindItem(x.first, theCurves);
			Debug_Null_Pointer(curve);

			auto hs = CalcH(poly, curve, sinAngle, baseSize, minSize, nbSegments, randPts);

			SmoothingH(hs, underRelax, nbIters);

			auto hsPtr = std::make_shared<std::vector<Standard_Real>>(std::move(hs));
			auto paired = std::make_pair(x.first, std::move(hsPtr));
			auto insert = hMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}
		return std::move(hMap);
	}

	auto RetrieveCurveMap(const std::vector<std::shared_ptr<Pln_Curve>>& theCurves)
	{
		std::map<Standard_Integer, std::shared_ptr<Pln_Curve>> curveMap;
		for (const auto& x : theCurves)
		{
			Debug_Null_Pointer(x);
			auto paired = std::make_pair(x->Index(), x);
			auto insert = curveMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}		
		}
		return std::move(curveMap);
	}

	auto RetrieveCoords
	(
		const std::map
		<
		Standard_Integer, 
		std::shared_ptr<Entity_Polygon<std::pair<Pnt2d, Standard_Real>>>
		>& theChains
	)
	{
		std::vector<Pnt2d> coords;
		Standard_Integer nbPts = 0;
		for (const auto& x : theChains)
		{
			Debug_Null_Pointer(x.second);
			const auto& poly = *x.second;

			nbPts += poly.NbPoints();
		}
		coords.reserve(nbPts);

		for (const auto& x : theChains)
		{
			Debug_Null_Pointer(x.second);
			const auto& poly = *x.second;

			for (const auto& c : poly.Points())
			{
				coords.push_back(c.first);
			}
		}
		return std::move(coords);
	}
}

namespace tnbLib
{

	struct NodeTree
	{
		NodeTree(const Pnt2d& theCoord)
			: coord(theCoord)
		{}

		Pnt2d coord;

		typedef Pnt2d ptType;
	};

	class QuadTreeObject
	{

	public:

		QuadTreeObject(const std::vector<Pnt2d>&, const Standard_Real tol);

		Geo_AdTree<NodeTree*> engine;

		Standard_Integer maxNbPts;
		Standard_Integer maxLevel;

		static Standard_Boolean Subdivide(const Entity2d_Box&, const QuadTreeObject* t);
	};
}

namespace tnbLib
{
	auto Merge(const std::vector<Pnt2d>& theCoords, const Standard_Real tol)
	{
		auto b = Geo_BoxTools::GetBox(theCoords, 0);
		const auto d = b.Diameter();
		if (d <= tol)
		{
			FatalErrorIn(FunctionSIG)
				<< "diameter of the domain is smaller than the tolerance!" << endl
				<< abort(FatalError);
		}

		b.Expand(d*1.0E-3);

		const auto radius = d*tol;
		const auto radius2 = radius * radius;

		Geo_AdTree<NodeTree*> alg;
		alg.SetGeometryRegion(b);
		alg.SetGeometryCoordFunc([](NodeTree* const& pt) ->const auto&{return pt->coord; });

		for (const auto& x : theCoords)
		{
			std::vector<NodeTree*> items;
			alg.GeometrySearch(Geo_BoxTools::GetBox(x, radius), items);

			if (items.size())
			{
				Standard_Boolean cond = Standard_False;
				for (const auto& node : items)
				{
					if (x.SquareDistance(node->coord) <= radius2)
					{
						cond = Standard_True;
						break;
					}
				}
				if (NOT cond)
				{
					auto node = new NodeTree(x);
					alg.InsertToGeometry(node);
				}
			}
		}
		return std::move(alg);
	}
}

tnbLib::QuadTreeObject::QuadTreeObject(const std::vector<Pnt2d>& theCoords, const Standard_Real tol)
	: maxNbPts(1)
	, maxLevel(6)
{
	auto b = Geo_BoxTools::GetBox(theCoords, 0);
	b.Expand(b.Diameter()*1.0E-3);

	engine = Merge(theCoords, tol);
}

Standard_Boolean 
tnbLib::QuadTreeObject::Subdivide(const Entity2d_Box & b, const QuadTreeObject * t)
{
#ifdef _DEBUG
	if (t->maxNbPts < 1)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid max. nb of points in leaf has been detected!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	std::vector<NodeTree*> nodes;
	t->engine.GeometrySearch(b, nodes);

	if (nodes.size() > t->maxNbPts)
	{
		return Standard_True;
	}
	return Standard_False;
}

namespace tnbLib
{
	void SetSources
	(
		const Entity_Polygon<std::pair<Pnt2d, Standard_Real>>& thePoly,
		const std::vector<Standard_Real>& theHs, 
		const Standard_Real baseSize, 
		GeoMesh2d_Background& theMesh
	)
	{
		const auto& mesh = theMesh.Mesh();
		const auto& poly = thePoly.Points();

		auto& sources = theMesh.Sources();
		sources.resize(mesh->Elements().size(), baseSize);

		auto start = mesh->FirstElement();
		for (size_t i = 0; i < poly.size(); i++)
		{
			const auto& coord = poly[i].first;
			auto h = theHs[i];

			const auto current = mesh->TriangleLocation(start, coord);
			if (NOT current)
			{
				FatalErrorIn(FunctionSIG)
					<< "the point is outside of the mesh!" << endl
					<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
					<< " - coordinates of the point: " << coord << endl
					<< abort(FatalError);
			}

			const auto& currentRef = *current;
			auto n0 = Index_Of(currentRef.Node0()->Index());
			auto n1 = Index_Of(currentRef.Node1()->Index());
			auto n2 = Index_Of(currentRef.Node2()->Index());

			auto v0 = sources[n0];
			auto v1 = sources[n1];
			auto v2 = sources[n2];

			if (v0 < h) sources[n0] = v0;
			if (v1 < h) sources[n1] = v1;
			if (v2 < h) sources[n2] = v2;

			start = current;
		}
	}

	void SetSources
	(
		const std::map<Standard_Integer, std::shared_ptr<Entity_Polygon<std::pair<Pnt2d, Standard_Real>>>>& theChains,
		const std::map<Standard_Integer, std::shared_ptr<std::vector<Standard_Real>>>& theHsMap,
		const Standard_Real baseSize, GeoMesh2d_Background& theMesh
	)
	{
		for (const auto& x : theChains)
		{
			Debug_Null_Pointer(x.second);
			const auto& poly = *x.second;

			const auto id = x.first;
			auto hs = FindItem(id, theHsMap);
			Debug_Null_Pointer(hs);

			SetSources(poly, *hs, baseSize, theMesh);
		}
	}
}

template<>
Standard_Real tnbLib::Mesh2d_CurveRemesh::Discretize
(
	const std::shared_ptr<Geo2d_SizeFunction>& theSizeFun
)
{
	const auto gMetricInfo = 
		std::make_shared<Geo_MetricPrcsr_Info>
		(
			sysLib::gl_geo_metric_processor_integration_info
			);
	const auto metricMap = 
		std::make_shared<Geo2d_MetricPrcsr>
		(
			theSizeFun, 
			gMetricInfo
			);
	Debug_Null_Pointer(metricMap);

	const auto curveMap = RetrieveCurveMap(Curves());

	const auto[chainMap, totLen] = DiscreteCurves(Curves(), metricMap, MeshInfo());

	const auto hsMap = 
		CalcH
		(
			chainMap, curveMap, 
			SpanAngle(), BaseSize(), 
			MinSize(), NbSamples(), 
			IsUsedRandSamples(), SmoothingFactor(),
			MaxNbSmoothing()
		);

	Entity2d_Box regionBox;
	std::vector<Entity2d_Box> boxes;
	{
		auto coords = RetrieveCoords(chainMap);

		QuadTreeObject obj(coords, 1.0E-5);
		coords.clear();

		if (verbose)
		{
			Info << " - Min. nb. of subdivisions: " << MinNbSubdivisions() << endl;
			Info << " - Max. nb. of subdivisions: " << MaxNbSubdivisions() << endl;
			Info << " - Unbalancing: " << UnbalancingLev() << endl;
			Info << endl;
		}

		Global_Timer myTimer;
		myTimer.SetInfo(Global_TimerInfo_ms);

		Geo2d_ApprxSpace<QuadTreeObject> tree;

		tree.SetMinLevel(MinNbSubdivisions());
		tree.SetMaxLevel(MaxNbSubdivisions());
		tree.SetMaxUnbalancingLevel(UnbalancingLev());

		tree.SetObject(&obj);
		tree.SetSubdivider(&QuadTreeObject::Subdivide);
		tree.SetDomain(obj.engine.GeometryBoundingBox());

		tree.Init();
		tree.Perform();

		boxes = tree.RetrieveBoxes();
		tree.Clear();

		regionBox = obj.engine.GeometryBoundingBox();
	}

	if (verbose)
	{
		Info << " - The Whole domain is approximated in: " << global_time_duration << " ms." << endl;
		Info << endl;
	}

	if (verbose)
	{
		Info << " Triangulation of the domain..." << endl;
		Info << endl;
	}
	Entity2d_Triangulation triangulation;
	{
		Global_Timer myTimer;
		myTimer.SetInfo(Global_TimerInfo_ms);
		triangulation = Geo_BoxTools::GetTriangulation(boxes);
	}

	if (verbose)
	{
		Info << " - the domain is triangulated in: " << global_time_duration << " ms." << endl;
		Info << endl;
	}

	if (verbose)
	{
		Info << " Constructing the background mesh..." << endl;
		Info << endl;
	}
	const auto bMesh = std::make_shared<GeoMesh2d_Background>();
	Debug_Null_Pointer(bMesh);

	bMesh->Mesh()->Construct(triangulation);
	bMesh->InitiateCurrentElement();
	bMesh->SetBoundingBox(std::move(regionBox));

	if (verbose)
	{
		Info << " Setting the sources into the background mesh..." << endl;
		Info << endl;
	}
	SetSources(chainMap, hsMap, BaseSize(), *bMesh);

	auto hvInfo = std::make_shared<GeoMesh_Background_SmoothingHvCorrection_Info>();
	Debug_Null_Pointer(hvInfo);
	hvInfo->SetMaxNbIters(sysLib::gl_background_hv_correction_info->MaxNbIters());
	hvInfo->SetFactor(Mesh_VariationRate::Rate(VariationRate()));

	if (verbose)
	{
		Info << " Applying Hv-correction..." << endl;
		Info << " - Max. nb. of iterations: " << hvInfo->MaxNbIters() << endl;
		Info << endl;
	}
	bMesh->HvCorrection(hvInfo);
	
	theBackmesh_ = std::move(bMesh);
	return totLen;
}

template<>
void tnbLib::Mesh2d_CurveRemesh::Perform()
{
	if (BaseSize() <= 0)
	{
		FatalErrorIn(FunctionSIG)
			<< "the base size is zero" << endl
			<< abort(FatalError);
	}

	if (NOT MeshInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been loaded!" << endl
			<< abort(FatalError);
	}

	if (Curves().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "no curve has been loaded!" << endl
			<< abort(FatalError);
	}

	auto uniSize = std::make_shared<GeoSizeFun2d_Uniform>(BaseSize(), *BoundingBox());
	Debug_Null_Pointer(uniSize);

	const auto length0 = Discretize(uniSize);

	for (size_t iter = 1; iter <= MaxNbIterations(); iter++)
	{

	}

	Change_IsDone() = Standard_True;
}