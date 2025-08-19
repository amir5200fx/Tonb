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
	if (NOT theSizeDistb_)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No size map distb. control has been found." << endl
			<< abort(FatalError);
	}
	const auto& path = Path();
	if (NOT path->Earth())
	{
		FatalErrorIn(FunctionSIG)
			<< "No earth has been assigned to the path." << endl
			<< abort(FatalError);
	}
	/*
	 * =============================
	 * Creating the Metric Processor
	 */
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
	/*
	 * The Metric Processor has been created.
	 * =====================================
	 */
	/*
	 * ===========================
	 * Creating the Base Size Map.
	 */
	std::shared_ptr<std::vector<std::vector<Standard_Real>>> bHs;
	{// Create the base size map [8/28/2023 aamir]
		if (verbose)
		{
			Info << endl
				<< " - Calculating the base sizes..." << endl;
		}
		//auto algInfo = std::make_shared<VoyageMesh_BaseSizeInfo>();
		auto algInfo = theSizeDistb_;
		const auto alg = 
			std::make_shared<VoyageMesh_BaseSize>
		(path->RetrieveOffsets(), metrics, algInfo);
		Debug_Null_Pointer(alg);
		// Perform the application
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not perforemd.");
		bHs = alg->Hs();
		if (verbose)
		{
			Info << endl
				<< " - the base sizes are successfully computed." << endl;
		}
	}
	/*
	 * The base sizes are computed. Now, creating the main size map:
	 * =============================================================
	 */
	/*
	 * =====================================
	 * Creating the Uncorrected Size function
	 */
	std::shared_ptr<GeoMesh2d_Background> unCorrSizeMap;
	constexpr auto baseSize = 1.0E-4; // I defined a really small size for the base.
	{// Calculate the uncorrected size map [8/28/2023 aamir]
		if (verbose)
		{
			Info << endl
				<< " - Creating the base size map..." << endl;
		}
		const auto alg = std::make_shared<VoyageMesh_SizeMap>();
		Debug_Null_Pointer(alg);
		alg->SetBaseSize(baseSize);
		alg->SetHs(bHs);
		alg->SetPath(path);
		// Perform the application
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
		unCorrSizeMap = alg->BackMesh();
		//OFstream myFile("sizeMap.plt");
		//unCorrSizeMap->ExportToPlt(myFile);
		if (verbose)
		{
			Info << endl;
			Info << " The base size map is successfully computed." << endl;
		}
	}
	const auto unCorrSizeFun =
		std::make_shared<GeoSizeFun2d_Background>
		(uniSizeMap->BoundingBox(), unCorrSizeMap);
	/*
	 * The Main size map is created.
	 * =============================
	 */
	/*
	 * ===========================================================================
	 * Now, we need two correcting size functions: one for starboard side and
	 * the other of the port side.
	 *
	 * For merging the two size functions I use min operator. Due to this, for
	 * correction size map we cannot use the same approach as the main size map.
	 * Because the correction size map only activates when is needed. So I use
	 * inverse value of the base size of the main size map as the base size of the
	 * correction size map.
	 */
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
		const auto alg = std::make_shared<VoyageMesh_CorrectSizeMap>();
		Debug_Null_Pointer(alg);
		alg->SetBaseSize(1.0 / baseSize); // I use the inverse value for the base size
		alg->SetPath(path);
		alg->SetDirection(voyageLib::PathDirect::Starboard);
		alg->SetSizeFunction(unCorrSizeFun);
		alg->SetInfo(GetInfo());
		// Perform the application
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
		starboard_corrSizeMap = alg->BackMesh();
		//OFstream myFile("starboard.plt");
		//starboard_corrSizeMap->ExportToPlt(myFile);
		if (verbose)
		{
			Info << endl;
			Info << " The Size map correction is successfully computed." << endl;
		}
	}
	/*
	 * The starboard size map correction has been created. Now,
	 * creating the port size map correction:
	 */
	//std::cout << "port size map..." << std::endl;
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
		Debug_Null_Pointer(alg);
		alg->SetBaseSize(1.0 / baseSize); // I use the inverse value for the base size
		alg->SetPath(path);
		alg->SetDirection(voyageLib::PathDirect::Port);
		alg->SetSizeFunction(unCorrSizeFun);
		alg->SetInfo(GetInfo());
		// Perform the application
		alg->Perform();
		Debug_If_Condition_Message(NOT alg->IsDone(), "the application is not performed.");
		port_corrSizeMap = alg->BackMesh();
		//OFstream myFile("port.plt");
		//port_corrSizeMap->ExportToPlt(myFile);
		if (verbose)
		{
			Info << endl;
			Info << " The Size map correction is successfully computed." << endl;
		}
	}
	//PAUSE;
	/*
	 * All of the three size maps are computed.
	 */
	//std::cout << "starboard size map..." << std::endl;
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
