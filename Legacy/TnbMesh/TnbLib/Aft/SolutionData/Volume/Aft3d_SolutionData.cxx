#include <Aft3d_SolutionData.hxx>

#include <Aft3d_SolutionData_SurfVol.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>


tnbLib::Aft3d_SolutionData::Aft3d_SolutionData(std::shared_ptr<Aft3d_SolutionData_SurfVol>& theSolu)
	: theBndSolu_(std::move(theSolu))
{
	// empty body
}

void tnbLib::Aft3d_SolutionData::SetBndSolu(std::shared_ptr<Aft3d_SolutionData_SurfVol> theSolu)
{
	theBndSolu_ = std::move(theSolu);
}

void tnbLib::Aft3d_SolutionData::SetMesh(std::shared_ptr<Entity3d_Tetrahedralization> theMesh)
{
	theMesh_ = std::move(theMesh);
}

std::shared_ptr<tnbLib::Aft3d_SolutionData::volume> tnbLib::Aft3d_SolutionData::RetrieveVolume(
	const Aft3d_SolutionData& solu)
{
	const auto& bnd = solu.BndSolu();
	if (NOT bnd)
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< " No boundary mesh has been found." << "\n"
			<< abort(FatalError);
	}
	return bnd->Geometry();
}

std::shared_ptr<tnbLib::Aft3d_SolutionData::sizeFun> tnbLib::Aft3d_SolutionData::RetrieveSizeFun(
	const Aft3d_SolutionData& solu)
{
	const auto& bnd = solu.BndSolu();
	if (NOT bnd)
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< " No boundary mesh has been found." << "\n"
			<< abort(FatalError);
	}
	return bnd->SizeFunction();
}

std::shared_ptr<tnbLib::Aft3d_SolutionData::surfMesh> tnbLib::Aft3d_SolutionData::RetrieveSurfMesh(
	const Aft3d_SolutionData& solu)
{
	const auto& bnd = solu.BndSolu();
	if (NOT bnd)
	{
		FatalErrorIn(FunctionSIG) << "\n"
			<< " No boundary mesh has been found." << "\n"
			<< abort(FatalError);
	}
	return bnd->Merged();
}
