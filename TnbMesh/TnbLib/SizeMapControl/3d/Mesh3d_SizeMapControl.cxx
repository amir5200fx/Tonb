#include <Mesh3d_SizeMapControl.hxx>

#include <Mesh3d_SizeMapTool.hxx>
#include <Mesh3d_UnionSizeMap.hxx>
#include <Mesh_SizeMapControl_Info.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Mesh3d_SizeMapControl::Perform()
{
	if (NOT this->SizeMapInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no size map control info has been found." << endl
			<< abort(FatalError);
	}
	if (Maps().empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the map list is empty." << endl
			<< abort(FatalError);
	}
	if (NOT Domain())
	{
		FatalErrorIn(FunctionSIG)
			<< "no domain has been set!" << endl
			<< abort(FatalError);
	}

	if (verbose)
	{
		Mesh_SizeMapToolBaseNonTemplate::verbose = verbose;
	}

	for (const auto& x : Maps())
	{
		Debug_Null_Pointer(x.second);
		const auto& mapTool = x.second;

		if(NOT mapTool->IsDone())
			mapTool->Perform();
	}

	if (Maps().size() IS_EQUAL 1)
	{
		if (verbose)
		{
			Info << endl
				<< " one size map has been detected, no unifying algorithm is needed." << endl;
		}
		theBackground_ = Maps().at(0)->BackgroundMesh();
	}
	else
	{
		if (verbose)
		{
			Info << endl
				<< " unifying the maps..." << endl
				<< " - nb. of the maps: " << Maps().size() << endl;
		}
		Global_Timer myTimer;
		myTimer.SetInfo(Global_TimerInfo_ms);

		auto alg = std::make_shared<Mesh3d_UnionSizeMap>();
		Debug_Null_Pointer(alg);

		const auto& myInfo = SizeMapInfo();
		alg->SetMaxUnbalancing(myInfo->MaxUnbalancing());
		alg->SetTolerance(myInfo->Tolerance());
		alg->SetDomain(Domain());
		alg->SetSmoothingInfo(myInfo->HvCorrInfo());

		std::set<std::shared_ptr<Cad_TModel>> compact;
		for (const auto& x : Maps())
		{
			Debug_Null_Pointer(x.second);
			const auto& g = x.second->Model();
			if (NOT compact.insert(g).second)
			{
				// duplicate data has been detected. [7/21/2022 Amir]
				//- do nothing!
			}
		}

		std::vector<std::shared_ptr<Cad_TModel>> models;
		models.reserve(compact.size());
		for (auto& x : compact)
		{
			models.push_back(std::move(x));
		}

		std::vector<std::shared_ptr<GeoMesh3d_Background>> backs;
		backs.reserve(Maps().size());
		for (const auto& x : Maps())
		{
			Debug_Null_Pointer(x.second);
			backs.push_back(x.second->BackgroundMesh());
		}

		alg->SetModels(std::move(models));
		alg->SetBackgrounds(backs);

		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");

		theBackground_ = alg->UnifiedMap();
	}

	if (verbose)
	{
		Info << endl
			<< " - all of the maps in the size map control have been unified, in " << global_time_duration << " ms." << endl;
	}

	Change_IsDone() = Standard_True;
}