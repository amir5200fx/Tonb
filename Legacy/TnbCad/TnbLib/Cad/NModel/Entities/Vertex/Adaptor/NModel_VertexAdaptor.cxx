#include <NModel_VertexAdaptor.hxx>

#include <Global_Macros.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::NModel_VertexAdaptor::ImportToSurfaces_dup
(
	const Standard_Integer theIndex,
	const std::weak_ptr<NModel_Surface>& theFace
)
{
	auto Iter = theEdges_.find(theIndex);
	if (Iter IS_EQUAL theEdges_.end())
	{
		theFaces_.insert(std::make_pair(theIndex, theFace));
	}
}

void tnbLib::NModel_VertexAdaptor::RemoveFromEdges
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

void tnbLib::NModel_VertexAdaptor::RemoveFromFaces
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