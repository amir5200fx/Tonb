#include <SectPx_PntTools.hxx>

#include <SectPx_Node.hxx>
#include <SectPx_Pnts.hxx>
#include <SectPx_Edge.hxx>
#include <SectPx_Makers.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//Standard_Integer
//tnbLib::SectPx_PntTools::NbParents
//(
//	const std::shared_ptr<SectPx_Coord>& thePnt
//)
//{
//	Debug_Null_Pointer(thePnt);
//	return thePnt->NbParents();
//}
//
//Standard_Boolean
//tnbLib::SectPx_PntTools::HasParent
//(
//	const std::shared_ptr<SectPx_Coord>& thePnt
//)
//{
//	return (Standard_Boolean)NbParents(thePnt);
//}

Standard_Boolean
tnbLib::SectPx_PntTools::IsRemovable
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	Debug_Null_Pointer(thePnt);
	auto tpt = std::dynamic_pointer_cast<SectPx_TPnt>(thePnt);
	Debug_Null_Pointer(tpt);
	return NOT tpt->NbEdges();
}

Standard_Boolean
tnbLib::SectPx_PntTools::IsEmpty
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	return (Standard_Boolean)
		std::dynamic_pointer_cast<sectPxLib::Pnt_Empty>(thePnt);
}

Standard_Boolean
tnbLib::SectPx_PntTools::IsComponent
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	return (Standard_Boolean)
		std::dynamic_pointer_cast<sectPxLib::Pnt_Compnt>(thePnt);
}

Standard_Boolean
tnbLib::SectPx_PntTools::IsGeoField
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	return (Standard_Boolean)
		std::dynamic_pointer_cast<sectPxLib::Pnt_GeoField>(thePnt);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Pnt>>
tnbLib::SectPx_PntTools::MakeOffsetPnts
(
	const std::vector<Pnt2d>& theCoords, 
	const std::shared_ptr<SectPx_FrameRegistry>& theRegistry
)
{
	Debug_Null_Pointer(theRegistry);

	if (theCoords.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "there are no enough points to create a profile" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<SectPx_Pnt>> pnts;
	pnts.reserve(theCoords.size());

	auto p0 = 
		std::make_shared<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>>
		(
			theCoords[0].X(),
			theCoords[0].Y()
			);
	auto pn = 
		std::make_shared<sectPxLib::OuterPnt<sectPxLib::Pnt_Offset>>
		(
			theCoords[theCoords.size() - 1].X(),
			theCoords[theCoords.size() - 1].Y()
			);

	pnts.push_back(std::move(p0));

	for (size_t i = 1; i < theCoords.size() - 1; i++)
	{
		auto pt = 
			std::make_shared<sectPxLib::InnerPnt<sectPxLib::Pnt_Offset>>
			(
				theCoords[i].X(),
				theCoords[i].Y()
				);
		pnts.push_back(std::move(pt));
	}

	pnts.push_back(std::move(pn));

	for (const auto& x : pnts)
	{
		Debug_Null_Pointer(x);
		theRegistry->Import(x);
	}

	for (size_t i = 0; i < pnts.size() - 1; i++)
	{
		const auto& p0 = pnts[i];
		const auto& p1 = pnts[i + 1];

		auto seg = std::make_shared<SectPx_Edge>(p0, p1);
		Debug_Null_Pointer(seg);

		auto id = theRegistry->Import(seg);

		auto tp0 = std::dynamic_pointer_cast<SectPx_TPnt>(p0);
		Debug_Null_Pointer(tp0);

		auto tp1 = std::dynamic_pointer_cast<SectPx_TPnt>(p1);
		Debug_Null_Pointer(tp1);

		tp0->Import(id, seg);
		tp1->Import(id, seg);
	}
	return std::move(pnts);
}

namespace tnbLib
{
	std::shared_ptr<SectPx_Pnt> 
		TrackNextPnt(const std::shared_ptr<SectPx_Pnt>& thePnt)
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

std::vector<std::shared_ptr<tnbLib::SectPx_Pnt>> 
tnbLib::SectPx_PntTools::TrackPnts
(
	const std::shared_ptr<SectPx_Node>& theNode0, 
	const std::shared_ptr<SectPx_Node>& theNode1
)
{
	Debug_Null_Pointer(theNode0);
	Debug_Null_Pointer(theNode1);

	Debug_Null_Pointer(theNode0->Pnt());
	Debug_Null_Pointer(theNode1->Pnt());

	std::vector<std::shared_ptr<SectPx_Pnt>> pnts;
	pnts.push_back(theNode0->Pnt());

	auto pt = TrackNextPnt(theNode0->Pnt());
	while (pt NOT_EQUAL theNode1->Pnt())
	{
		pnts.push_back(pt);
		pt = TrackNextPnt(pt);
	}
	pnts.push_back(theNode1->Pnt());
	return std::move(pnts);
}

std::vector<std::shared_ptr<tnbLib::SectPx_Pnt>> 
tnbLib::SectPx_PntTools::Neighbors
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	std::vector<std::shared_ptr<SectPx_Pnt>> neighbors;
	neighbors.reserve(2);

	auto tPnt = std::dynamic_pointer_cast<SectPx_TPnt>(thePnt);
	Debug_Null_Pointer(tPnt);

	const auto& edges = tPnt->Edges();
	for (const auto& x : edges)
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		const auto& p0 = edge->P0();
		const auto& p1 = edge->P0();

		if (p0 NOT_EQUAL thePnt)
		{
			neighbors.push_back(p0);
		}
		if (p1 NOT_EQUAL thePnt)
		{
			neighbors.push_back(p1);
		}
	}
	return std::move(neighbors);
}

void tnbLib::SectPx_PntTools::deAttach
(
	const std::shared_ptr<SectPx_TPnt>& thePnt,
	const std::shared_ptr<SectPx_Edge>& theEdge
)
{
	const auto removed = thePnt->RemoveFromEdges(theEdge->Index()).lock();
	if (removed NOT_EQUAL theEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected!" << endl
			<< "the removed items are not matched" << endl
			<< abort(FatalError);
	}
}

std::vector<std::shared_ptr<tnbLib::SectPx_Edge>>
tnbLib::SectPx_PntTools::deAttach
(
	const std::shared_ptr<SectPx_Pnt>& thePnt
)
{
	auto tPnt = std::dynamic_pointer_cast<SectPx_TPnt>(thePnt);
	Debug_Null_Pointer(tPnt);

	if (NOT tPnt->NbEdges())
	{
		return std::vector<std::shared_ptr<tnbLib::SectPx_Edge>>();
	}

	const auto& wedges = tPnt->Edges();

	std::vector<std::shared_ptr<SectPx_Edge>> edges;
	edges.reserve(wedges.size());
	for (const auto& x : wedges)
	{
		edges.push_back(x.second.lock());
	}

	if (edges.size() > 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of the profile!" << endl
			<< "there is a point with more than two edges around it" << endl
			<< "nb. of edges: " << (int)edges.size() << endl
			<< abort(FatalError);
	}

	for (const auto& x : edges)
	{
		deAttach(tPnt, x);
	}

	return std::move(edges);
}

std::shared_ptr<tnbLib::SectPx_Edge> 
tnbLib::SectPx_PntTools::CommonEdge
(
	const std::shared_ptr<SectPx_Pnt>& theP0,
	const std::shared_ptr<SectPx_Pnt>& theP1
)
{
	auto tp0 = std::dynamic_pointer_cast<SectPx_TPnt>(theP0);
	Debug_Null_Pointer(tp0);

	const auto& edges = tp0->Edges();
	for (const auto& x : edges)
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		if (edge->P0() IS_EQUAL theP1)
		{
			return std::move(edge);
		}

		if (edge->P1() IS_EQUAL theP1)
		{
			return std::move(edge);
		}
	}
	return nullptr;
}

void tnbLib::SectPx_PntTools::Replace
(
	const std::shared_ptr<SectPx_Pnt>& thePrior,
	const std::shared_ptr<SectPx_Edge>& theEdge,
	const std::shared_ptr<SectPx_Pnt>& theNew
)
{
	auto tPnt = std::dynamic_pointer_cast<SectPx_TPnt>(theNew);
	Debug_Null_Pointer(tPnt);
	Debug_If_Condition(tPnt->NbEdges());

	const auto id = theEdge->IndexOf(thePrior);

	if (id)
	{
		theEdge->SetP1(theNew);
	}
	else
	{
		theEdge->SetP0(theNew);
	}

	tPnt->Import(theEdge->Index(), theEdge);
}

void tnbLib::SectPx_PntTools::Replace
(
	const std::shared_ptr<SectPx_Pnt>& thePrior,
	const std::shared_ptr<SectPx_Pnt>& theNew
)
{
	Debug_If_Condition(std::dynamic_pointer_cast<SectPx_TPnt>(theNew)->NbEdges());

	const auto edges = deAttach(thePrior);

	for (const auto& x : edges)
	{
		Replace(thePrior, x, theNew);
	}
}