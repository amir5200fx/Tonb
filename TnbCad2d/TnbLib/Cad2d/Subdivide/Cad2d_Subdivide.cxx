#include <Cad2d_Subdivide.hxx>

#include <Global_Macros.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_IntsctEntity.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_IntsctEntity_TangSegment.hxx>
#include <Cad2d_IntsctEntity_OrthSegment.hxx>
#include <Cad2d_EntityEntityIntersection.hxx>
#include <Cad2d_PlanePlaneIntersection.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/Geom2d_Curve.hxx>
#include <map>
#include <vector>
#include <list>
#include <algorithm>

#include <Geo_CurveIntegrand_Function.hxx>
#include <NumAlg_AdaptiveInteg.hxx>

namespace tnbLib
{
	
	typedef std::map<Standard_Integer, std::shared_ptr<Pln_CmpEdge>>
		cmpEdgeMap;

	typedef std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>> entityList;
	typedef std::map<Standard_Integer, std::shared_ptr<entityList>>
		entityMap;

	std::shared_ptr<Geo_ApprxCurve_Info> Cad2d_Subdivide::myApprxCurveInfo = nullptr;
	Standard_Boolean Cad2d_Subdivide::overrideMyApprxCurveInfo = Standard_False;

	namespace subdivide
	{

		/*static std::vector<std::shared_ptr<Pln_Edge>>
			SubdivideEdge
			(
				const std::shared_ptr<Pln_Edge>& theEdge, 
				const std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>>& theEntities,
				const Standard_Real theTol
			)
		{
			auto curve = theEdge->Curve();

			std::vector<Standard_Integer> sense;
			std::vector<std::shared_ptr<Pln_Curve>> curves;
			for (const auto& x : theEntities)
			{
				Debug_Null_Pointer(x);

				if (x->IsOrthogonal())
				{
					auto orth = std::dynamic_pointer_cast<Cad2d_IntsctEntity_OrthSegment>(x);
					Debug_Null_Pointer(orth);

					auto[c0, c1] = SubdivideCurve(*curve, orth->Parameter());
					
					if (IsValidCurve(c0, theTol))
					{
						curves.push_back(c0);
						sense.push_back(0);
					}

					curve = c1;
				}
				else
				{
					auto tang = std::dynamic_pointer_cast<Cad2d_IntsctEntity_TangSegment>(x);
					Debug_Null_Pointer(tang);

					auto[c0, c1, c2] = SubdivideCurve(*curve, *tang);

					if (IsValidCurve(c0, theTol))
					{
						curves.push_back(c0);
						sense.push_back(0);
					}

					if (IsValidCurve(c1, theTol))
					{
						curves.push_back(c1);
						sense.push_back(1);
					}

					curve = c2;
				}
			}

			std::vector<std::shared_ptr<Pln_Vertex>> vertices;
			vertices.reserve(curves.size() + 1);

			auto iter = curves.begin();

			Standard_Integer K = 0;
			vertices.push_back(std::make_shared<Pln_Vertex>(++K, (*iter)->FirstCoord()));

			auto p0 = (*iter)->LastCoord();

			iter++;

			while (iter NOT_EQUAL curves.end())
			{
				auto pf = (*iter)->FirstCoord();
				auto pt = MEAN(p0, pf);

				auto prec = MAX(Distance(pt, pf), Distance(pt, p0))*1.005;
				auto vtx = std::make_shared<Pln_Vertex>(++K, pt);
				Debug_Null_Pointer(vtx);

				vtx->SetPrecision(prec);

				vertices.push_back(std::move(vtx));

				p0 = (*iter)->LastCoord();

				iter++;
			}

			vertices.push_back(std::make_shared<Pln_Vertex>(++K, (*iter)->LastCoord()));

			K = 0;

			std::vector<std::shared_ptr<Pln_Edge>> edges;
			edges.reserve(curves.size());
			for (const auto& x : curves)
			{
				if (sense[K])
				{
					auto edge = std::make_shared<Pln_TangEdge>(vertices[K], vertices[K + 1], x);
					Debug_Null_Pointer(edge);

					edges.push_back(std::move(edge));
				}
				else
				{
					auto edge = std::make_shared<Pln_Edge>(vertices[K], vertices[K + 1], x);
					Debug_Null_Pointer(edge);

					edges.push_back(std::move(edge));
				}

				++K;
			}

			if (theEdge->Sense())
			{
				for (const auto& x : edges)
				{
					Debug_Null_Pointer(x);
					x->Reverse();
				}

				std::reverse(edges.begin(), edges.end());
			}

			return std::move(edges);
		}*/

		/*static std::vector<std::shared_ptr<Pln_Edge>>
			ReplaceEdge
			(
				const std::shared_ptr<Pln_Edge>& theReplaced, 
				const std::shared_ptr<Pln_CmpEdge>& theEdge, 
				const std::vector<std::shared_ptr<Pln_Edge>>& thePrior
			)
		{
			std::vector<std::shared_ptr<Pln_Edge>> edges;
			edges.reserve(thePrior.size() - 1 + theEdge->NbEdges());
			for (const auto& x : thePrior)
			{
				if (x IS_EQUAL theReplaced)
				{
					for (const auto& e : theEdge->Edges())
					{
						Debug_Null_Pointer(e);
						edges.push_back(e);
					}
				}
				else
				{
					edges.push_back(x);
				}
			}
			return std::move(edges);
		}*/

		

		/*static std::shared_ptr<Pln_Wire>
			SubdivideWire
			(
				const std::shared_ptr<Pln_Wire>& theWire,
				const entityMap& theMap,
				const Standard_Real theTol
			)
		{
			const auto& edges = theWire->Edges();
			Standard_Boolean touch = Standard_False;

			std::vector<std::shared_ptr<Pln_Edge>> newEdges;
			for (const auto& x : edges)
			{
				Debug_Null_Pointer(x);

				auto iter = theMap.find(x->Index());
				if (iter IS_EQUAL theMap.end())
				{
					newEdges.push_back(x);
				}
				else
				{
					if (NOT touch) touch = Standard_True;

					Debug_Null_Pointer(iter->second);
					auto& l = *iter->second;
					
					SortEntities(l);

					auto subEdges = SubdivideEdge(x, l, theTol);
					for (const auto& i : subEdges)
					{
						Debug_Null_Pointer(i);
						newEdges.push_back(i);
					}
				}
			}

			if (NOT touch)
			{
				return theWire;
			}

			auto cmpEdge = Pln_Tools::MakeCompoundEdge(newEdges);

			if (NOT cmpEdge->IsValidForWire(theTol))
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			auto wire = Pln_CmpEdge::MakeWire(cmpEdge, theTol);
			Debug_Null_Pointer(wire);

			return std::move(wire);
		}*/

		
	}

	void InsertToMap
	(
		const Standard_Integer theIndex,
		std::shared_ptr<Cad2d_IntsctEntity_Segment>&& theEntity,
		entityMap& theMap
	)
	{
		auto iter = theMap.find(theIndex);
		if (iter IS_EQUAL theMap.end())
		{
			auto l = std::make_shared<entityList>();
			l->push_back(std::move(theEntity));

			auto paired = std::make_pair(theIndex, std::move(l));
			auto insert = theMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				FatalErrorIn(FunctionSIG)
					<< "duplicate data!" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			auto& l = *iter->second;
			l.push_back(std::move(theEntity));
		}
	}

	auto SubdivideWire
	(
		const std::shared_ptr<Pln_Wire>& theWire,
		const entityMap& theMap,
		const Standard_Real theTol
	)
	{
		const auto& edges = theWire->Edges();

		std::vector<std::shared_ptr<Pln_Curve>> newCurves;
		std::vector<Standard_Boolean> senses;
		for (const auto& x : edges)
		{
			Debug_Null_Pointer(x);

			auto iter = theMap.find(x->Index());
			if (iter IS_EQUAL theMap.end())
			{
				newCurves.push_back(std::dynamic_pointer_cast<Pln_Curve>(x->Curve()->Copy()));
				senses.push_back(x->Sense());
			}
			else
			{
				Debug_Null_Pointer(iter->second);
				auto& l = *iter->second;

				Cad2d_IntsctEntity_Segment::SortEntities(l);

				auto subEdges = Cad2d_IntsctEntity_Segment::SubdivideEdge(x, l, theTol);

				if (NOT x->Sense())
				{
					std::reverse(subEdges.begin(), subEdges.end());
				}

				for (const auto& i : subEdges)
				{
					Debug_Null_Pointer(i);
					senses.push_back(x->Sense());
				}

				for (const auto& i : subEdges)
				{
					Debug_Null_Pointer(i);
					newCurves.push_back(i);
				}
			}
		}

		auto t = std::make_tuple(std::move(newCurves), std::move(senses));
		return std::move(t);
	}

	auto SubdividePalne
	(
		const std::shared_ptr<Cad2d_Plane>& thePlane,
		const entityMap& theMap,
		const Standard_Real theTol
	)
	{

		auto outer = thePlane->OuterWire();
		Debug_Null_Pointer(outer);

		auto[newOuterCurves, outerSense] = SubdivideWire(outer, theMap, theTol);
		auto[minTol, maxTol] = outer->BoundTolerance();

		std::shared_ptr<Pln_Wire> newOuter;
		if (Cad2d_Subdivide::overrideMyApprxCurveInfo)
		{
			newOuter = Pln_Tools::MakeWire
			(
				newOuterCurves, 
				outerSense, 
				Cad2d_Subdivide::myApprxCurveInfo, 
				MAX(2.05*maxTol, theTol)
			);
		}
		else
		{
			newOuter = Pln_Tools::MakeWire
			(
				newOuterCurves,
				outerSense, 
				MAX(2.05*maxTol, theTol)
			);
		}

		Debug_Null_Pointer(newOuter);

		newOuter->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);

		//- replace the vertices and update the precisions
#ifdef _DEBUG
		Pln_Tools::CheckManifold(newOuter);
#endif // _DEBUG

		Pln_Tools::PlaceVertices(newOuter);
		Pln_Tools::SetPrecision(newOuter);

		if (thePlane->InnerWires())
		{
			const auto& inners = thePlane->InnerWires();
			Debug_Null_Pointer(inners);

			auto newInners = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
			for (const auto& x : *inners)
			{
				Debug_Null_Pointer(x);

				auto[newWireCurves, innerSense] = SubdivideWire(x, theMap, theTol);
				auto[minTol, maxTol] = x->BoundTolerance();

				std::shared_ptr<Pln_Wire> newInner;
				if (Cad2d_Subdivide::overrideMyApprxCurveInfo)
				{
					newInner = Pln_Tools::MakeWire
					(
						newWireCurves,
						innerSense,
						Cad2d_Subdivide::myApprxCurveInfo, 
						MAX(2.05*maxTol, theTol)
					);
				}
				else
				{
					newInner = Pln_Tools::MakeWire
					(
						newWireCurves,
						innerSense,
						MAX(2.05*maxTol, theTol)
					);
				}
				Debug_Null_Pointer(newInner);

#ifdef _DEBUG
				Pln_Tools::CheckManifold(newInner);
#endif // _DEBUG

				newInner->ApplyOrientation(Pln_Orientation::Pln_Orientation_CW);

				//- replace the vertices and update the precisions
				Pln_Tools::PlaceVertices(newInner);
				Pln_Tools::SetPrecision(newInner);

				newInners->push_back(std::move(newInner));
			}

			auto plane = Cad2d_Plane::MakePlane(newOuter, newInners, thePlane->System());
			Debug_Null_Pointer(plane);

			return std::move(plane);
		}

		auto plane = Cad2d_Plane::MakePlane(newOuter, nullptr, thePlane->System());
		Debug_Null_Pointer(plane);

		return std::move(plane);
	}
}

void tnbLib::Cad2d_Subdivide::Perform()
{
	if (NOT IntersectionAlgorithm())
	{
		FatalErrorIn("void tnbLib::Cad2d_Subdivide::Perform()")
			<< "no intersection algorithm is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT IntersectionAlgorithm()->IsDone())
	{
		FatalErrorIn("void tnbLib::Cad2d_Subdivide::Perform()")
			<< "intersection algorithm is not performed!" << endl
			<< abort(FatalError);
	}

	entityMap entities0, entities1;

	const auto& entities = IntersectionAlgorithm()->Entities();
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsEdgeEdge())
		{
			FatalErrorIn("void tnbLib::Cad2d_Subdivide::Perform()")
				<< "Invalid intersection type" << endl
				<< abort(FatalError);
		}

		auto edgeEdge = std::dynamic_pointer_cast<Cad2d_EdgeEdgeIntersection>(x);
		Debug_Null_Pointer(edgeEdge);

		Debug_Null_Pointer(edgeEdge->Edge0());
		Debug_Null_Pointer(edgeEdge->Edge1());

		const auto& edge0 = *edgeEdge->Edge0();
		const auto& edge1 = *edgeEdge->Edge1();

		const auto& pairList = edgeEdge->Entities();
		for (const auto& pair : pairList)
		{
			Debug_Null_Pointer(pair);

			auto ent0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity0());
			Debug_Null_Pointer(ent0);

			auto ent1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(pair->Entity1());
			Debug_Null_Pointer(ent1);

			InsertToMap(edge0.Index(), std::move(ent0), entities0);
			InsertToMap(edge1.Index(), std::move(ent1), entities1);
		}
	}

	ChangePlane0() = 
		SubdividePalne
		(
			IntersectionAlgorithm()->Plane0(), 
			entities0, IntersectionAlgorithm()->Tolerance());

	ChangePlane1() = 
		SubdividePalne
		(IntersectionAlgorithm()->Plane1(), 
			entities1, IntersectionAlgorithm()->Tolerance());

	/*for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsEdgeEdge())
		{
			FatalErrorIn("void tnbLib::Cad2d_Subdivide::Perform()")
				<< "Invalid intersection type" << endl
				<< abort(FatalError);
		}
		
		const auto& pairList = x->Entities();
		
		auto[edge0, edge1] = Cad2d_Subdivide::RetrieveSubEdges(pairList);
		Debug_Null_Pointer(edge0);
		Debug_Null_Pointer(edge1);
	}*/

	Change_IsDone() = Standard_True;
}