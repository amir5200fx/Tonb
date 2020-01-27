#include <PlnOpert_Subdivide.hxx>

#include <Geo_BinSearch.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <PlnOpert_IntsctVertex.hxx>
#include <PlnOpert_IntsctEdge.hxx>
#include <PlnOpert_IntsctEntity.hxx>
#include <PlnOpert_IntsctPoint.hxx>
#include <PlnOpert_IntsctPoint2.hxx>
#include <PlnOpert_IntsctSegment.hxx>
#include <PlnOpert_IntsctSegment2.hxx>
#include <PlnOpert_IntsctPair.hxx>

namespace tnbLib
{

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
			theMap.insert
			(
				std::make_pair
				(
					theIndex,
					std::make_shared<std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>>()
				));
		}
		else
		{
			iter->second->push_back(theEntity);
		}
	}

	bool CompareEntities
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& theEnt0,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theEnt1
	)
	{
		Debug_Null_Pointer(theEnt0);
		Debug_Null_Pointer(theEnt1);

		return theEnt0->CharParameter() < theEnt1->CharParameter();
	}

	std::shared_ptr<PlnOpert_IntsctEntity> 
		ConvertToPoints
		(
			const std::shared_ptr<PlnOpert_IntsctEntity>& theEntity
		)
	{
		if (theEntity->IsPoint())
		{
			FatalErrorIn("std::shared_ptr<PlnOpert_IntsctEntity> ConvertToPoints(const std::shared_ptr<PlnOpert_IntsctEntity>& theEntity)")
				<< "the entity already is a point type" << endl
				<< abort(FatalError);
		}

		auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment>(theEntity);
		Debug_Null_Pointer(seg);

		auto nSeg = std::make_shared<PlnOpert_IntsctSegment2>
			(
				seg->Index(), seg->Coord0(), 
				seg->Coord1(), seg->Parameter0(), seg->Parameter1());
		Debug_Null_Pointer(nSeg);

		auto n0 = std::make_shared<PlnOpert_IntsctPoint2>(0, seg->Coord0(), seg->Parameter0());
		Debug_Null_Pointer(n0);

		auto n1 = std::make_shared<PlnOpert_IntsctPoint2>(0, seg->Coord1(), seg->Parameter1());
		Debug_Null_Pointer(n1);

		nSeg->SetStart(n0);
		nSeg->SetEnd(n1);

		n0->SetSegment(nSeg);
		n1->SetSegment(nSeg);

		return std::move(nSeg);
	}

	std::shared_ptr<PlnOpert_IntsctPair> 
		ConvertToPoints
		(
			const std::shared_ptr<PlnOpert_IntsctPair>& theEntity
		)
	{
		if (theEntity->IsPoint())
		{
			FatalErrorIn("std::shared_ptr<PlnOpert_IntsctPair> ConvertToPoints(const std::shared_ptr<PlnOpert_IntsctPair>& theEntity)")
				<< "the entity already is a point type" << endl
				<< abort(FatalError);
		}

		auto e0 = ConvertToPoints(theEntity->Entity0());
		auto e1 = ConvertToPoints(theEntity->Entity1());
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);

		auto pairSeg = std::make_shared<PlnOpert_IntsctPair>(theEntity->Index(), e0, e1);

		auto e0_2 = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(e0);
		Debug_Null_Pointer(e0_2);

		auto e1_2 = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(e1);
		Debug_Null_Pointer(e1_2);

		const auto& p0 = e0_2->Start();
		const auto& p1 = e0_2->End();

		const auto& v0 = e1_2->Start();
		const auto& v1 = e1_2->End();

		if (theEntity->SameDirection())
		{
			p0->SetPair(v0);
			v0->SetPair(p0);

			p1->SetPair(v1);
			v1->SetPair(p1);
		}
		else
		{
			p0->SetPair(v1);
			v1->SetPair(p0);

			p1->SetPair(v0);
			v0->SetPair(p1);
		}

		return std::move(pairSeg);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctPair>> 
		ConvertToPoints
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctPair>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctPair>> entities;
		entities.reserve(theEntities.size());

		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->IsSegment())
			{
				entities.push_back(ConvertToPoints(x));
			}
			else
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
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

		for(const auto& x: theEntities)
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

			edges.push_back(std::move(edge));
		}
		return std::move(edges);
	}

	typedef std::array<std::shared_ptr<Pln_Vertex>, 2> vertexArray_2;
	typedef std::pair<std::shared_ptr<PlnOpert_IntsctPoint>, vertexArray_2> intsctToSubVerticesPair;

	std::vector<std::shared_ptr<Pln_Edge>>
		Subdivide
		(
			const std::shared_ptr<Pln_Curve>& theCurve,
			std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities,
			std::map<Standard_Integer, intsctToSubVerticesPair>& theEntityMap
		)
	{
		theEntities.sort(CompareEntities);
		theEntities.sort();

		std::vector<Standard_Real> params;
		std::vector<std::shared_ptr<PlnOpert_IntsctPoint>> ptEntities;
		std::vector<Standard_Integer> flag; 
		for (const auto& x : theEntities)
		{
			if (x->IsPoint())
			{
				params.push_back(x->CharParameter());

				ptEntities.push_back(std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(x));
				flag.push_back(0);
			}
			else
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment>(x);
				Debug_Null_Pointer(seg);

				params.push_back(seg->Parameter0());
				params.push_back(seg->Parameter1());

				auto twoPts = PlnOpert_IntsctSegment::ConvertToPoints(*seg);

				twoPts[0]->SetPair(x);
				twoPts[1]->SetPair(x);

				ptEntities.push_back(twoPts[0]);
				flag.push_back(1);

				ptEntities.push_back(twoPts[1]);
				flag.push_back(1);
			}
		}

		Standard_Integer k = 0;
		for (const auto& x : ptEntities)
		{
			Debug_Null_Pointer(x);
			x->SetIndex(++k);
		}

		//- splitting the curve
		auto curves = theCurve->Split(params);

		std::vector<std::shared_ptr<Pln_Vertex>> vertices;
		vertices.reserve(curves.size() * 2);
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);
			vertices.push_back(std::make_shared<PlnOpert_IntsctVertex>(0, x->FirstCoord()));
			vertices.push_back(std::make_shared<PlnOpert_IntsctVertex>(0, x->LastCoord()));
		}

		//- the first and the last point are not the intersection ones
		vertices[0] = std::make_shared<Pln_Vertex>(0, vertices[0]->Coord());
		vertices[vertices.size() - 1] = 
			std::make_shared<Pln_Vertex>(0, vertices[vertices.size() - 1]->Coord());

		//- assigning the entities to the corresponding vertex
		k = 0;
		for (const auto& x : ptEntities)
		{
			auto e0 = std::dynamic_pointer_cast<PlnOpert_IntsctVertex>(vertices[2 * k + 1]);
			Debug_Null_Pointer(e0);

			e0->SetIntsctEntity(x);

			auto e1 = std::dynamic_pointer_cast<PlnOpert_IntsctVertex>(vertices[2 * k + 2]);
			Debug_Null_Pointer(e1);

			e1->SetIntsctEntity(x);

			k++;

			vertexArray_2 pairedVertices;
			pairedVertices[0] = e0;
			pairedVertices[1] = e1;

			auto pairedVerticesWithEntity = std::make_pair(x, std::move(pairedVertices));
			auto insert = theEntityMap.insert(std::make_pair(x->Index(), std::move(pairedVerticesWithEntity)));

			if (NOT insert.second)
			{
				FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> Subdivide()")
					<< "Unable to insert the item to the map" << endl
					<< abort(FatalError);
			}
		}

		std::vector<std::shared_ptr<Pln_Edge>> edges;
		edges.reserve(curves.size());

		k = 0;
		for (const auto& x : curves)
		{
			Debug_Null_Pointer(x);
			if (flag[k] AND flag[k + 1])
			{
				auto edge = 
					std::make_shared<PlnOpert_IntsctEdge>(vertices[2 * k], vertices[2 * k + 1], x);

				++k;
				edges.push_back(edge);
			}
			else
			{
				auto edge = 
					std::make_shared<Pln_Edge>(vertices[2 * k], vertices[2 * k + 1], x);

				++k;
				edges.push_back(edge);
			}

			
		}
		return std::move(edges);
	}


}

#include <PlnOpert_IntsctCurveCurve.hxx>
#include <PlnOpert_IntsctCurveCurve_Info.hxx>

void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)
{
	if (NOT OuterWire())
	{
		FatalErrorIn("void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)")
			<< "Invalid data: no outer wire is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Cutter())
	{
		FatalErrorIn("void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)")
			<< "no cutter is loaded!" << endl
			<< abort(FatalError);
	}

	auto info = std::make_shared<PlnOpert_IntsctCurveCurve_Info>();
	info->SetTolerance(theTol);

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	for (const auto& x : OuterWire()->Edges())
	{
		Debug_Null_Pointer(x);
		edges.push_back(x);
	}

	if (InnerWires())
	{
		for (const auto& wire : *InnerWires())
		{
			Debug_Null_Pointer(wire);
			for (const auto& x : wire->Edges())
			{
				Debug_Null_Pointer(x);
				edges.push_back(x);
			}
		}
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctPair>> intPaires;

	std::map<Standard_Integer, Standard_Integer> CurveToEdgeIndexMap;
	std::map<Standard_Integer, Standard_Integer> CutterToEdgeIndexMap;

	const auto& cmpEdges = Cutter()->Edges();
	for (const auto& x : cmpEdges)
	{
		auto alg = std::make_shared<PlnOpert_IntsctCurveCurve>(info);
		Debug_Null_Pointer(alg);

		if (NOT x->Curve())
		{
			FatalErrorIn("void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)")
				<< "the edge has no curve!" << endl
				<< abort(FatalError);
		}

		auto cutterIter = CutterToEdgeIndexMap.insert(std::make_pair(x->Curve()->Index(), x->Index()));
		if (NOT cutterIter.second)
		{
			FatalErrorIn("void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)")
				<< "Unable to insert the item into the map" << endl
				<< abort(FatalError);
		}

		alg->LoadCurve0(x->Curve());
		for (const auto& edge : edges)
		{
			Debug_Null_Pointer(edge);

			if (NOT edge->Curve())
			{
				FatalErrorIn("void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)")
					<< "the edge has no curve!" << endl
					<< abort(FatalError);
			}

			auto edgeIter = CurveToEdgeIndexMap.insert(std::make_pair(edge->Curve()->Index(), edge->Index()));
			if (NOT edgeIter.second)
			{
				FatalErrorIn("void tnbLib::PlnOpert_Subdivide::Perform(const Standard_Real theTol)")
					<< "Unable to insert the item into the map" << endl
					<< abort(FatalError);
			}

			alg->LoadCurve1(edge->Curve());

			alg->Perform();
			Debug_If_Condition_Message(NOT alg->IsDone(), "the intersection algorithm is not performed!");

			if (alg->HasIntersection())
			{
				const auto& entities = alg->Entities();
				for (const auto& ent : entities)
				{
					Debug_Null_Pointer(ent);
					intPaires.push_back(ent);
				}
			}
		}
	}

	auto modifiedPaires = ConvertToPoints(intPaires);

	std::map<Standard_Integer, std::shared_ptr<std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>>>
		EdgeToEntityMap;
	std::map<Standard_Integer, std::shared_ptr<std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>>>
		CutterToEntityMap;

	for (const auto& x : modifiedPaires)
	{
		Debug_Null_Pointer(x);

		const auto& ent0 = x->Entity0();
		const auto& ent1 = x->Entity1();

		Debug_Null_Pointer(ent0);
		Debug_Null_Pointer(ent1);

		const auto& c0 = ent0->Curve();
		const auto& c1 = ent1->Curve();

		Debug_Null_Pointer(c0);
		Debug_Null_Pointer(c1);

		PushToMap(CutterToEdgeIndexMap[c0->Index()], ent0, CutterToEntityMap);
		PushToMap(CutterToEdgeIndexMap[c1->Index()], ent1, EdgeToEntityMap);
	}


}