#include <MeshPost2d_LaplacianSmoothingSurface_AdjEdges.hxx>
#include <MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AdjEdges.hxx>
#include <MeshPost2d_QualityMapSurface_Vlrms2Ratio.hxx>
#include <MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio.hxx>
#include <MeshPost2d_LaplacianSmoothingSurface.hxx>
#include <MeshPost2d_LaplacianSmoothingSurfaceUniMetric.hxx>
#include <Aft_Tools.hxx>
#include <Aft2d_tModelSurface.hxx>
#include <Aft2d_tModelSurfaceUniMetric.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_tRegionPlaneSurfaceUniMetric.hxx>
#include <Aft2d_OptNodeSurface_Calculator.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Calculator.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric_RefineH.hxx>
#include <Aft2d_MetricPrcsrSurface_RefineH.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Standard.hxx>
#include <Aft2d_tBoundaryOfPlaneSurfaceUniMetric.hxx>
#include <Aft2d_tBoundaryOfPlaneSurface.hxx>
#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <MeshIO3d_BoundaryMesh.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Mesh_Curve_Info.hxx>
#include <GeoMetricFun2d_Plane.hxx>
#include <GeoMetricFun2d_Cylinder.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <Cad_tCommonSingularity.hxx>
#include <Cad_Volume.hxx>
#include <Cad_Solid.hxx>
#include <Cad_Tools.hxx>
#include <Cad_TModel.hxx>
#include <Cad_Shape.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Plane.hxx>
#include <TModel_ParaCurve.hxx>
#include <TModel_ParaWire.hxx>
#include <Geo_Tools.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <GeoSizeFun2d_Surface.hxx>
#include <Entity3d_SurfTriangulation.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NelderMeadInfo.hxx>
#include <Global_Tools.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Face.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Precision.hxx>

namespace tnbLib
{
	static unsigned short verbose = 0;

	static std::shared_ptr<Cad_Volume> myModel;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;
	static std::shared_ptr<Mesh_Curve_Info> myGlobalCurveInfo;
	static std::map<int, std::shared_ptr<Mesh_Curve_Info>> myLocalCurveInfo;

	static auto myCoeff = 0.3;
	static auto myDelta = 0.2;

	static auto myMinDistFactor = 0.4;

	static double myTol = 1.0E-5;

	// max. level of the subdividing a triangle algorithm [6/14/2023 Payvand]
	static int myMaxSubTriLev = 3;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setMaxSubTriLev(int n)
	{
		myMaxSubTriLev = n;
		if (verbose)
		{
			Info << endl
				<< " - the maximum level of the incremental calculation of the optimum point: "
				<< myMaxSubTriLev << endl;
		}
	}

	static double myMergTol = 1.0E-6;

	void setMergTol(double x)
	{
		myMergTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the boundary merging tolerance is set to: "
				<< myMergTol << endl;
		}
	}

	static auto myMesh = 
		std::make_shared<std::map<int, std::shared_ptr<Entity3d_SurfTriangulation>>>();

	static auto loadTag = false;
	static auto exeTag = false;


	static auto myIntegInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
	static auto mySizeCorrIterInfo = std::make_shared<Aft_SizeCorr_IterativeInfo>();
	static auto myLaplacianSmoothInfo = std::make_shared<MeshPost_LaplacianSmoothing_Info>();
	static auto myMetricPrcsrInfo = std::make_shared<Aft_MetricPrcsrAnIso_Info>();
	static auto myNelderMeadInfo = std::make_shared<NumAlg_NelderMeadInfo>();

	RunTimeConfigs(IntegInfo);
	SetRunTimeConfigs(IntegInfo)
	{
		myIntegInfo->SetMaxNbIterations(200);
		myIntegInfo->SetNbInitIterations(4);
		myIntegInfo->SetTolerance(1.0E-4);
	}

	void setMaxNbIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo, int n)
	{
		theInfo->SetMaxNbIterations(n);
		if (verbose)
		{
			Info << endl
				<< " - the maximum no. of iterations is set to: "
				<< theInfo->MaxNbIterations() << endl;
		}
	}

	void setNbInitIterations(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo, int n)
	{
		theInfo->SetNbInitIterations(n);
		if (verbose)
		{
			Info << endl
				<< " - the no. of initial iterations is set to: "
				<< theInfo->NbInitIterations() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the adaptive integration is set to: "
				<< theInfo->Tolerance() << endl;
		}
	}

	RunTimeConfigs(SizeCorrIterInfo);
	SetRunTimeConfigs(SizeCorrIterInfo)
	{
		mySizeCorrIterInfo->SetIgnoreNonConvergency(true);
		mySizeCorrIterInfo->SetMaxNbIters(100);
		mySizeCorrIterInfo->SetTolerance(1.0E-5);
		mySizeCorrIterInfo->SetUnderRelaxation(0.85);
	}

	void setMaxNbIters(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo, int n)
	{
		theInfo->SetMaxNbIters(n);
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of iterations of the size corr. is set to: "
				<< theInfo->MaxNbIters() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the size corr. is set to: "
				<< theInfo->Tolerance() << endl;
		}
	}

	void setUr(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo, double x)
	{
		theInfo->SetUnderRelaxation(x);
		if (verbose)
		{
			Info << endl
				<< " - the under relaxation of the size corr. is set to: "
				<< theInfo->UnderRelaxation() << endl;
		}
	}

	RunTimeConfigs(NelderMeadInfo);
	SetRunTimeConfigs(NelderMeadInfo)
	{
		myNelderMeadInfo->SetMaxNbIterations(50);
		myNelderMeadInfo->SetTolerance(1.0E-3);
	}

	void setNbIters(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo, int n)
	{
		theInfo->SetMaxNbIterations(n);
		if (verbose)
		{
			Info << endl
				<< " - the max. no. of iterations of the Nelder-Mead is set to: "
				<< theInfo->MaxNbIterations() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the Nelder-Mead is set to: "
				<< theInfo->Tolerance() << endl;
		}
	}

	RunTimeConfigs(MetricPrcsrInfo);
	SetRunTimeConfigs(MetricPrcsrInfo)
	{
		myMetricPrcsrInfo->SetNbIters(5);
		myMetricPrcsrInfo->SetNbSamples(3);
		myMetricPrcsrInfo->SetTolerance(0.001);
	}

	void setNbIters(const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo, int n)
	{
		theInfo->SetNbIters(n);
		if (verbose)
		{
			Info << endl
				<< " - the maximum no. of iterations of the metric processor is set to: "
				<< theInfo->NbIters() << endl;
		}
	}

	void setNbSamples(const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo, int n)
	{
		theInfo->SetNbSamples(n);
		if (verbose)
		{
			Info << endl
				<< " - the no. of samples of the metric processor is set to: "
				<< theInfo->NbSamples() << endl;
		}
	}

	void setTolerance(const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo, double x)
	{
		theInfo->SetTolerance(x);
		if (verbose)
		{
			Info << endl
				<< " - the tolerance of the metric processor is set to: "
				<< theInfo->Tolerance() << endl;
		}
	}

	//******************************** IO FUNCTIONS ************************************//

	void loadModel()
	{
		static const auto current_directory = "model";
		myModel = 
			file::LoadSingleFile<std::shared_ptr<Cad_Volume>>
			(current_directory, Cad_Volume::extension, verbose);
		if (NOT myModel)
		{
			FatalErrorIn(FunctionSIG)
				<< "no model has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadSizeFun()
	{
		static const auto current_directory = "sizeMap";
		mySizeFun = 
			file::LoadSingleFile<std::shared_ptr<Geo3d_SizeFunction>>
			(current_directory, Geo3d_SizeFunction::extension, verbose);
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< "no size function has been loaded." << endl
				<< abort(FatalError);
		}
	}

	void loadCurveInfo()
	{
		static const auto current_directory = "curveInfo";
		myGlobalCurveInfo = file::LoadSingleFile<std::shared_ptr<Mesh_Curve_Info>>(current_directory, Mesh_Curve_Info::extension, verbose);
		if (NOT myGlobalCurveInfo)
		{
			FatalErrorIn(FunctionSIG)
				<< "no curve info. has been loaded." << endl
				<< abort(FatalError);
		}

		// get the current path [6/11/2023 Payvand]
		const auto current_path = boost::filesystem::current_path();

		// change the current path [6/11/2023 Payvand]
		boost::filesystem::current_path(current_path.string() + R"(\)" + current_directory);
		{
			const auto subCurrentPath = boost::filesystem::current_path();
			// load the subs [6/11/2023 Payvand]
			for
				(
					boost::filesystem::directory_iterator iter(subCurrentPath);
					iter != boost::filesystem::directory_iterator();
					iter++
					)
			{
				auto fname = iter->path().string();
				if (Global_Tools::IsNumber(fname))
				{
					auto curveNb = std::stoi(fname);
					// Change the current path [12/2/2021 Amir]
					boost::filesystem::current_path(subCurrentPath.string() + R"(\)" + fname);

					try
					{
						auto name = file::GetSingleFile(boost::filesystem::current_path(), Mesh_Curve_Info::extension).string();
						auto curveInfo = file::LoadFile<std::shared_ptr<Mesh_Curve_Info>>(name + Mesh_Curve_Info::extension, verbose);
						if (NOT curveInfo)
						{
							FatalErrorIn(FunctionSIG)
								<< " the info curve file is null!" << endl
								<< abort(FatalError);
						}

						auto paired = std::make_pair(curveNb, std::move(curveInfo));
						auto insert = myLocalCurveInfo.insert(std::move(paired));
						if (NOT insert.second)
						{
							FatalErrorIn(FunctionSIG)
								<< "unable to insert the curve info into the map!" << endl
								<< " Duplicate data maybe?!" << endl
								<< abort(FatalError);
						}

						if (verbose)
						{
							Info << " - the curve info, " << curveNb << ", has been loaded, successfully!" << endl;
						}
					}
					catch (const error& x)
					{
						Info << " - Couldn't load the curve info: " << endl;
						Info << x.message() << endl;
					}
				}
			}
		}
		boost::filesystem::current_path(current_path);
	}

	void loadFiles()
	{
		loadModel();

		loadSizeFun();

		loadCurveInfo();

		loadTag = true;

		if (verbose)
		{
			Info << endl
				<< " - the files have been loaded." << endl;
		}
	}


	//******************************* MESHING FUNCTIONS ****************************************//

	auto createMetricCalculator()
	{
		/*std::shared_ptr<Cad_MetricCalculator> alg =
			std::make_shared<cadLib::MetricCalculator_Std>();
		return std::move(alg);*/
		if (mySizeFun)
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_SizeFun>([](const Pnt3d& pt) {return mySizeFun->Value(pt); });
			return std::move(alg);
		}
		else
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_Std>();
			return std::move(alg);
		}
	}

	auto meshSurface
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurface>& theMetricPrcsr, 
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		auto alg = std::make_shared<Aft2d_tModelSurface>();
		alg->LoadMetricMap(theMetricPrcsr);
		alg->LoadBoundaryMetricMap(theMetricPrcsr);

		alg->LoadBoundaryEdges(theBoundaries);
		alg->LoadNodeCalculator(theCalculator);

		alg->SetMinDistFactor(myMinDistFactor);

		{// timer scope [6/13/2023 Payvand]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			alg->Perform();
		}

		const auto& elemMap = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements.push_back(x.second);
		}
		auto nodesRef = Aft_Tools::RetrieveNodes(elements);
		auto nodes = std::make_shared<std::vector<std::shared_ptr<Aft2d_NodeSurface>>>(std::move(nodesRef));

		auto avgFun = std::make_shared<MeshPost2d_LaplacianSmoothingSurface_AdjEdges>();
		avgFun->SetMetrics(theMetricPrcsr);

		auto qualityFun = std::make_shared<MeshPost2d_QualityMapSurface_Vlrms2Ratio>();
		qualityFun->SetMetrics(theMetricPrcsr);

		auto smoothingAlg = std::make_shared<MeshPost2d_LaplacianSmoothingSurface>();
		smoothingAlg->SetAvgFun(avgFun);
		smoothingAlg->SetQualityFun(qualityFun);
		smoothingAlg->SetInfo(myLaplacianSmoothInfo);
		smoothingAlg->SetNodes(nodes);

		smoothingAlg->Perform();

		Aft_Tools::CalcCood3d(nodesRef, *theMetricPrcsr->Geometry());

		return std::move(elements);
	}

	auto meshSurface
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theMetricPrcsr,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theCalculator,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		auto alg = std::make_shared<Aft2d_tModelSurfaceUniMetric>();
		alg->LoadMetricMap(theMetricPrcsr);
		alg->LoadBoundaryMetricMap(theMetricPrcsr);

		alg->LoadBoundaryEdges(theBoundaries);
		alg->LoadNodeCalculator(theCalculator);

		alg->SetMinDistFactor(myMinDistFactor);
		{// timer scope [3/12/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			alg->Perform();
		}

		const auto& elemMap = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements.push_back(x.second);
		}
		auto nodesRef = Aft_Tools::RetrieveNodes(elements);
		auto nodes = std::make_shared<std::vector<std::shared_ptr<Aft2d_NodeSurface>>>(std::move(nodesRef));

		auto avgFun = std::make_shared<MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AdjEdges>();
		avgFun->SetMetrics(theMetricPrcsr);

		auto qualityFun = std::make_shared<MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio>();
		qualityFun->SetMetrics(theMetricPrcsr);

		auto smoothingAlg = std::make_shared<MeshPost2d_LaplacianSmoothingSurfaceUniMetric>();
		smoothingAlg->SetAvgFun(avgFun);
		smoothingAlg->SetQualityFun(qualityFun);
		smoothingAlg->SetInfo(myLaplacianSmoothInfo);
		smoothingAlg->SetNodes(nodes);

		smoothingAlg->Perform();

		Aft_Tools::CalcCood3d(nodesRef, *theMetricPrcsr->Geometry());

		return std::move(elements);
	}

	auto meshSurface
	(
		const std::shared_ptr<TModel_Surface>& theSurface,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theUniMetricCalculator,
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator,
		const std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info>& theBndInfo
	)
	{
		if (NOT theSurface->GeomSurface())
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT theSurface->GeomSurface()->Geometry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry has been found!" << endl
				<< abort(FatalError);
		}
		auto geometry = theSurface->GeomSurface()->Geometry();

		auto wire = TModel_Tools::GetOuterParaWire(theSurface);
		auto box = TModel_Tools::CalcBoundingBox(*wire);

		auto d = box.Diameter();
		auto tol = myTol * d;

		auto metricCalculator = createMetricCalculator();

		std::vector<std::vector<std::shared_ptr<Aft2d_ElementSurface>>> meshes;
		std::vector<std::vector<std::shared_ptr<Aft2d_EdgeSurface>>> bMeshes;

		if (TModel_Tools::IsPlane(theSurface) OR TModel_Tools::IsCylinder(theSurface))
		{
			auto pln = TModel_Tools::GetParaPlane(theSurface, Precision::PConfusion());
			auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, mySizeFun, box);

			std::shared_ptr<GeoMetricFun2d_Uniform> metricFun;
			if (TModel_Tools::IsPlane(theSurface))
			{
				auto gPlane = Handle(Geom_Plane)::DownCast(geometry);
				if (NOT gPlane)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "the geometry is not plane!" << endl
						<< abort(FatalError);
				}
				metricFun = std::make_shared<GeoMetricFun2d_Plane>(gPlane, box);
			}
			else
			{
				auto gPlane = Handle(Geom_CylindricalSurface)::DownCast(geometry);
				if (NOT gPlane)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< "the geometry is not plane!" << endl
						<< abort(FatalError);
				}
				metricFun = std::make_shared<GeoMetricFun2d_Cylinder>(gPlane, box);
			}

			//Aft2d_MetricPrcsrSurfaceUniMetric xx(sizeFun, metricFun, theInfo);
			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurfaceUniMetric_RefineH>();
			metricPrcsr->SetCoeff(myCoeff);
			metricPrcsr->SetDelta(myDelta);
			metricPrcsr->SetSizeFun(sizeFun);
			metricPrcsr->SetMetricFun(metricFun);
			metricPrcsr->SetInfo(myMetricPrcsrInfo);
			metricPrcsr->SetDimSize(box.Diameter());
			metricPrcsr->SetGeometry(geometry);

			metricPrcsr->SetNodeCalculator(theUniMetricCalculator);

			if 
				(
					auto optNodeAlg = 
					std::dynamic_pointer_cast<Aft2d_OptNodeSurfaceUniMetric_Standard>
					(theUniMetricCalculator)
					)
			{
				optNodeAlg->SetMetricMap(metricPrcsr);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid optimum point calculator has been detected!" << endl
					<< abort(FatalError);
			}

			auto plnRegion = Aft2d_tRegionPlaneSurfaceUniMetric::MakePlane(pln);
			//std::cout << "nb curves: " << plnRegion->Outer()->NbCurves() << std::endl;
			Aft2d_tBoundaryOfPlaneSurfaceUniMetric::verbose = verbose;
			auto bnd = 
				std::make_shared<Aft2d_tBoundaryOfPlaneSurfaceUniMetric>(theBndInfo);
			bnd->LoadMetricProcessor(metricPrcsr);
			bnd->LoadPlane(plnRegion);

			theBndInfo->SetMergeTolerance(tol);  // added to adapt the merging tolerance [5/16/2022 Amir]
			bnd->Perform();

			if (NOT bnd->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			const auto& boundaries = bnd->Boundaries();

			Aft_Tools::Connect(boundaries);

			auto ibMesh = Aft_Tools::UpCast(boundaries);
			auto elements = meshSurface(metricPrcsr, theUniMetricCalculator, ibMesh);
			meshes.push_back(std::move(elements));
			bMeshes.push_back(std::move(ibMesh));

			auto t = std::make_pair(std::move(meshes), std::move(bMeshes));
			return std::move(t);
		}
		else
		{
			auto pln = TModel_Tools::GetParaPlane(theSurface, Precision::PConfusion());

			auto plnRegion = Aft2d_tRegionPlaneSurface::MakePlane(pln);

			auto singAlg = std::make_shared<Cad_tCommonSingularity>();
			singAlg->SetPlane(plnRegion);
			singAlg->SetSurface(theSurface);
			singAlg->SetTolerance(1.0E-6);

			singAlg->Perform();

			plnRegion = singAlg->Modified();

			auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, mySizeFun, box);

			auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(geometry, box);
			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurface_RefineH>();
			metricPrcsr->SetCoeff(myCoeff);
			metricPrcsr->SetDelta(myDelta);
			metricPrcsr->SetSizeFun(sizeFun);
			metricPrcsr->SetMetricFun(metricFun);
			metricPrcsr->SetInfo(myMetricPrcsrInfo);
			metricPrcsr->SetDimSize(box.Diameter());
			metricPrcsr->SetGeometry(geometry);

			metricPrcsr->SetNodeCalculator(theCalculator);

			if (auto optNodeAlg = std::dynamic_pointer_cast<Aft2d_OptNodeSurface_Altr>(theCalculator))
			{
				optNodeAlg->SetMetricMap(metricPrcsr);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid optimum point calculator has been detected!" << endl
					<< abort(FatalError);
			}

			auto bnd = std::make_shared<Aft2d_tBoundaryOfPlaneSurface>(theBndInfo);
			bnd->LoadMetricProcessor(metricPrcsr);
			bnd->LoadPlane(plnRegion);

			theBndInfo->SetMergeTolerance(tol);  // added to adapt the merging tolerance [5/16/2022 Amir]

			bnd->Perform();
			if (NOT bnd->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			const auto& boundaries = bnd->Boundaries();

			Aft_Tools::Connect(boundaries);

			auto ibMesh = Aft_Tools::UpCast(boundaries);
			auto elements = meshSurface(metricPrcsr, theCalculator, ibMesh);

			meshes.push_back(std::move(elements));
			bMeshes.push_back(std::move(ibMesh));

			auto t = std::make_pair(std::move(meshes), std::move(bMeshes));
			return std::move(t);
		}
	}

	int ns = 0;
	OFstream myFile("tris.plt");

	void mesh
	(
		const Cad_Solid& theSolid,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theUniMetricCalculator,
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator,
		const std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info>& theBndInfo
	)
	{
		std::vector<std::shared_ptr<TModel_Surface>> triSurfaces;
		size_t nbSurfaces = 0;
		for (const auto& x : theSolid.RetrieveFaces())
		{
			Debug_Null_Pointer(x);
			if (Cad_Tools::HasTriangulation(x->Face()))
			{
				triSurfaces.push_back(x);
				x->SetIndex(++nbSurfaces);
			}
		}

		if (triSurfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no triangulated surface has been found." << endl
				<< abort(FatalError);
		}
		Entity3d_SurfTriangulation tris_all;
		for (const auto& x : triSurfaces)
		{
			Debug_Null_Pointer(x);
			if (verbose)
			{
				Info << endl
					<< "- meshing surface, " << x->Index() << endl;
			}

			const TopoDS_Face& face = x->Face();
			try
			{
				auto [plnMesh, bMesh] = 
					meshSurface
					(x, theUniMetricCalculator, theCalculator, theBndInfo);
				if (plnMesh.size() IS_EQUAL 1)
				{
					auto tris = Aft_Tools::RetrieveTriangleMesh(plnMesh.at(0));
					auto tris3d = Cad_Tools::SurfTriangulation(*x->GeomSurface()->Geometry(), *tris);
					tris_all.Add(*tris3d);
					if (face.Orientation() IS_EQUAL TopAbs_Orientation::TopAbs_REVERSED)
					{
						Geo_Tools::Reverse(*tris3d);
					}

					if (verbose)
					{
						Info << " - no. of elements: " << tris3d->NbConnectivity() << endl;
					}
					Global_Tools::Insert(/*x->Index()*/++ns, tris3d, *myMesh);
				}
				else
				{
					Entity2d_Triangulation mesh2d;
					for (const auto& m : plnMesh)
					{
						auto tris = Aft_Tools::RetrieveTriangleMesh(m);

						mesh2d.Add(*tris);
					}
					auto tris3d = Cad_Tools::SurfTriangulation(*x->GeomSurface()->Geometry(), mesh2d);
					if (face.Orientation() IS_EQUAL TopAbs_Orientation::TopAbs_REVERSED)
					{
						Geo_Tools::Reverse(*tris3d);
					}

					if (verbose)
					{
						Info << " - no. of elements: " << tris3d->NbConnectivity() << endl;
					}
					Global_Tools::Insert(/*x->Index()*/++ns, tris3d, *myMesh);
				}
			}
			catch (const error& er)
			{
				std::cout << er.message() << std::endl;
			}

			if (verbose)
			{
				Info << " - surface, " << x->Index() << ", is discretized, successfully!" << endl;
			}
			
		}
		tris_all.ExportToPlt(myFile);
	}

	void execute()
	{
		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the files haven't been loaded." << endl
				<< abort(FatalError);
		}

		// override the integration info of the metric processor with the global integration info. [6/14/2023 Payvand]
		myMetricPrcsrInfo->OverrideIntegInfo(myIntegInfo);

		auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_SubTri>();
		anIsoOptNode_altrAlg->SetSizeCorrInfo(mySizeCorrIterInfo);
		anIsoOptNode_altrAlg->SetNealderMeadInfo(myNelderMeadInfo);
		anIsoOptNode_altrAlg->SetMaxLev(myMaxSubTriLev);

		// the Opt. node calculator for a general surface [6/14/2023 Payvand]
		auto anIsoOptNode = 
			std::make_shared<Aft2d_OptNodeSurface_Altr>
			(anIsoOptNode_altrAlg, mySizeCorrIterInfo);

		// the Opt. node calculator for an uniform metric surface (e.g., plane, cylinder) [6/14/2023 Payvand]
		auto anIsoOptNodeUniMetric = 
			std::make_shared<Aft2d_OptNodeSurfaceUniMetric_Standard>();

		auto bndInfo = std::make_shared<Aft2d_BoundaryOfPlaneAnIso_Info>();
		bndInfo->SetOverrideInfo(Standard_False);
		bndInfo->OverrideGlobalCurve(myGlobalCurveInfo);
		bndInfo->SetMergeTolerance(myMergTol);
		bndInfo->OverrideGlobalMetricPrcsr(myMetricPrcsrInfo);

		auto solids = myModel->Volumes();
		if (verbose)
		{
			Info << endl
				<< " - Nb. of detected volumes: "
				<< solids.size() << endl << endl;
		}
		size_t k = 0;
		for (const auto& x : solids)
		{
			if (verbose)
			{
				Info << endl
					<< " - Meshing the boundaries of the volume, " << ++k << ":" << endl << endl;
			}
			mesh
			(
				*x, 
				anIsoOptNodeUniMetric, 
				anIsoOptNode, 
				bndInfo
			);
			if (verbose)
			{
				Info << endl
					<< "   Meshing of the boundaries has been completed." << endl << endl;
			}
		}
		exeTag = true;
		if (verbose)
		{
			Info << endl
				<< " - the application is performed, successfully!" << endl;
		}
	}
}

#ifdef DebugInfo
#undef DebugInfo
#endif // DebugInfo

#include <chaiscript/chaiscript.hpp>

namespace tnbLib
{

	typedef std::shared_ptr<chaiscript::Module> module_t;

	void setFuns(const module_t& mod)
	{
		// io functions 
		//mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		//mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFiles(); }), "loadFiles");

		// settings 
		mod->add(chaiscript::fun([](unsigned short i)-> void {setVerbose(i); }), "setVerbose");

		// operators 
		mod->add(chaiscript::fun([]()-> void {execute(); }), "execute");
	}

	std::string getString(char* argv)
	{
		std::string argument(argv);
		return std::move(argument);
	}

	Standard_Boolean IsEqualCommand(char* argv, const std::string& command)
	{
		auto argument = getString(argv);
		return argument IS_EQUAL command;
	}
}

using namespace tnbLib;

int main(int argc, char* argv[])
{
	FatalError.throwExceptions();
	FatalConvError.throwExceptions();

	if (argc <= 1)
	{
		Info << " - No command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}

	if (argc IS_EQUAL 2)
	{
		if (IsEqualCommand(argv[1], "--help"))
		{
			Info << " This application is aimed to mesh the boundaries of a volume." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFiles()" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - execute()" << endl
				<< endl;
			return 0;
		}
		else if (IsEqualCommand(argv[1], "--run"))
		{
			chaiscript::ChaiScript chai;

			auto mod = std::make_shared<chaiscript::Module>();

			setFuns(mod);

			chai.add(mod);

			try
			{
				fileName myFileName(file::GetSystemFile("tnbMeshVolumeBndAft"));

				chai.eval_file(myFileName);
				return 0;
			}
			catch (const chaiscript::exception::eval_error& x)
			{
				Info << x.pretty_print() << endl;
			}
			catch (const error& x)
			{
				Info << x.message() << endl;
			}
			catch (const std::exception& x)
			{
				Info << x.what() << endl;
			}
		}
		else
		{
			Info << " - No valid command is entered" << endl
				<< " - For more information use '--help' command" << endl;
			FatalError.exit();
		}
	}
	else
	{
		Info << " - No valid command is entered" << endl
			<< " - For more information use '--help' command" << endl;
		FatalError.exit();
	}
	return 1;
}