#include <Cad3d_TModelManager.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::Cad3d_TModelManager::NbCorners() const
{
	Debug_Null_Pointer(Corners());
	return (Standard_Integer)Corners()->Size();
}

Standard_Integer 
tnbLib::Cad3d_TModelManager::NbSegments() const
{
	Debug_Null_Pointer(Segments());
	return (Standard_Integer)Segments()->Size();
}

Standard_Integer 
tnbLib::Cad3d_TModelManager::NbFaces() const
{
	Debug_Null_Pointer(Faces());
	return (Standard_Integer)Faces()->Size();
}

std::vector<std::shared_ptr<tnbLib::TModel_Vertex>> 
tnbLib::Cad3d_TModelManager::RetrieveCorners() const
{
	std::vector<std::shared_ptr<TModel_Vertex>> corners;
	RetrieveCornersTo(corners);

	return std::move(corners);
}

std::vector<std::shared_ptr<tnbLib::TModel_Paired>> 
tnbLib::Cad3d_TModelManager::RetrieveSegments() const
{
	std::vector<std::shared_ptr<TModel_Paired>> segments;
	RetrieveSegmentsTo(segments);

	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::TModel_Surface>> 
tnbLib::Cad3d_TModelManager::RetrieveFaces() const
{
	std::vector<std::shared_ptr<TModel_Surface>> faces;
	RetrieveFacesTo(faces);

	return std::move(faces);
}

void tnbLib::Cad3d_TModelManager::RetrieveCornersTo
(
	std::vector<std::shared_ptr<TModel_Vertex>>& theVertices
) const
{
	auto entities = Corners()->RetrieveEntities();

	theVertices.reserve(entities.size());
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		theVertices.push_back(x);
	}
}

void tnbLib::Cad3d_TModelManager::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<TModel_Paired>>& theEdges
) const
{
	auto entities = Segments()->RetrieveEntities();

	theEdges.reserve(entities.size());
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		theEdges.push_back(x);
	}
}

void tnbLib::Cad3d_TModelManager::RetrieveFacesTo
(
	std::vector<std::shared_ptr<TModel_Surface>>& theSurfaces
) const
{
	auto entities = Faces()->RetrieveEntities();

	theSurfaces.reserve(entities.size());
	for (const auto& x : entities)
	{
		Debug_Null_Pointer(x);
		theSurfaces.push_back(x);
	}
}