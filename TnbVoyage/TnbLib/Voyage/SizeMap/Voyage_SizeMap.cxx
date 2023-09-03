#include <Voyage_SizeMap.hxx>

#include <Voyage_MetricInfo.hxx>
#include <VoyageMesh_CorrectSizeMap.hxx>
#include <VoyageMesh_SizeMap.hxx>
#include <VoyageMesh_BaseSize.hxx>
#include <VoyageMesh_BaseSizeInfo.hxx>
#include <VoyageGeo_Path2.hxx>
#include <VoyageGeo_Earth.hxx>
#include <Mesh2d_MultiSizeMap.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <Geo_MetricPrcsrAnIso_Info.hxx>
#include <GeoMesh2d_Background.hxx>
#include <GeoSizeFun2d_Background.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Entity2d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

unsigned short tnbLib::Voyage_SizeMap::verbose(0);

void tnbLib::Voyage_SizeMap::Perform()
{
	if (NOT Path())
	{
		FatalErrorIn(FunctionSIG)
			<< "No path has been found." << endl
			<< abort(FatalError);
	}
	if (NOT GetInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "No info has been found." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	if (NOT path->Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "No earth has been assigned to the path." << endl
			<< abort(FatalError);
	}
	const auto& earth = path->Earth();
	auto metricsFun = earth->GetMetrics();
	auto uniSizeMap = 
		std::make_shared<GeoSizeFun2d_Uniform>
		(1.0, metricsFun->BoundingBox());
	auto metricPrcsrInfo = 
		std::make_shared<Geo_MetricPrcsrAnIso_Info>
		(GetInfo()->MetricInfo(), GetInfo()->NbSamples());
	auto metrics = 
		std::make_shared<Geo2d_MetricPrcsrAnIso>
		(uniSizeMap, metricsFun, metricPrcsrInfo);
	std::shared_ptr<std::vector<std::vector<Standard_Real>>> bHs;
	{// Create the base size map [8/28/2023 aamir]
		if (verbose)
		{
			Info << endl
				<< " - Calculating the base sizes..." << endl;
		}
		auto algInfo = std::make_shared<VoyageMesh_BaseSizeInfo>();
		auto alg = std::make_shared<VoyageMesh_BaseSize>(path->RetrieveOffsets(), metrics, algInfo);
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not perforemd.");

		bHs = alg->Hs();
		if (verbose)
		{
			Info << endl
				<< " - the base sizes are successfully computed." << endl;
		}
	}

	std::shared_ptr<GeoMesh2d_Background> unCorrSizeMap;
	{// Calculate the uncorrected size map [8/28/2023 aamir]
		if (verbose)
		{
			Info << endl
				<< " - Creating the base size map..." << endl;
		}
		auto alg = std::make_shared<VoyageMesh_SizeMap>();
		const auto baseSize = 1.0E-3;
		alg->SetBaseSize(baseSize);
		alg->SetHs(bHs);
		alg->SetPath(path);

		alg->Perform();
		unCorrSizeMap = alg->BackMesh();

		if (verbose)
		{
			Info << endl;
			Info << " The base size map is successfully computed." << endl;
		}
	}

	auto unCorrSizeFun =
		std::make_shared<GeoSizeFun2d_Background>
		(uniSizeMap->BoundingBox(), unCorrSizeMap);

	std::shared_ptr<GeoMesh2d_Background> starboard_corrSizeMap;
	{// Calculate the size map correction [8/29/2023 aamir]
		if (verbose > 1)
		{
			VoyageMesh_CorrectSizeMap::verbose = 1;
		}
		if (verbose)
		{
			Info << endl
				<< " - Creating a correction size map for starboard region." << endl;
		}
		auto alg = std::make_shared<VoyageMesh_CorrectSizeMap>();
		alg->SetPath(path);
		alg->SetDirection(VoyageMesh_CorrectSizeMap::PathDirect::Starboard);
		alg->SetSizeFunction(unCorrSizeFun);
		alg->SetInfo(GetInfo());

		alg->Perform();
		starboard_corrSizeMap = alg->BackMesh();

		if (verbose)
		{
			Info << endl;
			Info << " The Size map correction is successfully computed." << endl;
		}
	}

	std::shared_ptr<GeoMesh2d_Background> port_corrSizeMap;
	{// Calculate the size map correction [8/29/2023 aamir]
		if (verbose > 1)
		{
			VoyageMesh_CorrectSizeMap::verbose = 1;
		}
		if (verbose)
		{
			Info << endl
				<< " - Creating a correction size map for port region." << endl;
		}
		auto alg = std::make_shared<VoyageMesh_CorrectSizeMap>();
		alg->SetPath(path);
		alg->SetDirection(VoyageMesh_CorrectSizeMap::PathDirect::Port);
		alg->SetSizeFunction(unCorrSizeFun);
		alg->SetInfo(GetInfo());

		alg->Perform();
		port_corrSizeMap = alg->BackMesh();

		if (verbose)
		{
			Info << endl;
			Info << " The Size map correction is successfully computed." << endl;
		}
	}
	std::shared_ptr<Mesh2d_MultiSizeMap> multi_starboard, multi_port;
	{
		std::vector<std::shared_ptr<GeoMesh2d_Background>> meshes;
		meshes.push_back(unCorrSizeMap);
		meshes.push_back(starboard_corrSizeMap);
		multi_starboard = std::make_shared<Mesh2d_MultiSizeMap>(std::move(meshes));
		Debug_Null_Pointer(multi_starboard);
		multi_starboard->SetBoundingBox(metricsFun->BoundingBox());
	}
	{
		std::vector<std::shared_ptr<GeoMesh2d_Background>> meshes;
		meshes.push_back(unCorrSizeMap);
		meshes.push_back(port_corrSizeMap);
		multi_port = std::make_shared<Mesh2d_MultiSizeMap>(std::move(meshes));
		Debug_Null_Pointer(multi_port);
		multi_port->SetBoundingBox(metricsFun->BoundingBox());
	}
	theStarboard_ = 
		std::make_shared<GeoSizeFun2d_Background>
		(multi_starboard->BoundingBox(), multi_starboard);
	thePort_ =
		std::make_shared<GeoSizeFun2d_Background>
		(multi_port->BoundingBox(), multi_port);
	Change_IsDone() = Standard_True;
}