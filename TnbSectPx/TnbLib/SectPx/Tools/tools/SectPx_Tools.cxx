#include <SectPx_Tools.hxx>

#include <SectPx_Pole.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_Node.hxx>
#include <SectPx_Segment.hxx>
#include <SectPx_PointMaker.hxx>
#include <SectPx_PntTools.hxx>
#include <SectPx_TopoProfile.hxx>
#include <SectPx_InterfaceMaker.hxx>
#include <error.hxx>
#include <OSstream.hxx>

Standard_Boolean
tnbLib::SectPx_Tools::IsValidToJoint
(
	const std::shared_ptr<SectPx_Node>& theNode0,
	const std::shared_ptr<SectPx_Node>& theNode1,
	const jointPriority priority
)
{
	if (priority IS_EQUAL jointPriority::right)
	{
		return IsValidToJoint(theNode1, theNode0, jointPriority::left);
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
	const std::shared_ptr<SectPx_Registry>& theReg,
	const jointPriority priority
)
{
	if (theP0->IsInner() OR theP1->IsInner())
	{
		FatalErrorIn(FunctionSIG)
			<< "the two points must be outer for pairing" << endl
			<< abort(FatalError);
	}

	if (priority IS_EQUAL jointPriority::right)
	{
		return MakePair(theP1, theP0, theReg, jointPriority::left);
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
	const std::shared_ptr<SectPx_Registry>& theReg,
	const jointPriority priority
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

//std::vector<tnbLib::Pnt2d>
//tnbLib::SectPx_Tools::RetrieveControlPoints
//(
//	const std::vector<std::shared_ptr<SectPx_Segment>>& theSegments
//)
//{
//	Debug_Null_Pointer(theSegments[0]->Pole0());
//	const auto first = theSegments[0]->Pole0()->Coord();
//
//	std::vector<Pnt2d> Q;
//	Q.push_back(first);
//
//	for (const auto& x : theSegments)
//	{
//		Debug_Null_Pointer(x);
//		if (x->HasController())
//		{
//			auto pts = x->RetrieveControlPoints();
//			for (const auto& p : pts)
//			{
//				Q.push_back(p);
//			}
//		}
//
//		Q.push_back(x->Pole1()->Coord());
//	}
//	return std::move(Q);
//}

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