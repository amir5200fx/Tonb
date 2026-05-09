#include <TModel_VertexAdaptor.hxx>

#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::TModel_Edge>> 
tnbLib::TModel_VertexAdaptor::RetrieveEdges() const
{
	std::vector<std::shared_ptr<TModel_Edge>> edges;
	RetrieveEdgesTo(edges);
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::TModel_Surface>> 
tnbLib::TModel_VertexAdaptor::RetrieveSurfaces() const
{
	std::vector<std::shared_ptr<TModel_Surface>> surfaces;
	RetrieveSurfacesTo(surfaces);
	return std::move(surfaces);
}

void tnbLib::TModel_VertexAdaptor::RetrieveEdgesTo
(
	std::vector<std::shared_ptr<TModel_Edge>>& theEdges
) const
{
	for (const auto& x : Edges())
	{
		auto e = x.second.lock();
		Debug_Null_Pointer(e);
		theEdges.push_back(std::move(e));
	}
}

void tnbLib::TModel_VertexAdaptor::RetrieveSurfacesTo
(
	std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
) const
{
	for (const auto& x : Faces())
	{
		auto s = x.second.lock();
		Debug_Null_Pointer(s);
		theSurfaces.push_back(std::move(s));
	}
}

void tnbLib::TModel_VertexAdaptor::ImportToEdges
(
	const Standard_Integer theIndex, 
	const std::weak_ptr<TModel_Edge>& theEdge
)
{
	auto paired = std::make_pair(theIndex, theEdge);
	auto insert = theEdges_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected while inserting the edge!" << endl
			<< "- index: " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::TModel_VertexAdaptor::ImportToSurfaces
(
	const Standard_Integer theIndex,
	const std::weak_ptr<TModel_Surface>& theFace
)
{
	auto paired = std::make_pair(theIndex, theFace);
	auto insert = theFaces_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected while inserting the surface!" << endl
			<< "- index: " << theIndex << endl
			<< abort(FatalError);
	}
}

void tnbLib::TModel_VertexAdaptor::ImportToSurfaces_dup
(
	const Standard_Integer theIndex,
	const std::weak_ptr<TModel_Surface>& theFace
)
{
	auto Iter = theEdges_.find(theIndex);
	if (Iter IS_EQUAL theEdges_.end())
	{
		theFaces_.insert(std::make_pair(theIndex, theFace));
	}
}

void tnbLib::TModel_VertexAdaptor::RemoveFromEdges
(
	const Standard_Integer theIndex
)
{
	auto Iter = theEdges_.find(theIndex);
	if (Iter IS_EQUAL theEdges_.end())
	{
		FatalErrorIn("void RemoveFromEdges(const Standard_Integer theIndex)")
			<< "The edge is not in the list" << endl
			<< abort(FatalError);
	}

	theEdges_.erase(Iter);
}

void tnbLib::TModel_VertexAdaptor::RemoveFromFaces
(
	const Standard_Integer theIndex
)
{
	auto Iter = theFaces_.find(theIndex);
	if (Iter IS_EQUAL theFaces_.end())
	{
		FatalErrorIn("void RemoveFromFaces(const Standard_Integer theIndex)")
			<< "The edge is not in the list" << endl
			<< abort(FatalError);
	}

	theFaces_.erase(Iter);
}