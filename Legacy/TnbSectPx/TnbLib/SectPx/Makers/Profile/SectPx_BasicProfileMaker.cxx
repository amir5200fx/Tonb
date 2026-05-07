#include <SectPx_BasicProfileMaker.hxx>

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

Standard_Integer
tnbLib::maker::BasicProfile::MakeEdge
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
tnbLib::maker::BasicProfile::RemoveEdge
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

void tnbLib::maker::BasicProfile::RemoveEdge
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

void tnbLib::maker::BasicProfile::AddEdgeToPnt
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

std::shared_ptr<tnbLib::SectPx_Edge>
tnbLib::maker::BasicProfile::SelectEdge
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
tnbLib::maker::BasicProfile::ImportPnt
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
