#include <Voyage_Tools.hxx>

#include <MeshBase_Tools.hxx>
#include <Mesh_SetSourcesNode.hxx>
#include <GeoMesh2d_Background.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Voyage_Tools::SetSourcesToMesh
(
	const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources, 
	const Standard_Real theBase, 
	const Standard_Real theGrowthRate,
	GeoMesh2d_SingleBackground& theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto meshNodes = MeshBase_Tools::RetrieveNodes(mesh.Elements());
	auto& sources = theMesh.Sources();
	sources.resize(meshNodes.size());
	for (auto& x : sources)
	{
		x = theBase;
	}
	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;

		auto [n0, n1, n2] = current->Nodes();
		{
			auto id = Index_Of(n0->Index());
			auto ho = sources.at(id);
			if (x->H() > ho) sources.at(id) = x->H();
		}
		{
			auto id = Index_Of(n1->Index());
			auto ho = sources.at(id);
			if (x->H() > ho) sources.at(id) = x->H();
		}
		{
			auto id = Index_Of(n2->Index());
			auto ho = sources.at(id);
			if (x->H() > ho) sources.at(id) = x->H();
		}

		/*{
			auto nearest = n0;
			auto neighbors = MeshBase_Tools::RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::max(theBase, ho + theGrowthRate * dx);
				if (val > ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() > h) sources.at(id) = x->H();
			}
		}*/
		/*{
			auto nearest = n1;
			auto neighbors = MeshBase_Tools::RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::max(theBase, ho + theGrowthRate * dx);
				if (val > ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() > h) sources.at(id) = x->H();
			}
		}*/
		/*{
			auto nearest = n2;
			auto neighbors = MeshBase_Tools::RetrieveAdjacentNodes(nearest);

			auto ho = sources.at(Index_Of(nearest->Index()));
			for (const auto& ni : neighbors)
			{
				Debug_Null_Pointer(ni);
				auto id = Index_Of(ni->Index());

				auto dx = nearest->Coord().Distance(ni->Coord());
				auto val = std::max(theBase, ho + theGrowthRate * dx);
				if (val > ho) sources.at(id) = val;
			}
			{
				auto id = Index_Of(nearest->Index());

				auto h = sources.at(id);
				if (x->H() > h) sources.at(id) = x->H();
			}
		}*/
	}
}

void tnbLib::Voyage_Tools::SetInverseSourcesToMesh
(
	const std::vector<std::shared_ptr<Mesh_SetSourcesNode<Pnt2d, Standard_Real>>>& theSources,
	const Standard_Real theBase,
	const Standard_Real theGrowthRate,
	GeoMesh2d_SingleBackground& theMesh
)
{
	const auto& mesh = *theMesh.Mesh();
	if (mesh.Elements().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the element list of the background mesh is empty!" << endl
			<< abort(FatalError);
	}

	auto meshNodes = MeshBase_Tools::RetrieveNodes(mesh.Elements());
	auto& sources = theMesh.Sources();
	sources.resize(meshNodes.size());
	for (auto& x:sources)
	{
		x = theBase;
	}
	auto start = mesh.Elements().at(0);
	for (const auto& x : theSources)
	{
		const auto current = mesh.TriangleLocation(start, x->Coord());
		if (NOT current)
		{
			FatalErrorIn(FunctionSIG)
				<< "the point is outside of the mesh!" << endl
				<< " - domain's of the mesh: " << theMesh.BoundingBox() << endl
				<< " - coordinates of the point: " << x->Coord() << endl
				<< abort(FatalError);
		}
		start = current;

		auto [n0, n1, n2] = current->Nodes();
		{
			auto id = Index_Of(n0->Index());
			auto ho = sources.at(id);
			if (x->H() < ho) sources.at(id) = x->H();
		}
		{
			auto id = Index_Of(n1->Index());
			auto ho = sources.at(id);
			if (x->H() < ho) sources.at(id) = x->H();
		}
		{
			auto id = Index_Of(n2->Index());
			auto ho = sources.at(id);
			if (x->H() < ho) sources.at(id) = x->H();
		}
	}
}