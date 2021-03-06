#include <SectPx_ProfileMaker.hxx>

#include <SectPx_Pnts.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ProfileQ.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_Tools.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

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

Standard_Integer 
tnbLib::maker::Profile::RemovePnt
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	Debug_Null_Pointer(thePnt);

	if (thePnt->HasChildMap())
	{
		FatalErrorIn(FunctionSIG)
			<< " the point is under the usage of a geometric map!" << endl
			<< " if you insist on to remove this point, make sure you have "
			<< " removed all the geometric maps that use this point." << endl
			<< abort(FatalError);
	}

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