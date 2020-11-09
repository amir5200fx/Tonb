#include <SectPx_ProfileMaker.hxx>

#include <SectPx_Pnts.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Registry.hxx>
#include <SectPx_ProfileQ.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::maker::Profile::MakeEdge
(
	const std::shared_ptr<SectPx_Pnt>& theP0, 
	const std::shared_ptr<SectPx_Pnt>& theP1
)
{
	Debug_If_Condition(theP0 IS_EQUAL theP1);

	auto segment = std::make_shared<SectPx_Edge>(theP0, theP1);
	Debug_Null_Pointer(segment);

	Debug_Null_Pointer(Registry());
	auto id = Registry()->Import(segment);

	AddEdgeToPnt(segment, theP0);
	AddEdgeToPnt(segment, theP1);

	return id;
}

std::shared_ptr<tnbLib::SectPx_Edge> 
tnbLib::maker::Profile::RemoveEdge
(
	const Standard_Integer theIndex
)
{
	Debug_Null_Pointer(Registry());

	auto item = Registry()->Remove(theIndex);
	auto edge = std::dynamic_pointer_cast<SectPx_Edge>(item);
	if (NOT edge)
	{
		FatalErrorIn(FunctionSIG)
			<< "the removed item is not edge" << endl
			<< abort(FatalError);
	}
	return std::move(edge);
}

void tnbLib::maker::Profile::RemoveEdge
(
	const std::shared_ptr<SectPx_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	Debug_Null_Pointer(Registry());

	const auto p0 = std::dynamic_pointer_cast<SectPx_TPnt>(theEdge->P0());
	const auto p1 = std::dynamic_pointer_cast<SectPx_TPnt>(theEdge->P1());

	auto seg0 = p0->RemoveFromEdges(theEdge->Index()).lock();
	auto seg1 = p1->RemoveFromEdges(theEdge->Index()).lock();

	Debug_If_Condition(seg0 NOT_EQUAL theEdge);
	Debug_If_Condition(seg1 NOT_EQUAL theEdge);

	Registry()->Remove(theEdge);
}

void tnbLib::maker::Profile::AddEdgeToPnt
(
	const std::shared_ptr<SectPx_Edge>& theSeg,
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	Debug_Null_Pointer(theSeg);
	Debug_Null_Pointer(thePnt);

	auto pnt = std::dynamic_pointer_cast<SectPx_TPnt>(thePnt);
	Debug_Null_Pointer(pnt);

	pnt->Import(theSeg->Index(), theSeg);
}

const std::shared_ptr<tnbLib::SectPx_Node>& 
tnbLib::maker::Profile::Node0() const
{
	Debug_Null_Pointer(TopoProfile());
	return TopoProfile()->Node0();
}

const std::shared_ptr<tnbLib::SectPx_Node>& 
tnbLib::maker::Profile::Node1() const
{
	Debug_Null_Pointer(TopoProfile());
	return TopoProfile()->Node1();
}

//Standard_Integer 
//tnbLib::maker::Profile::Init()
//{
//	Debug_Null_Pointer(Registry());
//	Debug_Null_Pointer(TopoProfile());
//
//	Debug_Null_Pointer(TopoProfile()->Node0());
//	Debug_Null_Pointer(TopoProfile()->Node1());
//
//	const auto& node0 = TopoProfile()->Node0();
//	const auto& node1 = TopoProfile()->Node1();
//
//	Debug_Null_Pointer(node0->Pnt());
//	Debug_Null_Pointer(node1->Pnt());
//
//	if (SectPx_PntTools::IsGeoField(node0->Pnt()))
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the geo_field_fun is forbidden for a boundary pnt!" << endl
//			<< abort(FatalError);
//	}
//
//	if (SectPx_PntTools::IsGeoField(node1->Pnt()))
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the geo_field_fun is forbidden for a boundary pnt!" << endl
//			<< abort(FatalError);
//	}
//
//	auto p0 = std::dynamic_pointer_cast<SectPx_TPnt>(node0->Pnt());
//	Debug_Null_Pointer(p0);
//
//	if (p0->NbEdges())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the p0 must be an orphan to be used as boundary profile!" << endl
//			<< abort(FatalError);
//	}
//
//	auto p1 = std::dynamic_pointer_cast<SectPx_TPnt>(node1->Pnt());
//	Debug_Null_Pointer(p1);
//
//	if (p1->NbEdges())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the p1 must be an orphan to be used as boundary profile!" << endl
//			<< abort(FatalError);
//	}
//
//	const auto id = MakeEdge(node0->Pnt(), node1->Pnt());
//
//	Change_IsDone() = Standard_True;
//	return id;
//}

Standard_Boolean 
tnbLib::maker::Profile::IsOnBoundary
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
) const
{
	Debug_Null_Pointer(Node0());
	Debug_Null_Pointer(Node1());

	Debug_Null_Pointer(Node0()->Pnt());
	Debug_Null_Pointer(Node1()->Pnt());

	if (thePnt IS_EQUAL Node0()->Pnt()) return Standard_True;
	if (thePnt IS_EQUAL Node1()->Pnt()) return Standard_True;
	return Standard_False;
}

std::shared_ptr<tnbLib::SectPx_Edge>
tnbLib::maker::Profile::SelectEdge
(
	const Standard_Integer theIndex
) const
{
	Debug_Null_Pointer(Registry());
	auto item = Registry()->SelectObj(theIndex);

	auto edge = std::dynamic_pointer_cast<SectPx_Edge>(item);
	if (NOT edge)
	{
		FatalErrorIn(FunctionSIG)
			<< "the selected item is not edge!" << endl
			<< " - index= " << theIndex << endl
			<< abort(FatalError);
	}
	return std::move(edge);
}

std::tuple<Standard_Integer, Standard_Integer> 
tnbLib::maker::Profile::ImportPnt
(
	const std::shared_ptr<SectPx_Pnt>& thePnt,
	const std::shared_ptr<SectPx_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);

	auto removed = RemoveEdge(theEdge->Index());
	if (removed NOT_EQUAL theEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory of data" << endl
			<< abort(FatalError);
	}

	const auto pnt0 = std::dynamic_pointer_cast<SectPx_TPnt>(removed->P0());
	const auto pnt1 = std::dynamic_pointer_cast<SectPx_TPnt>(removed->P1());
	Debug_Null_Pointer(pnt0);
	Debug_Null_Pointer(pnt1);

	if (pnt0)
	{
		auto removed0 = pnt0->RemoveFromEdges(removed->Index()).lock();
		Debug_If_Condition(removed0 NOT_EQUAL theEdge);
	}

	if (pnt1)
	{
		auto removed1 = pnt1->RemoveFromEdges(removed->Index()).lock();
		Debug_If_Condition(removed1 NOT_EQUAL theEdge);
	}

	auto snb0 = MakeEdge(pnt0, thePnt);
	auto snb1 = MakeEdge(thePnt, pnt1);

	auto t = std::make_tuple(snb0, snb1);
	return std::move(t);
}

Standard_Integer 
tnbLib::maker::Profile::RemovePnt
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	Debug_Null_Pointer(thePnt);
	if (IsOnBoundary(thePnt))
	{
		FatalErrorIn(FunctionSIG)
			<< "it's forbidden to remove a boundary pnt" << endl
			<< abort(FatalError);
	}

	auto tPnt = std::dynamic_pointer_cast<SectPx_TPnt>(thePnt);
	Debug_Null_Pointer(tPnt);

	Debug_If_Condition(tPnt->NbEdges() NOT_EQUAL 2);

	std::shared_ptr<SectPx_Pnt> pnt[2];
	std::shared_ptr<SectPx_Edge> removing[2];

	Standard_Integer k = 0;
	for (const auto& x : tPnt->Edges())
	{
		auto seg = x.second.lock();
		Debug_Null_Pointer(seg);

		removing[k++] = std::move(seg);
	}

	pnt[0] = removing[0]->Other(thePnt);
	pnt[1] = removing[1]->Other(thePnt);

	RemoveEdge(removing[0]);
	RemoveEdge(removing[1]);

	Debug_If_Condition(tPnt->NbEdges());
#ifdef _DEBUG
	if (pnt[0]->IsBoundary())
	{
		Debug_If_Condition(std::dynamic_pointer_cast<SectPx_TPnt>(pnt[0])->NbEdges());
	}
	else
	{
		Debug_If_Condition(std::dynamic_pointer_cast<SectPx_TPnt>(pnt[0])->NbEdges() NOT_EQUAL 1);
	}

	if (pnt[1]->IsBoundary())
	{
		Debug_If_Condition(std::dynamic_pointer_cast<SectPx_TPnt>(pnt[1])->NbEdges());
	}
	else
	{
		Debug_If_Condition(std::dynamic_pointer_cast<SectPx_TPnt>(pnt[1])->NbEdges() NOT_EQUAL 1);
	}
#endif // _DEBUG

	//thePnt->RemoveThisFromChilds();
	SectPx_Tools::RemoveParentFromChildren(thePnt);

	if (thePnt->HasChildMap())
	{
		for (Standard_Integer i = 0; i < thePnt->NbChildMaps(); i++)
		{
			auto parent = thePnt->ChildMap(i);
			if (parent)
			{
				Registry()->Remove(parent);
			}
		}
	}

	Registry()->Remove(thePnt);

	auto snb = MakeEdge(pnt[0], pnt[1]);
	auto segment = SelectEdge(snb);
	Debug_Null_Pointer(segment);

	return snb;
}

namespace tnbLib
{

	namespace maker
	{

		static std::shared_ptr<SectPx_Pnt>
			RetrieveNextPnt
			(
				const std::shared_ptr<SectPx_Pnt>& thePnt
			)
		{
			auto p0 = std::dynamic_pointer_cast<SectPx_TPnt>(thePnt);
			Debug_Null_Pointer(p0);

			for (const auto& x : p0->Edges())
			{
				auto segmt = x.second.lock();
				Debug_Null_Pointer(segmt);

				if (segmt->P0() IS_EQUAL thePnt)
				{
					return segmt->P1();
				}
			}
			FatalErrorIn(FunctionSIG)
				<< "something goes wrong!" << endl
				<< abort(FatalError);
			return nullptr;
		}
	}
}

std::shared_ptr<tnbLib::SectPx_ProfileQ> 
tnbLib::maker::Profile::RetrieveProfileQ() const
{
	Debug_Null_Pointer(Node0());
	Debug_Null_Pointer(Node0()->Pnt());

	Debug_Null_Pointer(Node1());
	Debug_Null_Pointer(Node1()->Pnt());

	auto profile = std::make_shared<SectPx_ProfileQ>();
	Debug_Null_Pointer(profile);

	auto& Q = profile->ChangeQ();
	Q.push_back(Node0()->Pnt());

	auto pt = RetrieveNextPnt(Node0()->Pnt());
	while (pt NOT_EQUAL Node1()->Pnt())
	{
		Q.push_back(pt);
		pt = RetrieveNextPnt(pt);
	}
	Q.push_back(Node1()->Pnt());
	return std::move(profile);
}

//Handle(Geom2d_Curve) 
//tnbLib::maker::Profile::RetrieveGeomCurve
//(
//	const Standard_Integer deg
//) const
//{
//	Debug_Null_Pointer(TopoProfile());
//	auto curve = TopoProfile()->RetrieveGeomCurve(deg);
//	return std::move(curve);
//}