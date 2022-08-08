#include <BoundarySizeMap3d_SegmentTool.hxx>

#include <Mesh3d_Element.hxx>
#include <MeshBase_Tools.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Paired.hxx>
#include <Cad_TModel.hxx>
#include <GeoMesh_Background_Info.hxx>
#include <GeoMesh3d_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <Geo3d_BalPrTree.hxx>
#include <Geo_ItemMerge.hxx>
#include <Geo_BoxTools.hxx>
#include <Entity3d_Box.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Entity3d_Polygon.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const Standard_Integer tnbLib::BoundarySizeMap3d_SegmentTool::DEFAULT_MAX_NB_CORR_ITERS(3);

std::vector<std::shared_ptr<tnbLib::TModel_Paired>> 
tnbLib::BoundarySizeMap3d_SegmentTool::RetrieveSegments() const
{
	std::vector<std::shared_ptr<TModel_Paired>> items;
	RetrieveSegmentsTo(items);

	return std::move(items);
}

void tnbLib::BoundarySizeMap3d_SegmentTool::RetrieveSegmentsTo
(
	std::vector<std::shared_ptr<TModel_Paired>>& theItems
) const
{
	if (NOT Model())
	{
		FatalErrorIn(FunctionSIG)
			<< "no model has been found." << endl
			<< abort(FatalError);
	}

	if (NOT Model()->Segments())
	{
		FatalErrorIn(FunctionSIG)
			<< "no segment manager has been found." << endl
			<< abort(FatalError);
	}
	const auto& manager = *Model()->Segments();
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