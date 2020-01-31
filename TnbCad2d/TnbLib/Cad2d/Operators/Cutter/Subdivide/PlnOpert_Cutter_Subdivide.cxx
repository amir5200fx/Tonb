#include <PlnOpert_Cutter_Subdivide.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <PlnOpert_IntsctEntity.hxx>
#include <PlnOpert_IntsctPoint.hxx>
#include <PlnOpert_IntsctSegment2.hxx>
#include <PlnOpert_IntsctPair.hxx>
#include <PlnOpert_Cutter_Intersection.hxx>
#include <PlnOpert_CutterVertex.hxx>
#include <PlnOpert_CutterEdge.hxx>
#include <PlnOpert_IntsctVertex.hxx>
#include <PlnOpert_IntsctEdge.hxx>
#include <PlnOpert_IntsctPoint2.hxx>
#include <PlnOpert_CutterEntity.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		CollectCutter
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctPair>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		entities.reserve(theEntities.size());
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);

			const auto& ent = x->Entity0();
			entities.push_back(ent);
			/*if (ent->IsPoint())
			{
				entities.push_back(x->Entity0());
			}
			else if (ent->IsSegment())
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(ent);
				Debug_Null_Pointer(seg);

				entities.push_back(seg->Start());
				entities.push_back(seg->End());
			}
			else
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> CollectCutter(Args)")
					<< "Invalid entity" << endl
					<< abort(FatalError);
			}*/
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		CollectEdges
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctPair>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		entities.reserve(theEntities.size());
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);

			const auto& ent = x->Entity1();
			entities.push_back(ent);
			/*if (ent->IsPoint())
			{
				entities.push_back(x->Entity1());
			}
			else if (ent->IsSegment())
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(ent);
				Debug_Null_Pointer(seg);

				entities.push_back(seg->Start());
				entities.push_back(seg->End());
			}
			else
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> CollectCutter(Args)")
					<< "Invalid entity" << endl
					<< abort(FatalError);
			}*/
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		IntsctOnVertices
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->Paires().size() > 1)
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		IntsctOnSegments
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->IsSegment())
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		IntsctOnPoints
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->IsPoint() AND x->Paires().size() IS_EQUAL 1)
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
	}

	Standard_Boolean IsInside
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& thePt,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theSegment,
		const Standard_Real theTol
	)
	{
		if (NOT std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(thePt))
		{
			FatalErrorIn("Standard_Boolean IsInside(Args...)")
				<< "the entity is no the point type" << endl
				<< abort(FatalError);
		}

		auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(theSegment);
		if (NOT seg)
		{
			FatalErrorIn("Standard_Boolean IsInside(Args...)")
				<< "the entity is no the segment type" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(seg->Start());
		Debug_Null_Pointer(seg->End());

		const auto x0 = seg->Start()->CharParameter();
		const auto x1 = seg->End()->CharParameter();

		return INSIDE(thePt->CharParameter(), x0 - theTol, x1 + theTol);
	}

	void MergeVerticesWithSegments
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& theVt,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theSegment,
		const Standard_Real theTol
	)
	{
		if (NOT std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(theVt))
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the point type" << endl
				<< abort(FatalError);
		}

		auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(theSegment);
		if (NOT seg)
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the segment type" << endl
				<< abort(FatalError);
		}

		if (ABS(seg->Start()->CharParameter() - theVt->CharParameter()) <= theTol)
		{
			const auto& v = seg->Start();
			
			v->Paires().clear();
			for (const auto& x : theVt->Paires())
			{
				v->PushToPairs(x);

				auto pair = x.lock();
				Debug_Null_Pointer(pair);

				pair->Paires().clear();
				pair->PushToPairs(v);
			}
		}
		else if (ABS(seg->End()->CharParameter() - theVt->CharParameter()) <= theTol)
		{
			const auto& v = seg->End();

			v->Paires().clear();
			for (const auto& x : theVt->Paires())
			{
				v->PushToPairs(x);

				auto pair = x.lock();
				Debug_Null_Pointer(pair);

				pair->Paires().clear();
				pair->PushToPairs(v);
			}
		}
		else
		{
			FatalErrorIn("void MergeVerticesWithSegments(Args...)")
				<< "invalid intersection type" << endl
				<< abort(FatalError);
		}
	}

	void MergeVerticesWithPoints
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& theVt,
		const std::shared_ptr<PlnOpert_IntsctEntity>& thePt,
		const Standard_Real theTol
	)
	{
		if (NOT std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(theVt))
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the point type" << endl
				<< abort(FatalError);
		}

		auto pt = std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(thePt);
		if (NOT pt)
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the segment type" << endl
				<< abort(FatalError);
		}

		if (ABS(pt->CharParameter() - theVt->CharParameter()) <= theTol)
		{
			pt->Paires().clear();
			for (const auto& x : theVt->Paires())
			{
				pt->PushToPairs(x);

				auto pair = x.lock();
				Debug_Null_Pointer(pair);

				pair->PushToPairs(pt);
			}
		}
		else
		{
			FatalErrorIn("void MergeVerticesWithPoints(Args...)")
				<< "invalid intersection type" << endl
				<< abort(FatalError);
		}
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		RemoveCollideVerticesWithSegments
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theVertices,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theSegments,
			const Standard_Real theTol
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& v : theVertices)
		{
			Debug_Null_Pointer(v);

			Standard_Boolean flag = Standard_False;
			for (const auto& seg : theSegments)
			{
				Debug_Null_Pointer(seg);
				if (IsInside(v, seg, theTol))
				{
					MergeVerticesWithSegments(v, seg, theTol);

					flag = Standard_True;
					break;
				}
			}

			if (NOT flag)
			{
				entities.push_back(v);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		RemoveCollideVerticesWithPoints
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theVertices,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& thePoints,
			const Standard_Real theTol
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& v : theVertices)
		{
			Debug_Null_Pointer(v);

			Standard_Boolean flag = Standard_False;
			for (const auto& pt : thePoints)
			{
				Debug_Null_Pointer(pt);
				if (ABS(v->CharParameter() - pt->CharParameter()) <= theTol)
				{
					MergeVerticesWithPoints(v, pt, theTol);

					flag = Standard_True;
					break;
				}
			}

			if (NOT flag)
			{
				entities.push_back(v);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		MergedEntities
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theVertices,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theSegments, 
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& thePoints
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theVertices)
		{
			Debug_Null_Pointer(x);
			entities.push_back(x);
		}

		for (const auto& x : theSegments)
		{
			Debug_Null_Pointer(x);
			entities.push_back(x);
		}

		for (const auto& x : thePoints)
		{
			Debug_Null_Pointer(x);
			entities.push_back(x);
		}
		return std::move(entities);
	}

	typedef std::map
		<
		Standard_Integer,
		std::shared_ptr<std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>>
		>
		intersectMap;

	void PushToMap
	(
		const Standard_Integer theIndex,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theEntity,
		intersectMap& theMap
	)
	{
		auto iter = theMap.find(theIndex);
		if (iter IS_EQUAL theMap.end())
		{
			auto insert = theMap.insert
			(
				std::make_pair
				(
					theIndex,
					std::make_shared<std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>>()
				));

			if (NOT insert.second)
			{
				FatalErrorIn("void PushToMap(Args...)")
					<< "Unable to insert the item to the map: duplicate data, index: " << endl
					<< abort(FatalError);
			}
		}
		else
		{
			iter->second->push_back(theEntity);
		}
	}

	intersectMap
		GetIndexMap
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		intersectMap edgeMap;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);

			const auto& pairList = x->Paires();
			if (pairList.empty() OR pairList.size() > 2)
			{
				FatalErrorIn("indexToEntityMap GetIndexMap(const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities)")
					<< "invalid data: Unrecognized pair of two entities!" << endl
					<< abort(FatalError);
			}

			for (const auto& ent : pairList)
			{
				auto pair = ent.lock();
				Debug_Null_Pointer(pair);

				const auto& edge = pair->ParentEdge();

				PushToMap(edge->Index(), pair, edgeMap);
			}
		}

		for (const auto& x : edgeMap)
		{
			const auto& l = x.second;
		}
		return std::move(edgeMap);
	}

	struct ClipParam
	{

		std::shared_ptr<PlnOpert_IntsctEntity> entity;

		Standard_Real param;

		ClipParam(const Standard_Real p, const std::shared_ptr<PlnOpert_IntsctEntity>& e)
			: param(p), entity(e)
		{}
	};

	std::vector<std::shared_ptr<ClipParam>>
		GetClips
		(
			const Pln_Curve& theCurve,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<ClipParam>> clips;
		clips.push_back(std::make_shared<ClipParam>(theCurve.FirstParameter(), nullptr));

		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);

			if (x->IsPoint())
			{
				clips.push_back(std::make_shared<ClipParam>(x->CharParameter(), x));
			}
			else if (x->IsSegment())
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(x);
				Debug_Null_Pointer(seg);

				const auto& x0 = seg->Start();
				const auto& x1 = seg->End();

				clips.push_back(std::make_shared<ClipParam>(x0->CharParameter(), x0));
				clips.push_back(std::make_shared<ClipParam>(x1->CharParameter(), x1));
			}
			else
			{
				FatalErrorIn("td::vector<std::shared_ptr<ClipParam>> GetClips()")
					<< "unable to identify the entity" << endl
					<< abort(FatalError);
			}
		}
		clips.push_back(std::make_shared<ClipParam>(theCurve.LastParameter(), nullptr));

		return std::move(clips);
	}

	std::vector<std::shared_ptr<Pln_Edge>>
		ClipCurve
		(
			const Pln_Curve& theCurve,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		auto clips = GetClips(theCurve, theEntities);

		std::vector<std::shared_ptr<Pln_Curve>> curves;
		curves.reserve(clips.size() - 1);
		forThose(Index, 0, clips.size() - 2)
		{
			const auto& x0 = clips[Index];
			Debug_Null_Pointer(x0);

			const auto& x1 = clips[Index + 1];
			Debug_Null_Pointer(x1);

			auto clip = Pln_Curve::Clip(theCurve, x0->param, x1->param);
			Debug_Null_Pointer(clip);

			curves.push_back(std::move(clip));
		}

		std::vector<std::shared_ptr<Pln_Edge>> edges;
		edges.reserve(curves.size());
		forThose(Index, 0, curves.size() - 1)
		{
			const auto& x0 = clips[Index];
			Debug_Null_Pointer(x0);

			const auto& x1 = clips[Index + 1];
			Debug_Null_Pointer(x1);

			std::shared_ptr<Pln_Vertex> v0, v1;
			if (x0->entity)
			{
				auto iv = std::make_shared<PlnOpert_IntsctVertex>(theCurve.Value(x0->param));
				iv->SetIntsctEntity(std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(x0->entity));
				Debug_Null_Pointer(iv);

				x0->entity->PushToVertices(iv);

				v0 = iv;
			}
			else
			{
				v0 = std::make_shared<Pln_Vertex>(theCurve.Value(x0->param));
			}

			if (x1->entity)
			{
				auto iv = std::make_shared<PlnOpert_IntsctVertex>(theCurve.Value(x1->param));
				iv->SetIntsctEntity(std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(x1->entity));
				Debug_Null_Pointer(iv);

				x1->entity->PushToVertices(iv);

				v1 = iv;
			}
			else
			{
				v1 = std::make_shared<Pln_Vertex>(theCurve.Value(x1->param));
			}

			std::shared_ptr<Pln_Edge> edge;
			if (v0->IsIntersect() AND v1->IsIntersect())
			{
				auto iv0 = std::dynamic_pointer_cast<PlnOpert_IntsctVertex>(v0);
				Debug_Null_Pointer(iv0);

				auto iv1 = std::dynamic_pointer_cast<PlnOpert_IntsctVertex>(v1);
				Debug_Null_Pointer(iv1);

				const auto& ent0 = iv0->IntsctEntity();
				Debug_Null_Pointer(ent0);

				const auto& ent1 = iv1->IntsctEntity();
				Debug_Null_Pointer(ent1);

				if (ent0->IsType2() AND ent1->IsType2())
				{
					auto ie = std::make_shared<PlnOpert_IntsctEdge>(v0, v1);
					Debug_Null_Pointer(ie);

					auto ent0_2 = std::dynamic_pointer_cast<PlnOpert_IntsctPoint2>(ent0);
					Debug_Null_Pointer(ent0_2);

					Debug_Null_Pointer(ent0_2->Segment().lock());
					ie->SetIntsctEntity(ent0_2->Segment().lock());
#ifdef FULLDEBUG
					auto ent1_2 = std::dynamic_pointer_cast<PlnOpert_IntsctPoint2>(ent1);
					Debug_Null_Pointer(ent1_2);

					Debug_Null_Pointer(ent1_2->Segment().lock());

					if (ent0_2->Segment().lock() NOT_EQUAL ent1_2->Segment().lock())
					{
						FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> ClipCurve()")
							<< "Invalid data: the segment is not same between the two vertices" << endl
							<< abort(FatalError);
					}
#endif // FULLDEBUG
					edge = ie;
				}
				else
				{
					edge = std::make_shared<Pln_Edge>(v0, v1);
				}
			}
			else
			{
				edge = std::make_shared<Pln_Edge>(v0, v1);
			}

			if (v0->IsIntersect())
			{
				auto iv = std::dynamic_pointer_cast<PlnOpert_IntsctVertex>(v0);
				Debug_Null_Pointer(iv);

				iv->IntsctEntity()->SetParentEdge(edge);
			}

			if (v1->IsIntersect())
			{
				auto iv = std::dynamic_pointer_cast<PlnOpert_IntsctVertex>(v1);
				Debug_Null_Pointer(iv);

				iv->IntsctEntity()->SetParentEdge(edge);
			}

			edges.push_back(std::move(edge));
		}
		return std::move(edges);
	}

	std::vector<std::shared_ptr<PlnOpert_CutterEntity>>
		GetCutterEntities
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_CutterEntity>> entities;
		entities.reserve(theEntities.size());

		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (NOT x->IsPoint())
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_CutterEntity>> GetCutterEntities(Arg...)")
					<< "the entity is not point type" << endl
					<< abort(FatalError);
			}

			auto ent = std::make_shared<PlnOpert_CutterEntity>();
			Debug_Null_Pointer(ent);

			const auto& vertices = x->Vertices();
			for (const auto& v : vertices)
			{
				Debug_Null_Pointer(v);

				std::vector<std::weak_ptr<Pln_Edge>> wEdges;
				v->RetrieveEdgesTo(wEdges);

				if (wEdges.size() NOT_EQUAL 1)
				{
					FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_CutterEntity>> GetCutterEntities(Arg...)")
						<< "contradictory data" << endl
						<< abort(FatalError);
				}

				auto edge = wEdges[0].lock();
				Debug_Null_Pointer(edge);

				auto id = edge->GetIndex(v);
				if (id IS_EQUAL 0)
				{
					ent->SetForwardCutter(v);
				}
				else
				{
					ent->SetBackwardCutter(v);
				}
			}

			const auto& pairs = x->Paires();
			if (pairs.empty())
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_CutterEntity>> GetCutterEntities(Arg...)")
					<< "contradictory data: there is no pair for the intersection entity!" << endl
					<< abort(FatalError);
			}

			if (pairs.size() > 2)
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_CutterEntity>> GetCutterEntities(Arg...)")
					<< "contradictory data: there are more than two pairs for the intersection entity" << endl
					<< abort(FatalError);
			}

			for (const auto& pair : pairs)
			{
				Debug_Null_Pointer(pair.lock());

				auto pEnt = pair.lock();
				Debug_Null_Pointer(pEnt);

				const auto& pVertices = pEnt->Vertices();
				for (const auto& v : pVertices)
				{
					Debug_Null_Pointer(v);

					std::vector<std::weak_ptr<Pln_Edge>> wEdges;
					v->RetrieveEdgesTo(wEdges);

					if (wEdges.size() NOT_EQUAL 1)
					{
						FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_CutterEntity>> GetCutterEntities(Arg...)")
							<< "contradictory data" << endl
							<< abort(FatalError);
					}

					auto edge = wEdges[0].lock();
					Debug_Null_Pointer(edge);

					auto id = edge->GetIndex(v);
					if (id IS_EQUAL 0)
					{
						ent->SetForwardVtx(v);
					}
					else
					{
						ent->SetBackwardVtx(v);
					}
				}
			}
		}
		return std::move(entities);
	}


}

void tnbLib::PlnOpert_Cutter_Subdivide::Perform(const Standard_Real theTol)
{
	const auto& intersection = Intersection();
	Debug_Null_Pointer(intersection);

	auto cutterEntities = CollectCutter(intersection->Entities());
	auto edgeEntities = CollectEdges(intersection->Entities());

	//sort(cutterEntities.begin(), cutterEntities.end(), &PlnOpert_IntsctEntity::IsLess);

	auto intsctVertices = IntsctOnVertices(cutterEntities);
	auto intsctSegments = IntsctOnSegments(cutterEntities);
	auto intsctPoints = IntsctOnPoints(cutterEntities);

	auto removedCollideVerticesWithSegments = 
		RemoveCollideVerticesWithSegments(intsctVertices, intsctSegments, theTol);

	auto mergedVertices = 
		RemoveCollideVerticesWithPoints(removedCollideVerticesWithSegments, intsctPoints, theTol);

	auto mergedCutterEntities = MergedEntities(mergedVertices, intsctSegments, intsctPoints);

	sort(mergedCutterEntities.begin(), mergedCutterEntities.end(), &PlnOpert_IntsctEntity::IsLess);

	auto edgeMap = GetIndexMap(mergedCutterEntities);


}