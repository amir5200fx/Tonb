#include <Aft3d_SolutionData.hxx>

const std::string tnbLib::legLib::Aft3d_SolutionData::extension = ".aft3dsoludata";

void tnbLib::legLib::Aft3d_SolutionData::SetSurface(std::shared_ptr<Entity3d_Triangulation> theSurface)
{
	theSurface_ = std::move(theSurface);
}

void tnbLib::legLib::Aft3d_SolutionData::SetSizeFun(std::shared_ptr<Aft3d_SizeFun> theSizeFun)
{
	theSizeFun_ = std::move(theSizeFun);
}

void tnbLib::legLib::Aft3d_SolutionData::SetMesh(std::shared_ptr<Entity3d_Tetrahedralization> theMesh)
{
	theMesh_ = std::move(theMesh);
}
