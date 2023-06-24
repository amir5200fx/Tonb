#include <BoundarySizeMap2d_SegmentTool.hxx>

#include <Cad2d_Plane.hxx>
#include <Cad2d_Plane_Manager.hxx>
#include <Cad_EntityManager.hxx>
#include <Pln_Edge.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::BoundarySizeMap2d_SegmentTool::DEFAULT_MAX_NB_CORR_ITERS(3);

std::vector<std::shared_ptr<tnbLib::Pln_Edge>>
tnbLib::BoundarySizeMap2d_SegmentTool::RetrieveSegments() const
{
	std::vector<std::shared_ptr<Pln_Edge>> items;
	RetrieveSegmentsTo(items);

	return std::move(items);
}

void tnbLib::BoundarySizeMap2d_SegmentTool::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<Pln_Edge>>& theItems
) const
{
	if (NOT this->Plane())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been found." << endl
			<< abort(FatalError);
	}

	if (NOT this->Plane()->Segments())
	{
		FatalErrorIn(FunctionSIG)
			<< "no segment manager has been found." << endl
			<< abort(FatalError);
	}
	const auto& manager = *this->Plane()->Segments();
	for (const auto& x : Patches())
	{
		if (NOT manager.HasBlock(x))
		{
			FatalErrorIn(FunctionSIG)
				<< "the segment manager doesn't have such a block." << endl
				<< " - block name: " << x << endl
				<< abort(FatalError);
		}
		auto block = manager.SelectBlock(x);
		const auto& entities = block->second;
		for (const auto& e : entities->Entities())
		{
			Debug_Null_Pointer(e.second);
			theItems.push_back(e.second);
		}
	}
}