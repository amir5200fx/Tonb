#include <HydStatic_Modeler.hxx>

#include <NModel_Vertex.hxx>
#include <NModel_Edge.hxx>
#include <NModel_Surface.hxx>
#include <error.hxx>
#include <OSstream.hxx>

void tnbLib::HydStatic_Modeler_SrchEng::AddCorner
(
	const std::shared_ptr<corner>& theCorner
)
{
	const auto& domain = theVtxSrchEngine_.GeometryBoundingBox();
	if (NOT domain.IsInside(theCorner->Coord()))
	{
		ReArrangeEngine();
	}
	theVtxSrchEngine_.InsertToGeometry(theCorner);
}

void tnbLib::HydStatic_Modeler_SrchEng::RemoveCorner
(
	const std::shared_ptr<corner>& theCorner
)
{
	if (theCorner->NbVertices())
	{
		FatalErrorIn("void HydStatic_Modeler_SrchEng::RemoveCorner(const std::shared_ptr<corner>& theCorner)")
			<< "unable to remove: the corner is not empty!" << endl
			<< abort(FatalError);
	}
	theVtxSrchEngine_.RemoveFromGeometry(theCorner);
}

std::pair
<
	std::vector
	<
	std::pair<std::shared_ptr<tnbLib::NModel_Vertex>,
	std::shared_ptr<typename tnbLib::HydStatic_Modeler::corner>>>,
	Standard_Boolean
> 
tnbLib::HydStatic_Modeler::RetrievePairs
(
	const std::shared_ptr<NModel_Surface>& theSurface
) const
{
	std::vector<std::pair<std::shared_ptr<NModel_Vertex>, std::shared_ptr<corner>>> paires;
	auto vertices = theSurface->RetrieveVertices();

	size_t k = 0;
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);

		const auto& cr = SelectCorner(x->Coord());
		if (NOT IsNull(cr))
		{
			auto p = std::make_pair(x, cr);
			paires.push_back(std::move(p));

			++k;
		}
		else
		{
			auto p = std::make_pair(x, nullptr);
			paires.push_back(std::move(p));
		}
	}

	Standard_Boolean all = Standard_False;
	if (vertices.size() IS_EQUAL k) all = Standard_True;

	auto ent = std::make_pair(std::move(paires), all);
	return std::move(ent);
}

void tnbLib::HydStatic_Modeler::AddVertex
(
	const std::shared_ptr<NModel_Vertex>& theVertex,
	const Standard_Integer theSurfaceIndex
)
{
	std::ostringstream stream;
	stream << "vertex " <<
		std::to_string(theVertex->Index()) << " surface " <<
		std::to_string(theSurfaceIndex);

	auto name = word(stream.str());
	theVertex->Name() = std::move(name);

	const auto& crn = SelectCorner(theVertex->Coord());
	if (NOT IsNull(crn))
	{
		crn->Insert(theVertex);
	}
	else
	{
		auto crn = std::make_shared<corner>();
		Debug_Null_Pointer(crn);

		crn->Index() = RetrieveIndexForCorner();
		crn->Name() = "corner nb. " + std::to_string(crn->Index());

		crn->Insert(theVertex);

		AddCorner(crn);
	}
}

void tnbLib::HydStatic_Modeler::AddEdge
(
	const std::shared_ptr<NModel_Edge>& theEdge,
	const Standard_Integer theSurfaceIndex
)
{
	theEdge->Index() = RetrieveIndexForEdge();

	std::ostringstream stream;
	stream << "edge " <<
		std::to_string(theEdge->Index()) << " surface " <<
		std::to_string(theSurfaceIndex);

	auto name = word(stream.str());
	theEdge->Name() = std::move(name);

	InsertToEdges(theEdge);
}

void tnbLib::HydStatic_Modeler::AddSurface
(
	const std::shared_ptr<NModel_Surface>& theSurface
)
{
	theSurface->Index() = RetrieveIndexForSurface();
	
	std::ostringstream stream;
	stream << "surface nb. " << theSurface->Index();
	auto name = word(stream.str());

	theSurface->Name() = std::move(name);

	for (const auto& x : theSurface->RetrieveVertices())
	{
		AddVertex(x, theSurface->Index());
	}

	for (const auto& x : theSurface->RetrieveEdges())
	{
		AddEdge(x, theSurface->Index());
	}

	InsertToSurfaces(theSurface);
}