#include <Mesh2d_BoundarySizeMapTool.hxx>

#include <Cad_TModel.hxx>
#include <TModel_CornerManager.hxx>
#include <TModel_SegmentManager.hxx>
#include <TModel_FaceManager.hxx>
#include <Cad_BlockEntity.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::Mesh2d_BoundarySizeMapTool::ImportPatch(const word& patchName)
{
	if (NOT thePatches_.insert(patchName).second)
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to insert: the patch is already existed!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Mesh2d_BoundarySizeMapTool::RemovePatch(const word& patchName)
{
	auto iter = thePatches_.find(patchName);
	if (iter IS_EQUAL thePatches_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the patch is not in the set." << endl
			<< " - name: " << patchName << endl
			<< abort(FatalError);
	}
	thePatches_.erase(iter);
}