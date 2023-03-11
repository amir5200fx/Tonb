#include <Aft3d_Volume.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Integer 
tnbLib::legLib::Aft3d_Volume::Meshing()
{
	if (base::FrontHandler.Fronts().IsPriorityEmpty())
	{
		FatalErrorIn(FunctionSIG)
			<< "empty priority list detected!" << endl
			<< abort(FatalError);
	}

	base::FrontHandler.SetCurrentLev(0);
	base::FrontHandler.SetMaxLevel(base::Mesh.NbNodes());

	base::CycleInfo.SetCycleMode(cycleMode::generation);

	while (NOT base::FrontHandler.Fronts().IsPriorityEmpty())
	{
		MeshOneLevel();

		if (base::IsSameLevelSupplied())
		{
			base::CycleInfo.SetCycleMode(cycleMode::generation);
			continue;
		}

		if (base::IsCavityRemoverSupplied())
		{
			base::CycleInfo.SetCycleMode(cycleMode::repair);
		}

		base::FrontHandler.SetCurrentLev(base::FrontHandler.LevelNumber() + 1);

		if (base::FrontHandler.LevelNumber() >= theALLOWED_MAX_LEVEL_)
		{
			return 1;
		}

		if (base::IsNextLevelSupplied())
		{
			base::CycleInfo.SetCycleMode(cycleMode::generation);
		}
	}
	return 0;
}

void tnbLib::legLib::Aft3d_Volume::MeshOneLevel()
{
	base::ModifyLocalFront(DEFAULT_LOCALFRONT_FACTOR);

	while (base::GetCurrent())
	{
		std::vector<std::shared_ptr<Aft3d_Node>>
			candidates,
			localNodes;
		std::vector<std::shared_ptr<Aft3d_Facet>>
			effectives,
			locals;
		if (base::IsBelongToFront())
		{
			continue;
		}

		// remove the current from the front [3/1/2023 Payvand]
		base::RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		base::CalcElementSize();

		// Calculate optimum coordinate of new point
		base::CalcOptimumCoord();

		base::CalcLocalFrontRadius();

		// Set depth of searching radius
		base::SetDepthSearching();

		base::RetrieveLocalFrontNodes(localNodes, candidates);

		base::RetrieveLocalFrontEntities(localNodes, locals);

		base::RetrieveEffectiveFronts(locals, effectives);

		base::SortNodes(candidates);

		if (base::IsNewNodeValid(effectives))
		{
			base::AddOptimumNodeTo(candidates);
		}

		FindValidNode(candidates, effectives);

		Update();
	}
}