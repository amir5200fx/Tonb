#include <Mesh3d_SetEdgeSources.hxx>

#include <Mesh3d_SetSourcesAdaptor.hxx>
#include <Mesh3d_SetSourcesNode.hxx>
#include <Mesh2d_Element.hxx>
#include <MeshBase_Tools.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_Node.hxx>
#include <Geo3d_AttrbBalPrTree.hxx>
#include <Geo_BoxTools.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Triangle.hxx>
#include <Entity_Segment.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Real tnbLib::Mesh3d_SetEdgeSources::DEFAULT_TOLERANCE(1.0E-6);

namespace tnbLib
{

	namespace setSources
	{
		// old comparator style [8/19/2022 Amir]
		struct ElementComparator
		{

			bool operator()(const std::shared_ptr<Mesh3d_Element>& lhs, const std::shared_ptr<Mesh3d_Element>& rhs)
			{
				Debug_Null_Pointer(lhs);
				Debug_Null_Pointer(rhs);
				return lhs->Index() < rhs->Index();
			}
		};

		struct FacetComparator
		{

			bool operator()(const std::shared_ptr<Mesh3d_Facet>& lhs, const std::shared_ptr<Mesh3d_Facet>& rhs)
			{
				Debug_Null_Pointer(lhs);
				Debug_Null_Pointer(rhs);
				return lhs->Index() < rhs->Index();
			}
		};

		struct NodeComparator
		{

			bool operator()(const std::shared_ptr<Mesh3d_Node>& lhs, const std::shared_ptr<Mesh3d_Node>& rhs)
			{
				Debug_Null_Pointer(lhs);
				Debug_Null_Pointer(rhs);
				return lhs->Index() < rhs->Index();
			}
		};

		auto nodeCompt =
			[]
		(
			const std::shared_ptr<Mesh3d_Node>& lhs,
			const std::shared_ptr<Mesh3d_Node>& rhs
			)
		{
			Debug_Null_Pointer(lhs);
			Debug_Null_Pointer(rhs);
			return lhs->Index() < rhs->Index();
		};

		auto elemntCompt =
			[]
		(
			const std::shared_ptr<Mesh3d_Element>& lhs,
			const std::shared_ptr<Mesh3d_Element>& rhs
			)
		{
			Debug_Null_Pointer(lhs);
			Debug_Null_Pointer(rhs);
			return lhs->Index() < rhs->Index();
		};

		auto facetCompt =
			[]
		(
			const std::shared_ptr<Mesh3d_Facet>& lhs,
			const std::shared_ptr<Mesh3d_Facet>& rhs
			)
		{
			Debug_Null_Pointer(lhs);
			Debug_Null_Pointer(rhs);
			return lhs->Index() < rhs->Index();
		};
	}

	// old comparator style [8/19/2022 Amir]
	typedef std::set<std::shared_ptr<Mesh3d_Node>, setSources::NodeComparator> NodeSet;
	typedef std::set<std::shared_ptr<Mesh3d_Facet>, setSources::FacetComparator> FacetSet;
	typedef std::set<std::shared_ptr<Mesh3d_Element>, setSources::ElementComparator> ElementSet;

	typedef Geo3d_AttrbBalPrTree<std::shared_ptr<meshLib::setSources::Node>, Mesh3d_Element>
		SearchEngine;

	auto RetrieveNodes
	(
		const ElementSet& theElements
	)
	{	
		NodeSet nodes;
		for (const auto& x : theElements)
		{
			Debug_Null_Pointer(x);
			nodes.insert(x->Node0());
			nodes.insert(x->Node1());
			nodes.insert(x->Node2());
			nodes.insert(x->Node3());
		}
		return std::move(nodes);
	}

	void SetH
	(
		std::vector<Standard_Real>& theSources, 
		const Standard_Integer id, 
		const Standard_Real theH
	)
	{
		if (theSources.at(id) <= theH)
		{
			return;
		}
		theSources.at(id) = theH;
	}

	void SetSources
	(
		const ElementSet& theElements,
		const std::shared_ptr<GeoMesh3d_SingleBackground>& theBack,
		const Standard_Real theH
	)
	{
		auto& sourcesRef = theBack->Sources();
		auto nodes = RetrieveNodes(theElements);
		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			try
			{
				SetH(sourcesRef, Index_Of(x->Index()), theH);
			}
			catch (const std::exception&)
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid background mesh has been detected." << endl
					<< abort(FatalError);
			}
		}
	}

	auto RetrieveTets(const std::vector<SearchEngine::leafNode*>& theLeaves)
	{
		std::vector<std::shared_ptr<Mesh3d_Element>> elements;
		for (const auto& x : theLeaves)
		{
			Debug_Null_Pointer(x);
			for (const auto& t : x->Tets())
			{
				Debug_Null_Pointer(t.second);
				elements.push_back(t.second);
			}
		}
		return std::move(elements);
	}

	auto RetrieveFacets(const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements)
	{
		FacetSet faces;
		for (const auto& x : theElements)
		{
			Debug_Null_Pointer(x);
			auto[f0, f1, f2, f3] = x->Facets();
			faces.insert(f0);
			faces.insert(f1);
			faces.insert(f2);
			faces.insert(f3);
		}
		return std::move(faces);
	}

	auto GetTriangle(const Mesh3d_Facet& theFace)
	{
		auto[p0, p1, p2] = theFace.RetrieveCoords();
		Entity3d_Triangle t(std::move(p0), std::move(p1), std::move(p2));
		return std::move(t);
	}

	auto RetrieveIntsctElements
	(
		const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements,
		const Pnt3d& theP0,
		const Pnt3d& theP1
	)
	{
		Entity3d_SegmentRef seg(theP0, theP1);
		auto faces = RetrieveFacets(theElements);

		ElementSet elements;
		for (const auto& x : faces)
		{
			Debug_Null_Pointer(x);
			auto[p0, p1, p2] = x->RetrieveCoords();

			auto t = GetTriangle(*x);
			if (Geo_Tools::IsIntersect_cgal(seg, t))
			{
				auto left = x->LeftElement().lock();
				auto right = x->RightElement().lock();
				Debug_If_Condition(NOT left AND NOT right);
				elements.insert(left);
				elements.insert(right);
			}
		}
		return std::move(elements);
	}

	void SetEdge
	(
		const Pnt3d& theP0, 
		const Pnt3d& theP1, 
		const Standard_Real theH, 
		const SearchEngine& theEnginge, 
		const std::shared_ptr<GeoMesh3d_SingleBackground>& theBack
	)
	{
		auto b = Geo_BoxTools::GetBox(theP0, theP1);
		auto leaves = theEnginge.RetrieveLeaves(*b);
		auto elemnts = RetrieveTets(leaves);

		auto intsctElements = RetrieveIntsctElements(elemnts, theP0, theP1);
		
		SetSources(intsctElements, theBack, theH);
	}

	void SetSources
	(
		const Entity3d_Chain& thePoly,
		const std::vector<Standard_Real>& theHs, 
		const SearchEngine& theEngine, 
		const std::shared_ptr<GeoMesh3d_SingleBackground>& theBack
	)
	{
		const auto& points = thePoly.Points();
		for (const auto& x : thePoly.Connectivity())
		{
			auto v0 = Index_Of(x.Value(0));
			auto v1 = Index_Of(x.Value(1));

			const auto& P0 = points.at(v0);
			const auto& P1 = points.at(v1);

			auto h = std::min(theHs.at(v0), theHs.at(v1));

			SetEdge(P0, P1, h, theEngine, theBack);
		}
	}
}

void tnbLib::Mesh3d_SetEdgeSources::Perform()
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}

	const auto& meshData = Mesh()->Mesh();
	Debug_Null_Pointer(meshData);

	// Register the elements in a tree [8/18/2022 Amir]
	SearchEngine engine;
	engine.SetMaxUnbalancing(2);
	engine.SetGeometryCoordFunc(&meshLib::setSources::Node::GetCoord);
	engine.SetGeometryRegion(Mesh()->BoundingBox());
	engine.BUCKET_SIZE = 1;

	const auto mergCrit = Tolerance()*Mesh()->BoundingBox().Diameter();

	for (const auto& x : meshData->Elements())
	{
		Debug_Null_Pointer(x);

		auto c = x->Centre();
		auto b = Geo_BoxTools::GetBox<Pnt3d>(c, mergCrit);

		std::vector<std::shared_ptr<meshLib::setSources::Node>> items;
		engine.GeometrySearch(b, items);
		if (items.empty())
		{
			auto node = std::make_shared<meshLib::setSources::Node>(std::move(c));
			Debug_Null_Pointer(node);
			engine.InsertToGeometry(node);
		}
		else
		{
			Standard_Real minDis = RealLast();
			for (const auto& i : items)
			{
				auto dis = i->Coord().Distance(c);
				if (dis < minDis)
				{
					minDis = dis;
				}
			}
			if (minDis > mergCrit)
			{
				auto node = std::make_shared<meshLib::setSources::Node>(std::move(c));
				Debug_Null_Pointer(node);
				engine.InsertToGeometry(node);
			}
		}
	}
	
	// Register the elements into the leaves [8/18/2022 Amir]
	for (const auto& x : meshData->Elements())
	{
		Debug_Null_Pointer(x);

		auto b = MeshBase_Tools::CalcBoundingBox(x);
		Debug_Null_Pointer(b);

		b->Expand(Tolerance()*b->Diameter());

		// Searching into the engine [8/14/2022 Amir]
		auto items = engine.RetrieveLeaves(*b);
		for (const auto& i : items)
		{
			Debug_Null_Pointer(i);
			i->InsertToTets(x);
		}
	}

	SetSources(*Edges(), Values(), engine, Mesh());

	Change_IsDone() = Standard_True;
}