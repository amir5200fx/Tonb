#include <Cad3d_NModelManager.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer
tnbLib::Cad3d_NModelManager::NbCorners() const
{
	Debug_Null_Pointer(Corners());
	return (Standard_Integer)Corners()->Size();
}

Standard_Integer
tnbLib::Cad3d_NModelManager::NbSegments() const
{
	Debug_Null_Pointer(Segments());
	return (Standard_Integer)Segments()->Size();
}

Standard_Integer
tnbLib::Cad3d_NModelManager::NbFaces() const
{
	Debug_Null_Pointer(Faces());
	return (Standard_Integer)Faces()->Size();
}

std::vector<std::shared_ptr<tnbLib::NModel_Vertex>>
tnbLib::Cad3d_NModelManager::RetrieveCorners() const
{
	std::vector<std::shared_ptr<NModel_Vertex>> corners;
	RetrieveCornersTo(corners);

	return std::move(corners);
}

std::vector<std::shared_ptr<tnbLib::NModel_Segment>>
tnbLib::Cad3d_NModelManager::RetrieveSegments() const
{
	std::vector<std::shared_ptr<NModel_Segment>> segments;
	RetrieveSegmentsTo(segments);

	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::NModel_Surface>>
tnbLib::Cad3d_NModelManager::RetrieveFaces() const
{
	std::vector<std::shared_ptr<NModel_Surface>> faces;
	RetrieveFacesTo(faces);

	return std::move(faces);
}

void tnbLib::Cad3d_NModelManager::RetrieveCornersTo
(
	std::vector<std::shared_ptr<NModel_Vertex>>& theVertices
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

void tnbLib::Cad3d_NModelManager::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<NModel_Segment>>& theEdges
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

void tnbLib::Cad3d_NModelManager::RetrieveFacesTo
(
	std::vector<std::shared_ptr<NModel_Surface>>& theSurfaces
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