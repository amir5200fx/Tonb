#include <GeoTop2d_VertexAdaptor.hxx>

#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::GeoTop2d_VertexAdaptor::NbEdges() const
{
	return Standard_Integer(theEdges_.size());
}

Standard_Integer 
tnbLib::GeoTop2d_VertexAdaptor::NbElements() const
{
	return Standard_Integer(theElements_.size());
}

std::weak_ptr<tnbLib::GeoTop2d_Edge> 
tnbLib::GeoTop2d_VertexAdaptor::RemoveEdge(const Standard_Integer theIndex)
{
	auto iter = theEdges_.find(theIndex);
	if (iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "cannot find the object!" << endl
			<< abort(FatalError);
	}
	auto item = iter->second;
	theEdges_.erase(iter);
	return std::move(item);
}

std::weak_ptr<tnbLib::GeoTop2d_Element> 
tnbLib::GeoTop2d_VertexAdaptor::RemoveElement(const Standard_Integer theIndex)
{
	auto iter = theElements_.find(theIndex);
	if (iter IS_EQUAL theElements_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "cannot find the object!" << endl
			<< abort(FatalError);
	}
	auto item = iter->second;
	theElements_.erase(iter);
	return std::move(item);
}

void tnbLib::GeoTop2d_VertexAdaptor::InsertToEdges
(
	const Standard_Integer theIndex,
	const std::shared_ptr<GeoTop2d_Edge>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::GeoTop2d_VertexAdaptor::InsertToElements
(
	const Standard_Integer theIndex,
	const std::shared_ptr<GeoTop2d_Element>& theElement
)
{
	auto paired = std::make_pair(theIndex, theElement);
	auto insert = theElements_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data!" << endl
			<< " - index: " << theIndex << endl
			<< abort(FatalError);
	}
}