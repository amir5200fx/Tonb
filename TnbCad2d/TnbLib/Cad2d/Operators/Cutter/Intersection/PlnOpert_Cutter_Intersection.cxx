#include <PlnOpert_Cutter_Intersection.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Tools.hxx>
#include <PlnOpert_IntsctVertex.hxx>
#include <PlnOpert_IntsctEdge.hxx>
#include <PlnOpert_IntsctEntity.hxx>
#include <PlnOpert_IntsctPoint.hxx>
#include <PlnOpert_IntsctPoint2.hxx>
#include <PlnOpert_IntsctSegment.hxx>
#include <PlnOpert_IntsctSegment2.hxx>
#include <PlnOpert_IntsctPair.hxx>
#include <PlnOpert_IntsctCurveCurve.hxx>
#include <PlnOpert_IntsctCurveCurve_Info.hxx>

namespace tnbLib
{

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

		nSeg->SetParentCurve(theEntity->ParentCurve());

		auto n0 = std::make_shared<PlnOpert_IntsctPoint2>(0, seg->Coord0(), seg->Parameter0());
		Debug_Null_Pointer(n0);

		n0->SetParentCurve(theEntity->ParentCurve());

		auto n1 = std::make_shared<PlnOpert_IntsctPoint2>(0, seg->Coord1(), seg->Parameter1());
		Debug_Null_Pointer(n1);

		n1->SetParentCurve(theEntity->ParentCurve());

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
			p0->PushToPairs(v0);
			v0->PushToPairs(p0);

			p1->PushToPairs(v1);
			v1->PushToPairs(p1);
		}
		else
		{
			p0->PushToPairs(v1);
			v1->PushToPairs(p0);

			p1->PushToPairs(v0);
			v0->PushToPairs(p1);
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

	std::vector<std::pair<std::shared_ptr<Pln_Vertex>, std::pair<std::shared_ptr<Pln_Curve>, Standard_Real>>>
		IntersectVertices
		(
			const std::shared_ptr<Pln_Curve>& theCurve,
			const std::vector<std::shared_ptr<Pln_Wire>>& theWires,
			const Standard_Real thePrecision
		)
	{
		std::vector
			<
			std::pair<std::shared_ptr<Pln_Vertex>, 
			std::pair<std::shared_ptr<Pln_Curve>, Standard_Real>>
			>
			paires;
		for (const auto& x : theWires)
		{
			Debug_Null_Pointer(x);

			auto vertices = x->RetrieveVertices();
			for (const auto& v : vertices)
			{
				Debug_Null_Pointer(v);

				const auto prec = MAX(thePrecision, v->Precision());

				Standard_Real param;
				auto dis = Pln_Tools::Distance(v->Coord(), theCurve->Geometry(), param);

				if (dis <= prec)
				{
					auto curve_param = std::make_pair(theCurve, param);
					paires.push_back(std::make_pair(v, std::move(curve_param)));
				}
			}
		}
		return std::move(paires);
	}

	std::vector<std::pair<std::shared_ptr<Pln_Vertex>, std::pair<std::shared_ptr<Pln_Curve>, Standard_Real>>>
		IntersectVertices
		(
			const Pln_CmpEdge& theEdge,
			const std::vector<std::shared_ptr<Pln_Wire>>& theWires,
			const Standard_Real thePrecision
		)
	{
		std::vector
			<
			std::pair<std::shared_ptr<Pln_Vertex>,
			std::pair<std::shared_ptr<Pln_Curve>, Standard_Real>>
			> entities;
		for (const auto& x : theEdge.Edges())
		{
			Debug_Null_Pointer(x);
			Debug_Null_Pointer(x->Curve());

			auto local = IntersectVertices(x->Curve(), theWires, thePrecision);

			for (const auto& l : local)
			{
				entities.push_back(std::move(l));
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<Pln_Edge>>
		GetEdges
		(
			const std::vector<std::shared_ptr<Pln_Wire>>& theWires
		)
	{
		std::vector<std::shared_ptr<Pln_Edge>> edges;
		for (const auto& wire : theWires)
		{
			Debug_Null_Pointer(wire);
			for (const auto& x : wire->Edges())
			{
				Debug_Null_Pointer(x);
				edges.push_back(x);
			}
		}
		return std::move(edges);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctPair>>
		GetEntities
		(
			const std::shared_ptr<Pln_CmpEdge>& theCutter,
			const std::vector<std::shared_ptr<Pln_Wire>>& theWires,
			const Standard_Real theTol
		)
	{
		auto info = std::make_shared<PlnOpert_IntsctCurveCurve_Info>();
		Debug_Null_Pointer(info);

		info->SetTolerance(theTol);

		auto alg = std::make_shared<PlnOpert_IntsctCurveCurve>(info);

		auto edges = GetEdges(theWires);

		std::vector<std::shared_ptr<PlnOpert_IntsctPair>> entities;
		for (const auto& cutter : theCutter->Edges())
		{
			Debug_Null_Pointer(cutter);
			Debug_Null_Pointer(cutter->Curve());

			alg->LoadCurve0(cutter->Curve());

			for (const auto& x : edges)
			{
				Debug_Null_Pointer(x);
				Debug_Null_Pointer(x->Curve());

				alg->LoadCurve1(x->Curve());

				alg->Perform();
				Debug_If_Condition_Message(NOT alg->IsDone(), "the intersection algorithm is not performed!");

				if (alg->HasIntersection())
				{
					for (const auto& ent : alg->Entities())
					{
						Debug_Null_Pointer(ent);
						entities.push_back(ent);
					}
				}
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctPair>> 
		GetEntities
		(
			const std::vector
			<
			std::pair<std::shared_ptr<Pln_Vertex>,
			std::pair<std::shared_ptr<Pln_Curve>, Standard_Real>>
			>& theVertices
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctPair>> paires;
		for (const auto& x : theVertices)
		{
			const auto& vtx = x.first;
			const auto& curve_param = x.second;

			const auto& curve = curve_param.first;
			const auto param = curve_param.second;

			auto ent0 = std::make_shared<PlnOpert_IntsctPoint>(0, curve->Value(param), param);
			Debug_Null_Pointer(ent0);

			ent0->SetParentCurve(curve);

			std::vector<std::weak_ptr<Pln_Edge>> edges;
			vtx->RetrieveEdgesTo(edges);

			if (edges.size() NOT_EQUAL 2)
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_IntsctPair>> GetEntities(...)")
					<< "Invalid Geometry: the model is not manifold" << endl
					<< abort(FatalError);
			}

			for (const auto& e : edges)
			{
				auto edge = e.lock();
				Debug_Null_Pointer(edge);

				auto id = edge->GetIndex(vtx);
				auto edge_param = edge->Parameter(id);

				const auto& c = edge->Curve();
				if (NOT c)
				{
					FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_IntsctPair>> GetEntities(...)")
						<< "Invalid Geometry: the edge has no geometric curve!" << endl
						<< abort(FatalError);
				}

				auto ent1 = std::make_shared<PlnOpert_IntsctPoint>(0, c->Value(edge_param), edge_param);
				Debug_Null_Pointer(ent1);

				ent1->SetParentCurve(c);

				ent1->PushToPairs(ent0);
				ent0->PushToPairs(ent1);

				auto paired = std::make_shared<PlnOpert_IntsctPair>(0, ent0, ent1);
				Debug_Null_Pointer(paired);

				paires.push_back(std::move(paired));
			}
		}
		return std::move(paires);
	}

	std::vector<std::shared_ptr<Pln_Wire>> 
		GetWires
		(
			const std::shared_ptr<Pln_Wire>& theOuter, 
			const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>>& theInners
		)
	{
		std::vector<std::shared_ptr<Pln_Wire>> wires;
		if (theInners)
		{
			wires.reserve(1 + theInners->size());
		}
		else
		{
			wires.reserve(1);
		}

		wires.push_back(theOuter);
		if (theInners)
		{
			for (const auto& x : *theInners)
			{
				wires.push_back(x);
			}
		}
		return std::move(wires);
	}
}

void tnbLib::PlnOpert_Cutter_Intersection::Perform
(
	const Standard_Real theTol
)
{
	if (NOT OuterWire())
	{
		FatalErrorIn("void tnbLib::PlnOpert_Cutter_Intersection::Perform(const Standard_Real theTol)")
			<< "Invalid data: no outer wire is loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Cutter())
	{
		FatalErrorIn("void tnbLib::PlnOpert_Cutter_Intersection::Perform(const Standard_Real theTol)")
			<< "no cutter is loaded!" << endl
			<< abort(FatalError);
	}

	auto wires = GetWires(OuterWire(), InnerWires());
	Debug_If_Condition(wires.empty());

	auto vertices = IntersectVertices(*Cutter(), wires, theTol);
	auto vEntities = GetEntities(vertices);

	auto& entities = ChangeEntities();
	for (const auto& x : vEntities)
	{
		Debug_Null_Pointer(x);
		entities.push_back(std::move(x));
	}

	auto eEntities = ConvertToPoints(GetEntities(Cutter(), wires, theTol));

	Standard_Integer k = 0;
	for (const auto& x : eEntities)
	{
		Debug_Null_Pointer(x);
		x->SetIndex(++k);

		entities.push_back(std::move(x));
	}

	Change_IsDone() = Standard_True;
}