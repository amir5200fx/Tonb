#include <Voyage_Mesh3.hxx>

#include <VoyageMesh_Element.hxx>
#include <Geo_AdTree.hxx>

void tnbLib::Voyage_Mesh3::MeshOneLevel()
{
	while (GetFrontEntity())
	{
		std::vector<std::shared_ptr<Aft2d_NodeSurface>>
			CandidateNodes,
			LocalNodes;

		std::vector<std::shared_ptr<Aft2d_EdgeSurface>>
			Effectives,
			Local;

		if (NOT IsBelongToFront())
			continue;

		// Remove the Current from front
		RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		CalcElementSize();

		// Calculate optimum coordinate of new point
		CalcOptimumCoord();

		CalcLocalFrontRadius();

		// Set depth of searching radius
		SetDepthSearching();

		RetrieveLocalFrontNodes(LocalNodes, CandidateNodes);

		RetrieveLocalFrontEntities(LocalNodes, Local);

		RetrieveEffectiveFronts(Local, Effectives);

		SortNodes(CandidateNodes);

		if (IsNewPointCandidate(Effectives))
		{
			AddOptimumNodeTo(CandidateNodes);
		}

		FindValidNode(CandidateNodes, Effectives);

		Update();
	}
}

void tnbLib::Voyage_Mesh3::Perform()
{
	
}