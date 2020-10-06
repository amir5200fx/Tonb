#include <SectPx_PntTools.hxx>

#include <SectPx_Pnts.hxx>
#include <SectPx_Edge.hxx>
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