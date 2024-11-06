#include <Aft3d_NodeAdaptor.hxx>

#include <Aft3d_Element.hxx>
#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::legLib::Aft3d_NodeAdaptor::NbEdges() const
{
	return Standard_Integer(theEdges_.size());
}

Standard_Integer 
tnbLib::legLib::Aft3d_NodeAdaptor::NbFacets() const
{
	return Standard_Integer(theFacets_.size());
}

Standard_Integer 
tnbLib::legLib::Aft3d_NodeAdaptor::NbElements() const
{
	return Standard_Integer(theElements_.size());
}

Standard_Integer 
tnbLib::legLib::Aft3d_NodeAdaptor::NbFrontEdges() const
{
	return Standard_Integer(theFrontEdges_.size());
}

Standard_Integer 
tnbLib::legLib::Aft3d_NodeAdaptor::NbFrontFacets() const
{
	return Standard_Integer(theFrontFacets_.size());
}

Standard_Boolean 
tnbLib::legLib::Aft3d_NodeAdaptor::IsContainsElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
) const
{
	auto iter = theElements_.find(theElement->Index());
	if (iter IS_EQUAL theElements_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

Standard_Boolean 
tnbLib::legLib::Aft3d_NodeAdaptor::IsContainsFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
) const
{
	auto iter = theFacets_.find(theFacet->Index());
	if (iter IS_EQUAL theFacets_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

Standard_Boolean 
tnbLib::legLib::Aft3d_NodeAdaptor::IsContainsEdge
(
	const std::shared_ptr<Aft3d_Facet>& theEdge
) const
{
	auto iter = theEdges_.find(theEdge->Index());
	if (iter IS_EQUAL theEdges_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

Standard_Boolean
tnbLib::legLib::Aft3d_NodeAdaptor::IsContainsFrontFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
) const
{
	auto iter = theFrontFacets_.find(theFacet->Index());
	if (iter IS_EQUAL theFrontFacets_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

Standard_Boolean 
tnbLib::legLib::Aft3d_NodeAdaptor::IsContainsFrontEdge
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
) const
{
	auto iter = theFrontEdges_.find(theEdge->Index());
	if (iter IS_EQUAL theFrontEdges_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

void tnbLib::legLib::Aft3d_NodeAdaptor::RemoveEdge
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto iter = theEdges_.find(theEdge->Index());
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " can not find the item!" << endl
			<< abort(FatalError);
	}
	theEdges_.erase(iter);
}

void tnbLib::legLib::Aft3d_NodeAdaptor::RemoveFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto iter = theFacets_.find(theFacet->Index());
	if (iter IS_EQUAL theFacets_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " can not find the item!" << endl
			<< abort(FatalError);
	}
	theFacets_.erase(iter);
}

void tnbLib::legLib::Aft3d_NodeAdaptor::RemoveElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto iter = theElements_.find(theElement->Index());
	if (iter IS_EQUAL theElements_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " can not find the item!" << endl
			<< abort(FatalError);
	}
	theElements_.erase(iter);
}

void tnbLib::legLib::Aft3d_NodeAdaptor::RemoveFrontEdge
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto iter = theFrontEdges_.find(theEdge->Index());
	if (iter IS_EQUAL theFrontEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " can not find the item!" << endl
			<< abort(FatalError);
	}
	theFrontEdges_.erase(iter);
}

void tnbLib::legLib::Aft3d_NodeAdaptor::RemoveFrontFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	const auto iter = theFrontFacets_.find(theFacet->Index());
	if (iter IS_EQUAL theFrontFacets_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " can not find the item!" << endl
			<< abort(FatalError);
	}
	theFrontFacets_.erase(iter);
}

void tnbLib::legLib::Aft3d_NodeAdaptor::InsertEdge
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	const auto insert = theEdges_.insert({theEdge->Index(), theEdge});
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data!" << endl
			<< " - index: " << theEdge->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::legLib::Aft3d_NodeAdaptor::InsertFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	const auto insert = theFacets_.insert({theFacet->Index(), theFacet});
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data!" << endl
			<< " - index: " << theFacet->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::legLib::Aft3d_NodeAdaptor::InsertElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	const auto insert = theElements_.insert({theElement->Index(), theElement});
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data!" << endl
			<< " - index: " << theElement->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::legLib::Aft3d_NodeAdaptor::InsertFrontEdge
(
	const std::shared_ptr<Aft3d_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	const auto insert = theFrontEdges_.insert({theEdge->Index(), theEdge});
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data!" << endl
			<< " - index: " << theEdge->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::legLib::Aft3d_NodeAdaptor::InsertFrontFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	const auto insert = theFrontFacets_.insert({theFacet->Index(), theFacet});
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data!" << endl
			<< " - index: " << theFacet->Index() << endl
			<< abort(FatalError);
	}
}