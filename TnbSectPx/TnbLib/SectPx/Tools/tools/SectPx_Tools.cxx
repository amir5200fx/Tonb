#include <SectPx_Tools.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_Pole.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Segment.hxx>
#include <SectPx_PointMaker.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <SectPx_Interface.hxx>
#include <SectPx_Poles.hxx>
#include <SectPx_CPtsMap.hxx>
#include <SectPx_TopoSegment.hxx>
#include <SectPx_CurveQ.hxx>
#include <SectPx_SegmentController.hxx>
#include <SectPx_PoleController.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::SectPx_Tools::IsValidToJoint
(
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1,
	const SectPx_JoinPriority priority
)
{
	if (priority IS_EQUAL SectPx_JoinPriority::right)
	{
		return IsValidToJoint(theNode1, theNode0, SectPx_JoinPriority::left);
	}

	const auto& p0 = theNode0->Pnt();
	const auto& p1 = theNode1->Pnt();

	if (NOT p0->IsMaster())
		return Standard_False;

	if (NOT p1->IsSlave())
		return Standard_False;

	auto slave =
		std::dynamic_pointer_cast<sectPxLib::Pnt_Empty>(p1);
	Debug_Null_Pointer(slave);

	if (slave->Master() NOT_EQUAL p0)
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Integer
tnbLib::SectPx_Tools::MakePair
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1,
	const std::shared_ptr<SectPx_FrameRegistry>& theReg,
	const SectPx_JoinPriority priority
)
{
	if (theP0->IsInner() OR theP1->IsInner())
	{
		FatalErrorIn(FunctionSIG)
			<< "the two points must be outer for pairing" << endl
			<< abort(FatalError);
	}

	if (priority IS_EQUAL SectPx_JoinPriority::right)
	{
		return MakePair(theP1, theP0, theReg, SectPx_JoinPriority::left);
	}

	if (NOT theP1->IsMaster())
	{
		FatalErrorIn(FunctionSIG)
			<< "the selected point is not master!" << endl
			<< abort(FatalError);
	}

	if (theP0->IsSlave())
	{
		auto empty = std::dynamic_pointer_cast<sectPxLib::Pnt_Empty>(theP0);
		Debug_Null_Pointer(empty);

		if (empty->Master() IS_EQUAL theP1)
		{
			return empty->Index();
		}
		else
		{
			auto master = std::dynamic_pointer_cast<SectPx_MasterPnt>(theP1);
			Debug_Null_Pointer(master);

			empty->SetMaster(master);
			return empty->Index();
		}
	}

	auto master = std::dynamic_pointer_cast<SectPx_MasterPnt>(theP1);
	Debug_Null_Pointer(master);

	auto maker = std::make_shared<maker::Point>(theReg);
	Debug_Null_Pointer(maker);

	auto id = maker->CreateEmpty(master);

	auto empty = maker->SelectPnt(id);
	Debug_Null_Pointer(empty);

	SectPx_PntTools::Replace(theP0, empty);

	return id;
}

std::tuple<Standard_Integer, Standard_Integer>
tnbLib::SectPx_Tools::MakeJoint
(
	const std::shared_ptr<SectPx_TopoProfile>& theLeft,
	const std::shared_ptr<SectPx_TopoProfile>& theRight,
	const std::shared_ptr<SectPx_FrameRegistry>& theReg,
	const SectPx_JoinPriority priority
)
{
	Debug_Null_Pointer(theLeft);
	Debug_Null_Pointer(theRight);

	const auto& leftNode = theLeft->Node1();
	const auto& rightNode = theRight->Node0();

	if (NOT IsValidToJoint(leftNode, rightNode, priority))
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to joint two profiles" << endl
			<< "make sure the intersection points are paired together before calling this function" << endl
			<< abort(FatalError);
	}

	auto maker = std::make_shared<maker::Interface>(theReg);
	Debug_Null_Pointer(maker);

	auto t = maker->CreateJoint(leftNode, rightNode);
	return std::move(t);
}

std::shared_ptr<tnbLib::SectPx_Edge> 
tnbLib::SectPx_Tools::MakeEdge
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1,
	const std::shared_ptr<SectPx_FrameRegistry>& theReg
)
{
	auto seg = std::make_shared<SectPx_Edge>(theP0, theP1);
	Debug_Null_Pointer(seg);

	auto seg_id = theReg->Import(seg);

	auto tp0 = std::dynamic_pointer_cast<SectPx_TPnt>(theP0);
	Debug_Null_Pointer(tp0);

	auto tp1 = std::dynamic_pointer_cast<SectPx_TPnt>(theP1);
	Debug_Null_Pointer(tp1);

	tp0->Import(seg_id, seg);
	tp1->Import(seg_id, seg);

	return std::move(seg);
}

namespace tnbLib
{

	std::shared_ptr<SectPx_Pole>
		TrackNextPole(const std::shared_ptr<SectPx_Pole>& thePole)
	{
		if (thePole->IsBoundary())
		{
			auto bnd = std::dynamic_pointer_cast<SectPx_BndPole>(thePole);
			Debug_Null_Pointer(bnd);

			auto seg = bnd->Segment().lock();
			Debug_Null_Pointer(seg);

			Debug_If_Condition_Message(thePole IS_EQUAL seg->Pole1(), "appearently, the semnet is inverted!");
			return seg->Pole1();
		}
		else
		{//- the pole is internal
			auto inter = std::dynamic_pointer_cast<SectPx_InterPole>(thePole);
			Debug_Null_Pointer(inter);

			auto seg = inter->Forward().lock();
			Debug_Null_Pointer(seg);

			Debug_If_Condition_Message(thePole IS_EQUAL seg->Pole1(), "appearently, the semnet is inverted!");
			return seg->Pole1();
		}
		
	}
}

std::vector<std::shared_ptr<tnbLib::SectPx_Pole>> 
tnbLib::SectPx_Tools::TrackPoles
(
	const std::shared_ptr<SectPx_Pole>& thePole0,
	const std::shared_ptr<SectPx_Pole>& thePole1
)
{
	Debug_Null_Pointer(thePole0);
	Debug_Null_Pointer(thePole1);

	if (thePole0 IS_EQUAL thePole1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the two poles are the same!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<SectPx_Pole>> poles;
	poles.push_back(thePole0);

	auto pole = TrackNextPole(thePole0);
	while (pole NOT_EQUAL thePole1)
	{
		poles.push_back(pole);
		auto pole0 = pole;
		pole = TrackNextPole(pole);
		if (pole0 IS_EQUAL pole)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to track the inner poles" << endl
				<< abort(FatalError);
		}
	}
	poles.push_back(thePole1);
	return std::move(poles);
}

std::pair
<
	std::shared_ptr<tnbLib::SectPx_Segment>,
	std::shared_ptr<tnbLib::SectPx_Segment>
> 
tnbLib::SectPx_Tools::RetrieveSegments
(
	const std::shared_ptr<SectPx_Pole>& thePole
)
{
	Debug_Null_Pointer(thePole);
	if (thePole->IsBoundary())
	{
		auto bnd = std::dynamic_pointer_cast<SectPx_BndPole>(thePole);
		Debug_Null_Pointer(bnd);

		auto seg = bnd->Segment().lock();
		Debug_Null_Pointer(seg);
		
		auto t = std::make_pair(std::move(seg), nullptr);
		return std::move(t);
	}
	else
	{//- the pole is internal
		auto inter = std::dynamic_pointer_cast<SectPx_InterPole>(thePole);
		Debug_Null_Pointer(inter);

		auto seg0 = inter->Backward().lock();
		Debug_Null_Pointer(seg0);

		auto seg1 = inter->Forward().lock();
		Debug_Null_Pointer(seg1);

		auto t = std::make_pair(std::move(seg0), std::move(seg1));
		return std::move(t);
	}
}

std::vector<std::shared_ptr<tnbLib::SectPx_Segment>> 
tnbLib::SectPx_Tools::RetrieveSegments
(
	const std::vector<std::shared_ptr<SectPx_Pole>>& thePoles
)
{
	std::vector<std::shared_ptr<SectPx_Segment>> segments;
	for (const auto& x : thePoles)
	{
		Debug_Null_Pointer(x);
		auto[seg0, seg1] = RetrieveSegments(x);
		
		if (x->IsBoundary())
		{
			Debug_If_Condition(seg1);
			segments.push_back(std::move(seg0));
		}
		else
		{
			segments.push_back(std::move(seg0));
			segments.push_back(std::move(seg1));
		}
	}
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>> 
tnbLib::SectPx_Tools::RetrieveChildren
(
	const std::shared_ptr<SectPx_TopoSegment>& theSeg
)
{
	Debug_Null_Pointer(theSeg);
	Debug_Null_Pointer(theSeg->Pole0());
	Debug_Null_Pointer(theSeg->Pole1());

	auto poles = TrackPoles(theSeg->Pole0(), theSeg->Pole1());
	auto segments = RetrieveSegments(poles);

	std::map<Standard_Integer, std::shared_ptr<SectPx_Child>> childMap;
	for (const auto& x : poles)
	{
		Debug_Null_Pointer(x);
		const auto& pnt = x->Pnt();

		auto childList = RetrieveChildren(pnt);
		for (const auto& c : childList)
		{
			Debug_Null_Pointer(c);
			auto paired = std::make_pair(c->Index(), std::move(c));
			auto insert = childMap.insert(std::move(paired));
			if (NOT insert.second)
			{
				//- the parameter already been registered!
				//- do nothing
			}
		}
	}

	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x);
		const auto& controller = x->Controller().lock();
		if (controller)
		{
			auto childList = RetrieveChildren(controller);
			for (const auto& c : childList)
			{
				Debug_Null_Pointer(c);
				auto paired = std::make_pair(c->Index(), std::move(c));
				auto insert = childMap.insert(std::move(paired));
				if (NOT insert.second)
				{
					//- the parameter already been registered!
					//- do nothing
				}
			}
		}
	}

	for (const auto& x : poles)
	{
		Debug_Null_Pointer(x);
		auto corner = std::dynamic_pointer_cast<sectPxLib::Pole_Corner>(x);
		if (corner)
		{
			if (corner->HasController())
			{
				const auto& controllers = corner->Controllers();
				for (const auto& ctrl : controllers)
				{
					Debug_Null_Pointer(ctrl.second.lock());
					auto plc = ctrl.second.lock();
					if (NOT plc->IsOnPole()) // controllers that not on the pole are registered before!
						continue;
					auto childList = RetrieveChildren(plc);
					for (const auto& c : childList)
					{
						Debug_Null_Pointer(c);
						auto paired = std::make_pair(c->Index(), std::move(c));
						auto insert = childMap.insert(std::move(paired));
						if (NOT insert.second)
						{
							//- the parameter already been registered!
							//- do nothing
						}
					}
				}
			}
		}
	}

	std::vector<std::shared_ptr<SectPx_Child>> children;
	children.reserve(childMap.size());
	for (const auto& x : childMap)
	{
		Debug_Null_Pointer(x.second);
		const auto& child = x.second;
		children.push_back(std::move(child));
	}
	return std::move(children);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Child>>
tnbLib::SectPx_Tools::RetrieveChildren
(
	const std::shared_ptr<SectPx_Parent>& theParent
)
{
	Debug_Null_Pointer(theParent);
	if (theParent->HasChildren())
	{
		auto childList = theParent->RetrieveChildren();
		return std::move(childList);
	}
	else if (theParent->HasChildMap())
	{ //- the parent has no children
		const auto nbChildMap = theParent->NbChildMaps();
		Debug_If_Condition_Message(NOT nbChildMap, "the parent has no childMap");

		std::map<Standard_Integer, std::shared_ptr<SectPx_Child>> childMap;
		for (Standard_Integer i = 0; i < nbChildMap; i++)
		{
			const auto& map = theParent->ChildMap(i);
			auto childList = RetrieveChildren(map);
			for (const auto& x : childList)
			{
				Debug_Null_Pointer(x);
				auto paired = std::make_pair(x->Index(), x);
				auto insert = childMap.insert(std::move(paired));
				if (NOT insert.second)
				{
					//- the parameter already been registered!
					//- do nothing
				}
			}
		}

		std::vector<std::shared_ptr<SectPx_Child>> childList;
		for (const auto& x : childMap)
		{
			Debug_Null_Pointer(x.second);
			childList.push_back(std::move(x.second));
		}
		return std::move(childList);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< " the parent has no children nor any childMaps" << endl
			<< " typename = " << theParent->RegObjTypeName() << endl
			<< abort(FatalError);
	}
	return std::vector<std::shared_ptr<SectPx_Child>>();
}

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_Tools::RetrieveControlPoints
(
	const std::shared_ptr<SectPx_TopoSegment>& theSeg
)
{
	auto poles = TrackPoles(theSeg->Pole0(), theSeg->Pole1());
	auto segments = RetrieveSegments(poles);

	const auto first = segments[0]->Pole0()->Coord();
	std::vector<Pnt2d> Q;
	Q.push_back(std::move(first));

	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x);
		if (x->HasController())
		{
			auto controller = x->Controller().lock();
			Debug_Null_Pointer(controller);

			const auto& cpts = controller->CPts();
			Debug_Null_Pointer(cpts);

			auto pts = cpts->Pts();

			for (const auto& p : pts)
			{
				Q.push_back(std::move(p));
			}
		}
		Q.push_back(x->Pole1()->Coord());
	}
	return std::move(Q);
}

std::vector<tnbLib::Pnt2d>
tnbLib::SectPx_Tools::RetrieveControlPoints
(
	const std::shared_ptr<SectPx_CurveQ>& theSeg
)
{
	auto poles = TrackPoles(theSeg->Pole0(), theSeg->Pole1());
	auto segments = RetrieveSegments(poles);

	const auto first = segments[0]->Pole0()->Coord();
	std::vector<Pnt2d> Q;
	Q.push_back(std::move(first));

	for (const auto& x : segments)
	{
		Debug_Null_Pointer(x);
		if (x->HasController())
		{
			auto controller = x->Controller().lock();
			Debug_Null_Pointer(controller);

			const auto& cpts = controller->CPts();
			Debug_Null_Pointer(cpts);

			auto pts = cpts->Pts();

			for (const auto& p : pts)
			{
				Q.push_back(std::move(p));
			}
		}
		Q.push_back(x->Pole1()->Coord());
	}
	return std::move(Q);
}

void tnbLib::SectPx_Tools::RemoveParentFromChildren
(
	const std::shared_ptr<SectPx_Parent>& theParent
)
{
	if (theParent->HasChildren())
	{
		theParent->RemoveThisFromChildren();
	}
	else if (theParent->HasChildMap())
	{
		for (Standard_Integer i = 0; i < theParent->NbChildMaps(); i++)
		{
			auto parent = theParent->ChildMap(i);
			if (parent)
			{
				RemoveParentFromChildren(parent);
			}
		}
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unexpected error has been occurred: unspecified parent type!" << endl
			<< " typename: " << theParent->RegObjTypeName() << endl
			<< abort(FatalError);
	}
}

void tnbLib::SectPx_Tools::disJiont
(
	const std::shared_ptr<SectPx_Interface>& theInterface
)
{
	Debug_Null_Pointer(theInterface);
	theInterface->disJoint();
}