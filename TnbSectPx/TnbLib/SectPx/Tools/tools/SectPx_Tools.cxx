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
#include <SectPx_WeightController.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <list>

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

std::shared_ptr<tnbLib::SectPx_Segment>
tnbLib::SectPx_Tools::CommonSegment
(
	const std::shared_ptr<SectPx_Pole>& thePole0,
	const std::shared_ptr<SectPx_Pole>& thePole1
)
{
	if (thePole0 IS_EQUAL thePole1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the two poles are the same!" << endl
			<< abort(FatalError);
	}

	auto[seg0, seg1] = RetrieveSegments(thePole0);
	auto[seg2, seg3] = RetrieveSegments(thePole1);

	if (seg1 IS_EQUAL seg2)
	{
		return std::move(seg1);
	}
	else if (seg3 IS_EQUAL seg0)
	{
		return std::move(seg0);
	}
	else
	{
		return nullptr;
	}
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

			Debug_If_Condition_Message(thePole IS_EQUAL seg->Pole1(), "appearently, the segment is inverted!");
			return seg->Pole1();
		}
		else
		{//- the pole is internal
			auto inter = std::dynamic_pointer_cast<SectPx_InterPole>(thePole);
			Debug_Null_Pointer(inter);

			auto seg = inter->Forward().lock();
			Debug_Null_Pointer(seg);

			Debug_If_Condition_Message(thePole IS_EQUAL seg->Pole1(), "appearently, the segment is inverted!");
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

		auto t = RetrieveBoundarySegment(bnd);
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

std::pair
<
	std::shared_ptr<tnbLib::SectPx_Segment>,
	std::shared_ptr<tnbLib::SectPx_Segment>
> 
tnbLib::SectPx_Tools::RetrieveBoundarySegment
(
	const std::shared_ptr<SectPx_BndPole>& bnd
)
{
	auto seg = bnd->Segment().lock();
	Debug_Null_Pointer(seg);

	if (seg->Pole0() IS_EQUAL bnd)
	{
		auto t = std::make_pair(nullptr, std::move(seg));
		return std::move(t);
	}
	else if (seg->Pole1() IS_EQUAL bnd)
	{
		auto t = std::make_pair(std::move(seg), nullptr);
		return std::move(t);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "something went wrong!" << endl
			<< abort(FatalError);
		auto t = std::make_pair(nullptr, nullptr);
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
			if (seg0 AND NOT seg1)
			{
				segments.push_back(std::move(seg0));
			}
			else if (seg1 AND NOT seg0)
			{
				segments.push_back(std::move(seg1));
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "Undefined behavior has been detected: "
					<< " for a boundary pole, there are two adjoint segments!" << endl
					<< abort(FatalError);
			}
		}
		else
		{
			segments.push_back(std::move(seg0));
			segments.push_back(std::move(seg1));
		}
	}
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Segment>> 
tnbLib::SectPx_Tools::RetrieveInnerSegments
(
	const std::vector<std::shared_ptr<SectPx_Pole>>& thePoles
)
{
	if (thePoles.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "not enough poles to retrieve the inner segments" << endl
			<< abort(FatalError);
		return std::vector<std::shared_ptr<tnbLib::SectPx_Segment>>();
	}
	auto iter = thePoles.begin();
	auto p0 = (*iter);
	iter++;

	std::vector<std::shared_ptr<SectPx_Segment>> segments;
	segments.reserve(thePoles.size() - 1);
	while (iter NOT_EQUAL thePoles.end())
	{
		auto p1 = (*iter);
		auto segment = CommonSegment(p0, p1);
		if (NOT segment)
		{
			FatalErrorIn(FunctionSIG)
				<< "there is no common segment between two poles" << endl
				<< abort(FatalError);
		}
		segments.push_back(std::move(segment));

		iter++;
		p0 = p1;
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

	auto pnts = RetrieveControlPoints(segments);
	return std::move(pnts);
}

std::vector<tnbLib::Pnt2d> 
tnbLib::SectPx_Tools::RetrieveControlPoints
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
)
{
	const auto& segments = theSegments;
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

std::vector<std::shared_ptr<tnbLib::SectPx_Pnt>> 
tnbLib::SectPx_Tools::RetrieveInnerPoints
(
	const std::shared_ptr<SectPx_TopoProfile>& theProfile
)
{
	Debug_Null_Pointer(theProfile->Node0());
	Debug_Null_Pointer(theProfile->Node1());
	auto pnts = SectPx_PntTools::TrackPnts(theProfile->Node0(), theProfile->Node1());

	std::vector<std::shared_ptr<SectPx_Pnt>> inners;
	inners.reserve(pnts.size() - 2);
	for (size_t i = 1; i < pnts.size() - 1; i++)
	{
		auto& x = pnts[i];
		inners.push_back(std::move(x));
	}
	return std::move(inners);
}

std::vector<Standard_Real> 
tnbLib::SectPx_Tools::RetrieveWeights
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
)
{
	const auto& segments = theSegments;
	const auto first = segments[0]->Pole0()->Coord();
	std::vector<Standard_Real> weights;

	const auto corner = std::dynamic_pointer_cast<sectPxLib::Pole_Corner>(segments[0]->Pole0());
	if (corner)
	{
		auto w = (Standard_Real)1.0;
		for (const auto& x : corner->Controllers())
		{
			auto c = std::dynamic_pointer_cast<sectPxLib::WeightController>(x.second.lock());
			if (c)
			{
				Debug_Null_Pointer(c->Weight().lock());
				w = c->Weight().lock()->Value();
				break;
			}
		}
		weights.push_back(w);
	}
	else
	{
		weights.push_back(1.0);
	}
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
				weights.push_back(1.0);
			}
		}
		const auto corner = std::dynamic_pointer_cast<sectPxLib::Pole_Corner>(x->Pole1());
		if (corner)
		{
			auto w = (Standard_Real)1.0;
			for (const auto& x : corner->Controllers())
			{
				auto c = std::dynamic_pointer_cast<sectPxLib::WeightController>(x.second.lock());
				if (c)
				{
					Debug_Null_Pointer(c->Weight().lock());
					w = c->Weight().lock()->Value();
					break;
				}
			}
			weights.push_back(w);
		}
		else
		{
			weights.push_back(1.0);
		}
	}
	return std::move(weights);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Pole>> 
tnbLib::SectPx_Tools::RetrievePoles
(
	const std::shared_ptr<SectPx_CurveQ>& theSeg
)
{
	auto poles = TrackPoles(theSeg->Pole0(), theSeg->Pole1());
	return std::move(poles);
}

namespace tnbLib
{
	Standard_Boolean IsInsiderOrBundary(const std::shared_ptr<SectPx_Pole>& thePole)
	{
		if (thePole->IsBoundary())
		{
			return Standard_True;
		}
		if (std::dynamic_pointer_cast<sectPxLib::Pole_Slider>(thePole))
		{
			return Standard_True;
		}
		return Standard_False;
	}

	std::shared_ptr<SectPx_CurveQ> TrackCurve(std::list<std::shared_ptr<SectPx_Segment>>& theList)
	{
		auto seg = theList.front();
		theList.pop_front();
		const auto& p0 = seg->Pole0();

		while (theList.size())
		{
			if (IsInsiderOrBundary(seg->Pole1()))
			{
				auto curve = std::make_shared<SectPx_CurveQ>(p0, seg->Pole1());
				return std::move(curve);
			}
			seg = theList.front();
			theList.pop_front();
		}
		if (IsInsiderOrBundary(seg->Pole1()))
		{
			auto curve = std::make_shared<SectPx_CurveQ>(p0, seg->Pole1());
			return std::move(curve);
		}
		return nullptr;
	}
}

std::vector<std::shared_ptr<tnbLib::SectPx_CurveQ>> 
tnbLib::SectPx_Tools::RetrieveSubCurveQ
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
)
{
	const auto& p0 = theSegments[0]->Pole0();
	const auto& p1 = theSegments[theSegments.size() - 1]->Pole1();
	if (NOT IsInsiderOrBundary(p0))
	{
		FatalErrorIn(FunctionSIG)
			<< "the first pole must be boundary or slider" << endl
			<< abort(FatalError);
	}
	if (NOT IsInsiderOrBundary(p1))
	{
		FatalErrorIn(FunctionSIG)
			<< "the last pole must be boundary or slider" << endl
			<< abort(FatalError);
	}

	Standard_Integer k = 0;
	std::list<std::shared_ptr<SectPx_Segment>> segList;
	for (const auto& x : theSegments)
	{
		Debug_Null_Pointer(x);
		segList.push_back(x);
	}

	std::vector<std::shared_ptr<SectPx_CurveQ>> curves;
	while (segList.size())
	{
		auto curve = TrackCurve(segList);
		if (NOT curve)
		{
			FatalErrorIn(FunctionSIG)
				<< "unable to track the curve" << endl
				<< abort(FatalError);
		}
		curves.push_back(std::move(curve));
	}
	return std::move(curves);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Pole>> 
tnbLib::SectPx_Tools::RetrievePoles
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
)
{
	std::vector<std::shared_ptr<SectPx_Pole>> poles;
	poles.reserve(theSegments.size() + 1);
	for (const auto& x : theSegments)
	{
		Debug_Null_Pointer(x);
		const auto& p0 = x->Pole0();
		poles.push_back(p0);		
	}
	poles.push_back(theSegments[theSegments.size() - 1]->Pole1());
	return std::move(poles);
}

std::vector<std::pair<Standard_Real, Standard_Integer>>
tnbLib::SectPx_Tools::KnotsNoInnerSlider
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments,
	const Standard_Integer theDegree,
	const Standard_Real u0,
	const Standard_Real u1
)
{
	if (u1 <= u0)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid boundary knot values" << endl
			<< abort(FatalError);
	}

	auto poles = RetrievePoles(theSegments);
	if (NOT IsInsiderOrBundary(poles[0]))
	{
		FatalErrorIn(FunctionSIG)
			<< "the first pole must be boundary or slider" << endl
			<< abort(FatalError);
	}
	if (NOT IsInsiderOrBundary(poles[poles.size()-1]))
	{
		FatalErrorIn(FunctionSIG)
			<< "the last pole must be boundary or slider" << endl
			<< abort(FatalError);
	}
	//- check for inner slider poles
	for (size_t i = 1; i < poles.size() - 1; i++)
	{
		const auto& x = poles[i];
		if (std::dynamic_pointer_cast<sectPxLib::Pole_Slider>(x))
		{
			FatalErrorIn(FunctionSIG)
				<< "there must be no slider pole between the segments" << endl
				<< abort(FatalError);
		}
	}
	auto pnts = RetrieveControlPoints(theSegments);
	if (pnts.size() <= theDegree)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid degree for the curve" << endl
			<< "p = " << theDegree << endl
			<< "n = " << pnts.size() << endl
			<< abort(FatalError);
	}
	auto knots = Knots((Standard_Integer)pnts.size(), theDegree, u0, u1);
	return std::move(knots);
}

std::vector<std::pair<Standard_Real, Standard_Integer>>  
tnbLib::SectPx_Tools::Knots
(
	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments,
	const Standard_Integer theDegree
)
{
	Debug_If_Condition(theSegments.empty());

	auto subCurves = RetrieveSubCurveQ(theSegments);
	Debug_If_Condition(subCurves.empty());

	Standard_Real u0 = 0;
	static const Standard_Real du = 1.0;
	std::vector<std::pair<Standard_Real, Standard_Integer>> knots;
	for (const auto& x : subCurves)
	{
		Debug_Null_Pointer(x);
		auto poles = RetrievePoles(x);

		auto segments = RetrieveInnerSegments(poles);

		auto knot = KnotsNoInnerSlider(segments, theDegree, u0, u0 + du);
		u0 += du;

		Add(knots, knot);
	}
	return std::move(knots);
}

std::pair<TColStd_Array1OfReal, TColStd_Array1OfInteger> 
tnbLib::SectPx_Tools::Knots
(
	const std::vector<std::pair<Standard_Real, Standard_Integer>>& theKnots
)
{
	TColStd_Array1OfReal knots(1, (Standard_Integer)theKnots.size());
	TColStd_Array1OfInteger mults(1, (Standard_Integer)theKnots.size());
	Standard_Integer K = 0;
	for (const auto& x : theKnots)
	{
		K++;
		knots.SetValue(K, x.first);
		mults.SetValue(K, x.second);
	}
	auto paired = std::make_pair(std::move(knots), std::move(mults));
	return std::move(paired);
}

std::vector<std::pair<Standard_Real, Standard_Integer>> 
tnbLib::SectPx_Tools::Knots
(
	const Standard_Integer theNbQ, 
	const Standard_Integer theDegree,
	const Standard_Real theU0, 
	const Standard_Real theU1
)
{
	if (theNbQ - 1 < theDegree)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid degree for the curve" << endl
			<< "p = " << theDegree << endl
			<< "n = " << theNbQ << endl
			<< abort(FatalError);
	}
	const auto u0 = theU0;
	const auto u1 = theU1;
	const auto n = theNbQ - 1;
	const auto p = theDegree;
	const auto nbKnots = n + p + 2;
	const auto nbInners = nbKnots - 2 * (p + 1);
	Debug_If_Condition(nbInners < 0);
	const auto du = (u1 - u0) / (nbInners + 1);

	std::vector<std::pair<Standard_Real, Standard_Integer>> Knots;
	Knots.reserve(nbInners + 2);
	for (size_t i = 0; i < nbInners + 2; i++)
	{
		auto u = u0 + i * du;
		auto paired = std::make_pair(u, 1);
		Knots.push_back(std::move(paired));
	}
	Knots[0].second = p + 1;
	Knots[Knots.size() - 1].second = p + 1;
	return std::move(Knots);
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

TColStd_Array1OfReal 
tnbLib::SectPx_Tools::Weights
(
	const std::vector<Standard_Real>& theKnots
)
{
	TColStd_Array1OfReal ws(1, (Standard_Integer)theKnots.size());
	Standard_Integer id = 0;
	for (auto x : theKnots)
	{
		ws.SetValue(++id, x);
	}
	return std::move(ws);
}

TColgp_Array1OfPnt2d 
tnbLib::SectPx_Tools::CPts
(
	const std::vector<Pnt2d>& thePoints
)
{
	TColgp_Array1OfPnt2d pnts(1, (Standard_Integer)thePoints.size());
	Standard_Integer id = 0;
	for (const auto& x : thePoints)
	{
		pnts.SetValue(++id, x);
	}
	return std::move(pnts);
}

void tnbLib::SectPx_Tools::disJiont
(
	const std::shared_ptr<SectPx_Interface>& theInterface
)
{
	Debug_Null_Pointer(theInterface);
	theInterface->disJoint();
}

void tnbLib::SectPx_Tools::Add
(
	std::vector<std::pair<Standard_Real, Standard_Integer>>& theCurrent, 
	const std::vector<std::pair<Standard_Real, Standard_Integer>>& theKnot
)
{
	if (theKnot.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid knot vector" << endl
			<< abort(FatalError);
	}
	if (theCurrent.empty())
	{
		theCurrent = theKnot;
		return;
	}
	auto& Un = theCurrent[theCurrent.size() - 1];
	auto U0 = theKnot[0];
	if (Un.second NOT_EQUAL U0.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "the two knot vectors are not the same degree" << endl
			<< abort(FatalError);
	}
	Un.second -= 1;
	std::vector<std::pair<Standard_Real, Standard_Integer>> knots;
	knots.reserve(theCurrent.size() + theKnot.size() - 1);
	for (const auto& x : theCurrent)
	{
		knots.push_back(std::move(x));
	}

	for (size_t i = 1; i < theKnot.size(); i++)
	{		
		knots.push_back(theKnot[i]);
	}
	theCurrent = std::move(knots);
}