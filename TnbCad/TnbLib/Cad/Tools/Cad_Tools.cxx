#include <Cad_Tools.hxx>

#include <Pln_Tools.hxx>
#include <TModel_FixWire_Info.hxx>
#include <TModel_System.hxx>
#include <TModel_Curve.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_Edge.hxx>
#include <TModel_CmpEdge.hxx>
#include <TModel_SingularEdge.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Vertex.hxx>
#include <TModel_Ring.hxx>
#include <TModel_Paired.hxx>
#include <TModel_Wire.hxx>
#include <Cad3d_TModel.hxx>
#include <Cad_BlockEntity.hxx>
#include <Cad_EntityManager.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Chain.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Adt_AvlTree.hxx>
#include <Geo_Tools.hxx>
#include <Merge3d_Chain.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Geom_TrimmedCurve.hxx>
#include <Bnd_Box.hxx>
#include <BRep_Tool.hxx>
#include <BRepLib.hxx>
#include <BRepBndLib.hxx>
#include <BRepTools.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopLoc_Location.hxx>
#include <ShapeFix_Wire.hxx>

Standard_Boolean 
tnbLib::Cad_Tools::IsBounded
(
	const Handle(Geom_Curve)& theCurve
)
{
	return (Standard_Boolean)Handle(Geom_BoundedCurve)::DownCast(theCurve);
}

tnbLib::Entity3d_Box 
tnbLib::Cad_Tools::BoundingBox
(
	const Bnd_Box & theBox
)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;
	Standard_Real Zmin, Zmax;

	theBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity3d_Box 
		box(Pnt3d(Xmin, Ymin, Zmin), Pnt3d(Xmax, Ymax, Zmin));
	return std::move(box);
}

tnbLib::Entity3d_Box 
tnbLib::Cad_Tools::BoundingBox
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	Bnd_Box B;
	for (const auto& x : theSurfaces)
	{
		Debug_Null_Pointer(x);
		BRepBndLib::Add(x->Face(), B);
	}
	auto b = BoundingBox(B);
	return std::move(b);
}

Bnd_Box 
tnbLib::Cad_Tools::BoundingBox
(
	const TopoDS_Shape & theShape
)
{
	Bnd_Box B;
	BRepBndLib::Add(theShape, B);

	return std::move(B);
}

std::shared_ptr<tnbLib::Entity3d_Triangulation> 
tnbLib::Cad_Tools::Triangulation
(
	const Poly_Triangulation & theTriangulation
)
{
	auto triangulation = std::make_shared<Entity3d_Triangulation>();
	Debug_Null_Pointer(triangulation);

	auto& pts = triangulation->Points();
	auto& indices = triangulation->Connectivity();

	pts.reserve(theTriangulation.NbNodes());
	for (const auto& x : theTriangulation.Nodes())
	{
		pts.push_back(x);
	}

	indices.reserve(theTriangulation.NbTriangles());
	for (const auto& x : theTriangulation.Triangles())
	{
		Standard_Integer i0, i1, i2;
		x.Get(i0, i1, i2);

		connectivity::triple I;
		I.Value(0) = i0;
		I.Value(1) = i1;
		I.Value(2) = i2;

		indices.push_back(std::move(I));
	}
	return std::move(triangulation);
}

Handle(Geom_Curve)
tnbLib::Cad_Tools::ConvertToTrimmed
(
	const Handle(Geom_Curve)& theCurve, 
	const Standard_Real u0,
	const Standard_Real u1
)
{
	Handle(Geom_Curve) trimmed =
		new Geom_TrimmedCurve(theCurve, u0, u1);
	return std::move(trimmed);
}

std::shared_ptr<tnbLib::TModel_Edge> 
tnbLib::Cad_Tools::GetEdge
(
	const TopoDS_Edge & theEdge,
	const TopoDS_Face & theFace
)
{
	Standard_Real u0, u1, U0, U1;
	TopLoc_Location pLoc, eLoc;
	auto patch = BRep_Tool::Surface(theFace, pLoc);

	if (NOT BRep_Tool::SameRange(theEdge))
	{
		BRepLib::SameRange(theEdge);
	}

	if (NOT BRep_Tool::SameParameter(theEdge))
	{
		BRepLib::SameParameter(theEdge);
	}

	if (NOT BRep_Tool::SameParameter(theEdge))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameParameter flag" << endl
			<< abort(FatalError);
	}

	if (NOT BRep_Tool::SameRange(theEdge))
	{
		FatalErrorIn(FunctionSIG)
			<< "It's supposed that the edge has SameRange flag" << endl
			<< abort(FatalError);
	}

	auto pCurve0 = BRep_Tool::CurveOnSurface(theEdge, patch, pLoc, u0, u1);
	auto pCurve = Handle(Geom2d_Curve)::DownCast(pCurve0->Copy());

	auto Curve = BRep_Tool::Curve(theEdge, eLoc, U0, U1);

	if (theEdge.Orientation() IS_EQUAL TopAbs_REVERSED)
	{
		auto temp = u1;
		u1 = pCurve->ReversedParameter(u0);
		u0 = pCurve->ReversedParameter(temp);
		pCurve->Reverse();
	}

	if (NOT Pln_Tools::IsBounded(pCurve))
	{
		pCurve = Pln_Tools::ConvertToTrimmedCurve(pCurve, u0, u1);
	}

	auto curveOnPlane = std::make_shared<TModel_ParaCurve>(pCurve);

	std::shared_ptr<TModel_Edge> newEdge;

	if (Curve)
	{
		if (NOT IsBounded(Curve))
		{
			Curve = ConvertToTrimmed(Curve, U0, U1);
		}

		auto curveOnSurface = std::make_shared<TModel_Curve>(Curve);
		newEdge = std::make_shared<TModel_Edge>(curveOnSurface, curveOnPlane);
	}
	else
	{
		newEdge = std::make_shared<TModel_SingularEdge>(curveOnPlane);
	}
	return std::move(newEdge);
}

std::shared_ptr<tnbLib::TModel_Edge> 
tnbLib::Cad_Tools::GetEdge
(
	const Standard_Integer theIndex, 
	const TopoDS_Edge & theEdge, 
	const TopoDS_Face & theFace
)
{
	auto edge = GetEdge(theEdge, theFace);
	Debug_Null_Pointer(edge);

	edge->SetIndex(theIndex);
	return std::move(edge);
}

std::shared_ptr<tnbLib::TModel_Surface> 
tnbLib::Cad_Tools::GetSurface
(
	const TopoDS_Face & theFace
)
{
	//const auto forwardFace = theFace;
	const auto forwardFace = TopoDS::Face(theFace.Oriented(TopAbs_FORWARD));

	auto cmpEdge = std::make_shared<TModel_CmpEdge>();
	Debug_Null_Pointer(cmpEdge);

	auto& outter_edges = cmpEdge->ChangeEdges();

	const auto Tol = sysLib::tmodel_fix_wire_info->Tolerance();
	Standard_Integer K = 0;
	Standard_Integer wireIndex = 0;

	const auto outer_wire = BRepTools::OuterWire(forwardFace);

	if (outer_wire.IsNull())
	{
		FatalErrorIn(FunctionSIG)
			<< "Null outer wire" << endl
			<< abort(FatalError);
	}

	ShapeFix_Wire SFWF(outer_wire, forwardFace, Tol);

	SFWF.SetPrecision(sysLib::tmodel_fix_wire_info->Precision());
	SFWF.SetMaxTolerance(sysLib::tmodel_fix_wire_info->MaxTolerance());
	SFWF.SetMinTolerance(sysLib::tmodel_fix_wire_info->MinTolerance());

	SFWF.FixReorder();
	SFWF.ClosedWireMode() = Standard_True;
	SFWF.FixClosed();
	SFWF.FixConnected();

	SFWF.Perform();

	auto fixed_outer_wire = SFWF.Wire();

	for (
		BRepTools_WireExplorer anEdgeExp(fixed_outer_wire);
		anEdgeExp.More();
		anEdgeExp.Next()
		)
	{
		K++;

		auto edge = TopoDS::Edge(anEdgeExp.Current());
		auto new_edge = GetEdge(K, edge, forwardFace);

		outter_edges.push_back(new_edge);
	}

	auto outerWire = std::make_shared<TModel_Wire>(++wireIndex, cmpEdge);
	std::shared_ptr<std::vector<std::shared_ptr<TModel_Wire>>> Qwire;
	for (
		TopExp_Explorer aWireExp(forwardFace, TopAbs_WIRE);
		aWireExp.More();
		aWireExp.Next()
		)
	{
		auto wire = TopoDS::Wire(aWireExp.Current());

		if (wire.IsNull()) continue;
		if (wire IS_EQUAL outer_wire) continue;
		// has inner wire

		auto cmpEdge = std::make_shared<TModel_CmpEdge>();
		Debug_Null_Pointer(cmpEdge);

		auto& Inner_edges = cmpEdge->ChangeEdges();

		ShapeFix_Wire SFWF(wire, forwardFace, Tol);

		SFWF.SetPrecision(sysLib::tmodel_fix_wire_info->Precision());
		SFWF.SetMaxTolerance(sysLib::tmodel_fix_wire_info->MaxTolerance());
		SFWF.SetMinTolerance(sysLib::tmodel_fix_wire_info->MinTolerance());

		SFWF.FixReorder();
		SFWF.ClosedWireMode() = Standard_True;
		SFWF.FixClosed();
		SFWF.FixConnected();

		SFWF.Perform();
		wire = SFWF.WireAPIMake();

		for (
			BRepTools_WireExplorer anEdgeExp(wire);
			anEdgeExp.More();
			anEdgeExp.Next()
			)
		{
			auto edge = TopoDS::Edge(anEdgeExp.Current());

			K++;

			Inner_edges.push_back(GetEdge(K, edge, forwardFace));
		}

		if (Inner_edges.empty())
		{
			FatalErrorIn("Cad3d_SolidTools::face_ptr Cad_Tools::GetSurface(const TopoDS_Face & theFace)")
				<< "Empty wire" << endl
				<< abort(FatalError);
		}

		auto innerWire = std::make_shared<TModel_Wire>(++wireIndex, cmpEdge);

		if (NOT Qwire) Qwire = std::make_shared<std::vector<std::shared_ptr<TModel_Wire>>>();
		Qwire->push_back(innerWire);
	}

	TopLoc_Location Location;
	auto geometry = BRep_Tool::Surface(forwardFace, Location);

	auto face =
		std::make_shared<TModel_Surface>(geometry, outerWire, Qwire);
	face->SetFace(theFace);

	return std::move(face);
}

std::vector<std::shared_ptr<tnbLib::TModel_Surface>> 
tnbLib::Cad_Tools::GetSurfaces
(
	const TopoDS_Shape & theShape
)
{
	Standard_Integer K = 0;
	std::vector<std::shared_ptr<TModel_Surface>> list;
	for (
		TopExp_Explorer aFaceExp(theShape.Oriented(TopAbs_FORWARD), TopAbs_FACE);
		aFaceExp.More();
		aFaceExp.Next()
		)
	{
		auto raw = TopoDS::Face(aFaceExp.Current());

		if (raw.IsNull())
		{
			continue;
		}

		auto face = GetSurface(raw);

		face->SetIndex(++K);

		list.push_back(face);
	}

	return std::move(list);
}

std::shared_ptr<tnbLib::Cad3d_TModel> 
tnbLib::Cad_Tools::MakeSolid
(
	const TopoDS_Shape & theShape,
	const Standard_Real theTolerance
)
{
	auto surfaces = GetSurfaces(theShape);

	auto solid = MakeSolid(surfaces, theTolerance);

	Debug_Null_Pointer(solid);
	if (solid) solid->SetShape(theShape);

	return std::move(solid);
}

namespace tnbLib
{

	namespace tModel
	{

		static Standard_Real squareMaxDistance_1
		(
			const std::shared_ptr<TModel_Edge>& theEdge0,
			const std::shared_ptr<TModel_Edge>& theEdge1
		)
		{
			Debug_Null_Pointer(theEdge0->Curve());
			Debug_Null_Pointer(theEdge1->Curve());

			const auto& geometry0 = *theEdge0->Curve();
			const auto& geometry1 = *theEdge1->Curve();

			return SquareDistance(geometry0.Value_normParam(0.5), geometry1.Value_normParam(0.5));
		}

		static void MakeStaticChain
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& Edges,
			Entity3d_Chain& Chain
		)
		{
			auto& Points = Chain.Points();
			auto& Indices = Chain.Connectivity();

			Points.resize(2 * Edges.size());
			Indices.reserve(Edges.size());

			Standard_Integer IP = 0;
			for (const auto& x : Edges)
			{
				Debug_Null_Pointer(x);
				Debug_Null_Pointer(x->Curve());

				const auto& curve = *x->Curve();

				Points[IP] = curve.FirstCoord();
				IP++;

				Points[IP] = curve.LastCoord();
				IP++;

				connectivity::dual edge;
				edge.Value(0) = IP - 1;
				edge.Value(1) = IP;

				Indices.push_back(edge);
			}
		}

		static void Pairing
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges
		)
		{
			if (theEdges.size() < 2)
			{
				FatalErrorIn("void Pairing(const edgeList& theEdges)")
					<< "Invalid Solid" << endl
					<< abort(FatalError);
			}

			Adt_AvlTree<std::shared_ptr<TModel_Edge>> tree;
			tree.SetComparableFunction(&TModel_Edge::IsLess);

			for (const auto& x : theEdges)
				tree.Insert(x);

			if (tree.IsEmpty())
			{
				FatalErrorIn("void Pairing(const edgeList& theEdges)")
					<< "Invalid Solid" << endl
					<< abort(FatalError);
			}

			std::shared_ptr<TModel_Edge> edge;
			tree.Root(edge);
			tree.Remove(edge);

			while (NOT tree.IsEmpty())
			{
				const auto& vtx0 = edge->Vtx0();
				const auto& vtx1 = edge->Vtx1();

				std::shared_ptr<TModel_Vertex> vtx;
				if (vtx0->NbEdges() <= vtx1->NbEdges())
					vtx = vtx0;
				else
					vtx = vtx1;

				const auto& compareList = vtx->Edges();
				auto v0 = vtx0->Index();
				auto v1 = vtx1->Index();

				if (edge->IsRing())
				{
					auto ring = std::dynamic_pointer_cast<TModel_Ring>(edge);
					Debug_Null_Pointer(ring);

					auto tol2 = ring->Presicion()*ring->Presicion();

					for (const auto& w_compare : compareList)
					{
						auto compare = w_compare.second.lock();
						Debug_Null_Pointer(compare);

						if (compare IS_EQUAL edge) continue;

						auto compareRing = std::dynamic_pointer_cast<TModel_Ring>(compare);
						if (compareRing)
						{
							if (squareMaxDistance_1(ring, compareRing) <= tol2)
							{
								edge->SetPairedEdge(compare);
								compare->SetPairedEdge(edge);

								tree.Remove(compare);
							}
						}
					}
				}
				else
				{
					std::vector<std::shared_ptr<TModel_Edge>> paired;

					Debug_Null_Pointer(edge->Curve());
					auto tol2 = edge->Presicion()*edge->Presicion();

					for (const auto& w_compare : compareList)
					{
						auto compare = w_compare.second.lock();
						Debug_Null_Pointer(compare);

						if (compare IS_EQUAL edge) continue;

						if (Geo_Tools::IsPairedTwoSegments(v0, v1, compare->Vtx0()->Index(), compare->Vtx1()->Index()))
						{
							if (squareMaxDistance_1(edge, compare) <= tol2)
							{
								paired.push_back(compare);
							}

							//paired.push_back(compare);
						}
					}

					/*if (paired.empty())
				{
					cout << "nothing found!" << std::endl;
				}*/
					if (paired.size() > 1)
					{
						if (edge->PairedEdge().lock())
						{
							FatalErrorIn("void Pairing(const edgeList& theEdges)")
								<< "the solid is not a manifold type"
								<< abort(FatalError);
						}
					}

					if (paired.size() IS_EQUAL 1)
					{
						edge->SetPairedEdge(paired[0]);
						paired[0]->SetPairedEdge(edge);
					}
				}

				if (tree.IsEmpty()) break;

				tree.Root(edge);
				tree.Remove(edge);
			}
		}

		static void Assembly
		(
			const Entity3d_Chain& theChain,
			const std::vector<std::shared_ptr<TModel_Vertex>>& theVertices,
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges
		)
		{
			const auto& Indices = theChain.Connectivity();
			if (theEdges.size() NOT_EQUAL Indices.size())
			{
				FatalErrorIn("void Assembly()")
					<< "Contradictory Data" << endl
					<< abort(FatalError);
			}

			forThose(Index, 0, Indices.size() - 1)
			{
				auto v0 = Indices[Index].Value(0);
				auto v1 = Indices[Index].Value(1);

				auto vtx0 = theVertices[Index_Of(v0)];
				auto vtx1 = theVertices[Index_Of(v1)];

				Debug_Null_Pointer(vtx0);
				Debug_Null_Pointer(vtx1);

				Debug_Null_Pointer(theEdges[Index]);

				theEdges[Index]->Vtx0() = vtx0;
				theEdges[Index]->Vtx1() = vtx1;

				theEdges[Index]->SetIndex(Index + 1);

				if (v0 IS_EQUAL v1)
				{
					//! For ring configuration
					vtx0->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
				}
				else
				{
					vtx0->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
					vtx1->ImportToEdges(theEdges[Index]->Index(), theEdges[Index]);
				}
			}

			Pairing(theEdges);

			for (const auto& x : theVertices)
			{
				Debug_Null_Pointer(x);

				auto vertex = std::dynamic_pointer_cast<TModel_Vertex>(x);
				Debug_Null_Pointer(vertex);


				const auto& edgesAroundVertex = vertex->Edges();

				for (const auto& edge : edgesAroundVertex)
				{
					Debug_Null_Pointer(edge.second.lock());
					auto x = edge.second.lock();
					vertex->ImportToSurfaces_dup(x->Index(), x->Surface());
				}
			}
		}

		static void MakePointsOnSolid
		(
			const Entity3d_Chain& Chain,
			std::shared_ptr<TModel_VertexManager>& thePointsOnSolid,
			std::vector<std::shared_ptr<TModel_Vertex>>& thePts
		)
		{
			const auto& Points = Chain.Points();

			thePts.reserve(Points.size());

			Standard_Integer K = 0;
			for (const auto& x : Points)
			{
				auto vertex = std::make_shared<TModel_Vertex>(++K, x);
				thePts.push_back(vertex);
			}

			auto block = std::make_shared<Cad_BlockEntity<TModel_Vertex>>("Default Block Point", thePts);
			thePointsOnSolid = std::make_shared<TModel_VertexManager>("Default Block Point", block);
		}

		static void MakePairedEdges
		(
			const std::vector<std::shared_ptr<TModel_Edge>>& theEdges,
			std::shared_ptr<TModel_PairedManager>& thePairedEdges
		)
		{
			Adt_AvlTree<std::shared_ptr<TModel_Edge>> tree;
			tree.SetComparableFunction(&TModel_Edge::IsLess);

			tree.Insert(theEdges);

			std::shared_ptr<TModel_Edge> edge;
			tree.Root(edge);
			tree.Remove(edge);

			std::vector<std::shared_ptr<TModel_Paired>> QPaired;
			Standard_Integer k = 0;

			while (NOT tree.IsEmpty())
			{
				auto w_paired = edge->PairedEdge();
				auto paired = w_paired.lock();

				if (paired)
				{
					tree.Remove(paired);
				}

				auto pairedOnSolid = std::make_shared<TModel_Paired>(++k, edge, paired);
				QPaired.push_back(pairedOnSolid);

				edge->SetPaired(pairedOnSolid);
				if (paired) paired->SetPaired(pairedOnSolid);

				if (tree.IsEmpty()) break;

				tree.Root(edge);
				tree.Remove(edge);
			}

			auto block = std::make_shared<Cad_BlockEntity<TModel_Paired>>("Default Block Edge", QPaired);
			thePairedEdges = std::make_shared<TModel_PairedManager>("Default Block Edge", block);
		}

		static void MarchingOnShell
		(
			const std::shared_ptr<TModel_Surface>& Face,
			Adt_AvlTree<std::shared_ptr<TModel_Surface>>& tree,
			std::vector<std::shared_ptr<TModel_Entity>>& QShell
		)
		{
			tree.Remove(Face);
			QShell.push_back(Face);

			const auto edges = Face->RetrieveEdges();

			std::vector<std::shared_ptr<TModel_Edge>> pairedList;
			pairedList.reserve(edges.size());

			std::shared_ptr<TModel_Edge> null = nullptr;

			for (const auto& x : edges)
			{
				Debug_Null_Pointer(x);

				pairedList.push_back(x->PairedEdge().lock());
				x->SetPairedEdge(null);
			}

			for (const auto& x : pairedList)
			{
				if (x)
				{
					auto paired = x->PairedEdge().lock();
					if (paired)
					{
						Debug_Null_Pointer(paired->Surface().lock());
						MarchingOnShell(paired->Surface().lock(), tree, QShell);
					}
				}
			}
		}


		static void MakeFaces
		(
			const std::vector<std::shared_ptr<TModel_Surface>>& theList,
			std::shared_ptr<TModel_SurfaceManager>& theFaces
		)
		{
			std::vector<std::shared_ptr<TModel_Surface>> Faces(theList.size());
			forThose(Index, 0, theList.size() - 1)
				Faces[Index] = theList[Index];

			auto block = std::make_shared<Cad_BlockEntity<TModel_Surface>>("Default Block Surface", Faces);
			theFaces = std::make_shared<TModel_SurfaceManager>("Default Block Surface", block);
		}


		static void LinkEdges(const std::shared_ptr<TModel_PairedManager>& theEdges)
		{
			Debug_Null_Pointer(theEdges);

			std::vector<std::shared_ptr<TModel_Paired>> edges;
			theEdges->RetrieveEntitiesTo(edges);

			for (const auto& paired : edges)
			{
				Debug_Null_Pointer(paired);

				auto edge0 = paired->Edge0();
				auto edge1 = paired->Edge1();

				if (NOT edge0)
				{
					FatalErrorIn("void LinkEdges(const entityManager_ptr& theEdges)")
						<< "Null pointer has been encountered!" << endl
						<< abort(FatalError);
				}

				if (edge1)
				{
					edge0->SetPairedEdge(edge1);
					edge1->SetPairedEdge(edge0);
				}
			}
		}
	}
}

std::shared_ptr<tnbLib::Cad3d_TModel> 
tnbLib::Cad_Tools::MakeSolid
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces,
	const Standard_Real theTolerance
)
{
	auto solid = std::make_shared<Cad3d_TModel>();

	solid->theBoundingBox_ = BoundingBox(theSurfaces);

	const auto tol = theTolerance * solid->theBoundingBox_.Diameter();
	auto EdgesOnSolid = RetrieveNonSingularEdges(theSurfaces);

	Standard_Integer K = 0;
	for (auto& x : EdgesOnSolid)
	{
		x->SetIndex(++K);
		x->SetPrecision(tol);
	}

	Entity3d_Chain chain;
	tModel::MakeStaticChain(EdgesOnSolid, chain);

	Merge3d_Chain merge;
	merge.InfoAlg().SetRadius(tol);
	merge.Import(chain);

	merge.Perform();

	const auto& merged = *merge.Merged();

	std::vector<std::shared_ptr<TModel_Vertex>> vertices;
	tModel::MakePointsOnSolid(merged, solid->ChangeCorners(), vertices);

	Debug_Null_Pointer(solid->Corners());

	K = 0;
	for (auto& x : vertices)
	{
		++K;

		Debug_Null_Pointer(x);
		x->SetIndex(K);
		x->SetName("Vertex " + std::to_string(K));
	}

	tModel::Assembly(merged, vertices, EdgesOnSolid);

	tModel::MakePairedEdges(EdgesOnSolid, solid->ChangeSegments());

	Debug_Null_Pointer(solid->Segments());

	tModel::MakeFaces(theSurfaces, solid->ChangeFaces());

	Debug_Null_Pointer(solid->Faces());

	tModel::LinkEdges(solid->Segments());

	return std::move(solid);
}

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::Cad_Tools::RetrieveNonSingularEdges
(
	const std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
)
{
	std::vector<std::shared_ptr<TModel_Edge>> gedges;
	for (const auto& x : theSurfaces)
	{
		Debug_Null_Pointer(x);
		const auto& face = *x;

		const auto edges = face.RetrieveEdges();
		for (const auto& edge : edges)
		{
			Debug_Null_Pointer(edge);
			if (NOT edge->IsDegenerated())
			{
				gedges.push_back(edge);
			}
		}
	}
	return std::move(gedges);
}

Handle(Poly_Triangulation)
tnbLib::Cad_Tools::RetrieveTriangulation
(
	const TopoDS_Face & theFace
)
{
	TopLoc_Location Loc;
	auto Triangulation = BRep_Tool::Triangulation(theFace, Loc);
	return std::move(Triangulation);
}

std::vector<Handle(Poly_Triangulation)> 
tnbLib::Cad_Tools::RetrieveTriangulation
(
	const TopoDS_Shape & theShape
)
{
	std::vector<Handle(Poly_Triangulation)> tris;
	for
		(
			TopExp_Explorer Explorer(theShape, TopAbs_FACE);
			Explorer.More();
			Explorer.Next()
			)
	{
		auto tri = RetrieveTriangulation(TopoDS::Face(Explorer.Current()));
		if (tri)
			tris.push_back(tri);
	}
	return std::move(tris);
}