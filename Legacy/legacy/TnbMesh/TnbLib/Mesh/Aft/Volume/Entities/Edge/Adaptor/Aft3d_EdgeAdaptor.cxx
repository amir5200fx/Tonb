#include <Aft3d_EdgeAdaptor.hxx>

#include <Aft3d_Element.hxx>
#include <Aft3d_Facet.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::legLib::Aft3d_EdgeAdaptor::NbFacets() const
{
	return Standard_Integer(theFacets_.size());
}

Standard_Integer 
tnbLib::legLib::Aft3d_EdgeAdaptor::NbElements() const
{
	return Standard_Integer(theElements_.size());
}

Standard_Integer 
tnbLib::legLib::Aft3d_EdgeAdaptor::NbFronts() const
{
	return Standard_Integer(theFronts_.size());
}

Standard_Boolean 
tnbLib::legLib::Aft3d_EdgeAdaptor::IsContainsFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
) const
{
	Debug_Null_Pointer(theFacet);
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
tnbLib::legLib::Aft3d_EdgeAdaptor::IsContainsElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
) const
{
	Debug_Null_Pointer(theElement);
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
tnbLib::legLib::Aft3d_EdgeAdaptor::IsContainsFront
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
) const
{
	Debug_Null_Pointer(theFacet);
	auto iter = theFronts_.find(theFacet->Index());
	if (iter IS_EQUAL theFronts_.end())
	{
		return Standard_False;
	}
	else
	{
		return Standard_True;
	}
}

void tnbLib::legLib::Aft3d_EdgeAdaptor::RemoveFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto iter = theFacets_.find(theFacet->Index());
	if (iter IS_EQUAL theFronts_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "can not find the item!" << endl
			<< " - index: " << theFacet->Index() << endl
			<< abort(FatalError);
	}
	theFacets_.erase(iter);
}

void tnbLib::legLib::Aft3d_EdgeAdaptor::RemoveElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto iter = theElements_.find(theElement->Index());
	if (iter IS_EQUAL theElements_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "can not find the item!" << endl
			<< " - index: " << theElement->Index() << endl
			<< abort(FatalError);
	}
	theElements_.erase(iter);
}

void tnbLib::legLib::Aft3d_EdgeAdaptor::RemoveFront
(
	const std::shared_ptr<Aft3d_Facet>& theFront
)
{
	Debug_Null_Pointer(theFront);
	auto iter = theFronts_.find(theFront->Index());
	if (iter IS_EQUAL theFronts_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "can not find the item!" << endl
			<< " - index: " << theFront->Index() << endl
			<< abort(FatalError);
	}
	theFronts_.erase(iter);
}

void tnbLib::legLib::Aft3d_EdgeAdaptor::InsertFacet
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto paired = std::make_pair(theFacet->Index(), theFacet);
	auto insert = theFacets_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< "- index: " << theFacet->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::legLib::Aft3d_EdgeAdaptor::InsertElement
(
	const std::shared_ptr<Aft3d_Element>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto paired = std::make_pair(theElement->Index(), theElement);
	auto insert = theElements_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< "- index: " << theElement->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::legLib::Aft3d_EdgeAdaptor::InsertFront
(
	const std::shared_ptr<Aft3d_Facet>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto paired = std::make_pair(theFacet->Index(), theFacet);
	auto insert = theFronts_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< "- index: " << theFacet->Index() << endl
			<< abort(FatalError);
	}
}