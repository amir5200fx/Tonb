#include <Mesh2d_SizeMapControl.hxx>

#include <Mesh2d_SizeMapTool.hxx>
#include <Mesh2d_UnionSizeMap.hxx>
#include <Mesh2d_MultiSizeMap.hxx>
#include <Mesh_SizeMapControl_Info.hxx>
#include <GeoMesh2d_Background.hxx>
#include <Global_Timer.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <OFstream.hxx>

template<>
void tnbLib::Mesh2d_SizeMapControl::Perform()
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
		//if(NOT mapTool->IsDone())
		mapTool->Perform();
	}

	if (Maps().size() IS_EQUAL 1)
	{
		/*if (verbose)
		{
			Info << endl
				<< " one size map has been detected, no unifying algorithm is needed." << endl;
		}*/
		theBackground_ = Maps().begin()->second->BackgroundMesh();
		Maps().begin()->second->ClearBackMesh();
		/*OFstream myFile("sizeMapControl.plt");
		theBackground_->ExportToPlt(myFile);*/
	}
	else
	{
		std::vector<std::shared_ptr<GeoMesh2d_Background>> meshes;
		meshes.reserve(Maps().size());
		for (const auto& x : Maps())
		{
			Debug_Null_Pointer(x.second);
			meshes.push_back(x.second->BackgroundMesh());
			x.second->ClearBackMesh();
		}

		auto multiBackMesh = std::make_shared<Mesh2d_MultiSizeMap>(std::move(meshes));
		Debug_Null_Pointer(multiBackMesh);

		multiBackMesh->SetBoundingBox(*Domain());

		theBackground_ = std::move(multiBackMesh);
	}

	Change_IsDone() = Standard_True;
}