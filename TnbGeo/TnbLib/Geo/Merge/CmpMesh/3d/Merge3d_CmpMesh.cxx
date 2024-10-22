#include <Merge3d_CmpMesh.hxx>

void tnbLib::Merge_StaticData<tnbLib::Entity3d_CmpMesh, tnbLib::Merge_PntAlg_Mean>::Import(const Entity3d_CmpMesh& input)
{
	theMerged_ = std::make_shared<Entity3d_CmpMesh>();
	auto& mesh = *theMerged_;
	mesh.CoordsRef() = input.Coords();
	mesh.IndicesRef() = input.Indices();
}

void tnbLib::Merge_StaticData<tnbLib::Entity3d_CmpMesh, tnbLib::Merge_PntAlg_Mean>::Perform()
{
	if (NOT theMerged_)
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< "No mesh has been imported.\n"
			<< abort(FatalError);
	}
	auto& mesh = *theMerged_;
	// Merge points
	theMergePnt_.SetCoords(mesh.Coords());
	theMergePnt_.Perform();

	mesh.CoordsRef() = theMergePnt_.CompactPoints();
	auto indices = theMergePnt_.CompactIndices();
	for (const auto& i: mesh.Connectivity())
	{
		i->Update(indices);
	}
	Change_IsDone() = Standard_True;
}
