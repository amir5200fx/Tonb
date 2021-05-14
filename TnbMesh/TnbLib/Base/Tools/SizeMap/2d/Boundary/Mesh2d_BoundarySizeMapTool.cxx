#include <Mesh2d_BoundarySizeMapTool.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad_EntityManager.hxx>

void tnbLib::Mesh2d_BoundarySizeMapTool::ImportCornerPatch(const word & patchName)
{
	theCornerPatches_.push_back(patchName);
}

void tnbLib::Mesh2d_BoundarySizeMapTool::ImportSegmentPatch(const word & patchName)
{
	theSegmentPatches_.push_back(patchName);
}

void tnbLib::Mesh2d_BoundarySizeMapTool::RetrieveCornersTo
(
	std::vector<std::shared_ptr<Pln_Vertex>>& corners
) const
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< " no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Plane()->NbCorners())
	{
		FatalErrorIn(FunctionSIG)
			<< " Invalid plane has been detected!" << endl
			<< abort(FatalError);
	}

	std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>> compact;
	const auto& allCorners = Plane()->Corners();
	for (const auto& x : theCornerPatches_)
	{
		auto iter = allCorners->SelectBlock(x);
		const auto& patch = iter->second;

		for (const auto& p : patch->Entities())
		{
			const auto& ent = p.second;
			auto paired = std::make_pair(ent->Index(), ent);
			auto insert = compact.insert(std::move(paired));
			if (NOT insert.second)
			{
				//- duplicate data: do nothing!
			}
		}
	}

	corners.reserve(compact.size());
	for (const auto& x : compact)
	{
		corners.push_back(std::move(x.second));
	}
}

void tnbLib::Mesh2d_BoundarySizeMapTool::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<Pln_Edge>>& edges
) const
{
	if (NOT Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< " no plane has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Plane()->NbSegments())
	{
		FatalErrorIn(FunctionSIG)
			<< " Invalid plane has been detected!" << endl
			<< abort(FatalError);
	}

	std::map<Standard_Integer, std::shared_ptr<Pln_Edge>> compact;
	const auto& allSegments = Plane()->Segments();
	for (const auto& x : theSegmentPatches_)
	{
		auto iter = allSegments->SelectBlock(x);
		const auto& patch = iter->second;

		for (const auto& p : patch->Entities())
		{
			const auto& ent = p.second;
			auto paired = std::make_pair(ent->Index(), ent);
			auto insert = compact.insert(std::move(paired));
			if (NOT insert.second)
			{
				//- duplicate data: do nothing!
			}
		}
	}

	edges.reserve(compact.size());
	for (const auto& x : compact)
	{
		edges.push_back(std::move(x.second));
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> 
tnbLib::Mesh2d_BoundarySizeMapTool::RetrieveCorners() const
{
	std::vector<std::shared_ptr<Pln_Vertex>> corners;
	RetrieveCornersTo(corners);
	return std::move(corners);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Mesh2d_BoundarySizeMapTool::RetrieveSegments() const
{
	std::vector<std::shared_ptr<Pln_Edge>> segments;
	RetrieveSegmentsTo(segments);
	return std::move(segments);
}