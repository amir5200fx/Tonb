#include <MeshPost2d_LaplacianSmoothingSurface.hxx>
#include <MeshPost2d_LaplacianSmoothingSurfaceUniMetric.hxx>
#include <MeshPost_LaplacianSmoothing_Info.hxx>
#include <MeshPost2d_LaplacianSmoothingSurface_AdjEdges.hxx>
#include <MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AdjEdges.hxx>
#include <MeshPost2d_QualityMapSurface_Vlrms2Ratio.hxx>
#include <MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft_Tools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft3d_SolutionData_SurfVol.hxx>
#include <Aft2d_tModelSurface.hxx>
#include <Aft2d_tModelSurfaceUniMetric.hxx>
#include <Aft2d_tRegionPlaneSurfaceUniMetric.hxx>
#include <Aft2d_tBoundaryOfPlaneSurfaceUniMetric.hxx>
#include <Aft2d_tBoundaryOfPlaneSurface.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric_RefineH.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Standard.hxx>
#include <Aft2d_MetricPrcsrSurface_RefineH.hxx>
#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>
#include <Mesh2d_CurveAnIso.hxx>
#include <Mesh2d_CurveUniMetric.hxx>
#include <Cad_Tools.hxx>
#include <Cad_MultiVolume.hxx>
#include <Cad_Solid.hxx>
#include <Cad_GeomSurface.hxx>
#include <Cad_tCommonSingularity.hxx>
#include <Cad_MetricCalculator.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <Cad_ApprxMetricCriterion_MinMax.hxx>
#include <TModel_Tools.hxx>
#include <TModel_Surface.hxx>
#include <TModel_Plane.hxx>
#include <GeoSizeFun2d_Surface.hxx>
#include <GeoMetricFun2d_Plane.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo2d_SamplePoints_4Pts.hxx>
#include <Geo2d_SamplePoints_5Pts.hxx>
#include <Geo2d_SamplePoints_8Pts.hxx>
#include <Geo2d_SamplePoints_9Pts.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Box.hxx>
#include <Geo2d_SamplePoints.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NelderMeadInfo.hxx>
#include <Global_File.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>

namespace tnbLib
{
	static const auto extension = Aft3d_SolutionData_SurfVol::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	// Loading objects
	static std::shared_ptr<Mesh_Curve_Info> my_curve_info;
	static std::shared_ptr<Aft_MetricPrcsrAnIso_Info> my_metric_info;
	static std::shared_ptr<Geo3d_SizeFunction> my_size_fun;

	static double my_tol = 1.0e-5;
	static double my_coeff = 0.3;
	static double my_delta = 0.2;

	static auto my_smaple_type = Geo2d_SamplePoints::Type::five_points;
	static auto my_metric_approx_tol = Cad_ApprxMetricCriterion::DEFAULT_TOLERANCE;

	static std::shared_ptr<Aft3d_SolutionData_SurfVol> my_solu_data;
	static std::string my_file_name;
	//.
	// Settings
	//.

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		my_tol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << my_tol << endl;
		}
	}
	//==========================================================================================
	// Smoothing settings
	//==========================================================================================
	static auto my_laplacian_smooth_info = std::make_shared<MeshPost_LaplacianSmoothing_Info>();
	RunTimeConfigs(Smoothing);
	static const int SMOOTH_DEFAULT_NB_ITERS = 4;
	static const double SMOOTH_DEFAULT_UR = 0.85;
	static const bool SMOOTH_DEFAULT_APPLY = true;
	SetRunTimeConfigs(Smoothing)
	{
		my_laplacian_smooth_info->SetNbLevels(SMOOTH_DEFAULT_NB_ITERS);
		my_laplacian_smooth_info->SetUnderRelaxation(SMOOTH_DEFAULT_UR);
	}
	struct SmoothConfig
	{
		std::shared_ptr<MeshPost_LaplacianSmoothing_Info> config;
		bool apply = SMOOTH_DEFAULT_APPLY;
	};
	static const auto my_smoothing_config = std::make_shared<SmoothConfig>(SmoothConfig{ my_laplacian_smooth_info, SMOOTH_DEFAULT_APPLY });
	auto get_smooth_config()
	{
		return *my_smoothing_config;
	}
	//
	void set_nb_iters(const SmoothConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - SmoothConfig.NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbLevels(n);
	}

	void set_ur(const SmoothConfig& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - SmoothConfig.UR is set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}

	void set_apply(const SmoothConfig& config, bool apply)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - SmoothConfig.APPLY is set to: " << (apply ? "TRUE" : "FALSE") << "\n";
		}
	}

	static double my_degen_crit = 1.0e-6;
	// ========================================================
	// the edges mesh configs
	// ========================================================
	static double EDGE_MESH_CONFIG_MERG_TOL = 1.0E-6;
	struct EdgeMeshConfig
	{
		std::shared_ptr<Mesh_Curve_Info> config;
		double tol = EDGE_MESH_CONFIG_MERG_TOL;
	};

	static auto my_edge_mesh_config = std::make_shared<EdgeMeshConfig>(EdgeMeshConfig{my_curve_info, EDGE_MESH_CONFIG_MERG_TOL});

	auto get_edge_config()
	{
		return *my_edge_mesh_config;
	}

	//.
	//* The curve overall length calculation settings
	//.
	struct EdgeMeshOverallLenConfig
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};
	//- getting the curve overall length calculation settings
	auto get_edge_mesh_overall_len_config()
	{
		return EdgeMeshOverallLenConfig{ my_edge_mesh_config->config->OverallLengthIntgInfo() };
	}
	//.
	//* The integral settings of the curve discretization algorithm
	//.
	struct EdgeMeshIntegConfig
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};
	//- getting the integral settings of the curve discretization algorithm
	auto get_edge_mesh_integ_config()
	{
		return EdgeMeshIntegConfig{ my_edge_mesh_config->config->NewtonIntgInfo() };
	}
	//.
	//* The iteration settings of the curve discretization algorithm
	//.
	struct EdgeMeshIterConfig
	{
		std::shared_ptr<NumAlg_NewtonSolver_Info> config;
	};
	//- getting the iteration settings of the curve discretization algorithm
	auto get_edge_mesh_iter_config()
	{
		return EdgeMeshIterConfig{ my_edge_mesh_config->config->NewtonIterInfo() };
	}
	//.
	//* The correction settings of the curve discretization algorithm
	//.
	struct EdgeMeshCorrConfig
	{
		std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> config;
	};
	//- getting the corrections settings of the curve discretization algorithm
	auto get_edge_mesh_corr_config()
	{
		return EdgeMeshCorrConfig{ my_edge_mesh_config->config->CorrAlgInfo() };
	}

	void set_max_nb_iters(const EdgeMeshOverallLenConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.OverallLen.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_init_nb_iters(const EdgeMeshOverallLenConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.OverallLen.INIT_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	void set_tol(const EdgeMeshOverallLenConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.OverallLen.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_nb_iters(const EdgeMeshIntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Integ.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_init_nb_iters(const EdgeMeshIntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Integ.INIT_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	void set_tol(const EdgeMeshIntegConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Integ.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_max_nb_iters(const EdgeMeshIterConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Iter.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxIterations(n);
	}

	void set_small(const EdgeMeshIterConfig& config, double x)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Iter.SMALL is set to: " << x << "\n";
		}
		config.config->SetSmall(x);
	}

	void set_zero(const EdgeMeshIterConfig& config, double x)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Iter.ZERO is set to: " << x << "\n";
		}
		config.config->SetZero(x);
	}

	void set_tol(const EdgeMeshIterConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Iter.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_ur(const EdgeMeshIterConfig& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Iter.UR is set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}

	void set_max_lev(const EdgeMeshCorrConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Corr.MAX_LEV is set to: " << n << "\n";
		}
		config.config->SetMaxLevel(n);
	}

	void set_tol(const EdgeMeshCorrConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Corr.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_ur(const EdgeMeshCorrConfig& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - EdgeMeshConfig.Corr.UR is set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}
	// =================================================================================
	// Metric config
	// =================================================================================
	//
	//.
	// The metric settings
	struct MetricConfig
	{
		std::shared_ptr<Aft_MetricPrcsrAnIso_Info> config;
	};
	static std::shared_ptr<Aft_MetricPrcsrAnIso_Info> my_metric_config;
	//- getting the metric settings
	auto get_metric_config()
	{
		return MetricConfig{ my_metric_config };
	}
	// The metric integration settings
	struct MetricIntegConfig
	{
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> config;
	};
	// getting the metric integration settings
	auto get_metric_integ_config()
	{
		return MetricIntegConfig{ my_metric_config->IntegInfo() };
	}

	// the metrics settings
	void set_tol(const MetricConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - MetricConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_nb_iters(const MetricConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - MetricConfig.NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbIters(n);
	}

	void set_nb_samples(const MetricConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - MetricConfig.NB_SAMPLES is set to: " << n << "\n";
		}
		config.config->SetNbSamples(n);
	}

	void set_max_nb_iters(const MetricIntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - MetricConfig.Integ.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxNbIterations(n);
	}

	void set_tol(const MetricIntegConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - MetricConfig.Integ.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_init_nb_iters(const MetricIntegConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - MetricConfig.Integ.INIT_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetNbInitIterations(n);
	}

	//.
	// ===================================================================
	// The node calculator algorithm
	// ===================================================================
	//.
	static auto my_size_corr = std::make_shared<Aft_SizeCorr_IterativeInfo>();
	RunTimeConfigs(Iter);
	static const bool SIZE_CORR_DEFAULT_IGNORE_CONV = true;
	static const int SIZE_CORR_DEFAULT_MAX_NB_ITERS = 100;
	static const double SIZE_CORR_DEFAULT_TOL = 1.E-5;
	static const double SIZE_CORR_DEFAULT_UR = 0.85;
	SetRunTimeConfigs(Iter)
	{
		my_size_corr->SetIgnoreNonConvergency(SIZE_CORR_DEFAULT_IGNORE_CONV);
		my_size_corr->SetMaxNbIters(SIZE_CORR_DEFAULT_MAX_NB_ITERS);  // default: 30 [5/24/2022 Amir]
		my_size_corr->SetTolerance(SIZE_CORR_DEFAULT_TOL);  // default: 1.0E-3 [5/24/2022 Amir]
		my_size_corr->SetUnderRelaxation(SIZE_CORR_DEFAULT_UR);  // default: 0.85 [5/24/2022 Amir]
	}
	//* the optimum node generator
	static const int OPT_NODE_GEN_DEFAULT_MAX_SUB_LEV = 5;
	struct OptNodeGenConfig
	{
		std::shared_ptr<Aft_SizeCorr_IterativeInfo> config;
		int max_sub_lev = OPT_NODE_GEN_DEFAULT_MAX_SUB_LEV;
	};
	static const auto my_node_gen_config = std::make_shared<OptNodeGenConfig>(OptNodeGenConfig{ my_size_corr, OPT_NODE_GEN_DEFAULT_MAX_SUB_LEV });
	auto get_node_gen_config()
	{
		return *my_node_gen_config;
	}
	// the iteration settings
	void set_conv_condition(const OptNodeGenConfig& config, bool condition)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - NodeGenConfig.CONV is set to: " << condition << "\n";
		}
		config.config->SetIgnoreNonConvergency(condition);
	}

	void set_max_nb_iters(const OptNodeGenConfig& config, int n)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - NodeGenConfig.MAX_NB_ITERS is set to: " << n << "\n";
		}
		config.config->SetMaxNbIters(n);
	}

	void set_tol(const OptNodeGenConfig& config, double tol)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - NodeGenConfig.TOL is set to: " << tol << "\n";
		}
		config.config->SetTolerance(tol);
	}

	void set_ur(const OptNodeGenConfig& config, double ur)
	{
		if (verbose)
		{
			Info << "\n"
				<< " - NodeGenConfig.UR is set to: " << ur << "\n";
		}
		config.config->SetUnderRelaxation(ur);
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		my_solu_data = file::LoadFile<std::shared_ptr<Aft3d_SolutionData_SurfVol>>(name + extension, verbose);
		if (NOT my_solu_data)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		my_size_fun = my_solu_data->SizeFunction();
		if (NOT my_size_fun)
		{
			FatalErrorIn(FunctionSIG)
				<< "no size map has been found!" << endl
				<< abort(FatalError);
		}

		if (NOT my_solu_data->Geometry())
		{
			FatalErrorIn(FunctionSIG)
				<< "no geometry has been found." << endl
				<< abort(FatalError);
		}
		for (const auto& x: my_solu_data->Geometry()->Volumes())
		{
			Cad_Tools::Connect(x);
		}
		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		my_file_name = name;
		loadFile(name);
	}

	void saveTo(const std::string& name)
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		file::CheckExtension(name);
		file::SaveTo(my_solu_data, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(my_file_name);
	}

	auto calcSize(const Pnt3d& pt)
	{
		return my_size_fun->Value(pt);
	}

	auto createMetricCalculator()
	{
		/*std::shared_ptr<Cad_MetricCalculator> alg =
			std::make_shared<cadLib::MetricCalculator_Std>();
		return std::move(alg);*/
		if (my_size_fun)
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_SizeFun>(&calcSize);
			return std::move(alg);
		}
		else
		{
			std::shared_ptr<Cad_MetricCalculator> alg =
				std::make_shared<cadLib::MetricCalculator_Std>();
			return std::move(alg);
		}
	}

	auto mesh
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurface>& theMetricPrcsr,
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		const auto alg = std::make_shared<Aft2d_tModelSurface>();
		alg->LoadMetricMap(theMetricPrcsr);
		alg->LoadBoundaryMetricMap(theMetricPrcsr);

		alg->LoadBoundaryEdges(theBoundaries);
		alg->LoadNodeCalculator(theCalculator);

		alg->SetMinDistFactor(0.4);
		//Aft2d_gModelSurface::ALLOWED_MAX_LEVEL_GENERATION = 30;
		{// timer scope [3/12/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			alg->Perform();
		}

		const auto& elem_map = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elem_map.size());
		for (const auto& x : elem_map)
		{
			elements.push_back(x.second);
		}
		auto nodes_ref = Aft_Tools::RetrieveNodes(elements);
		const auto nodes = std::make_shared<std::vector<std::shared_ptr<Aft2d_NodeSurface>>>(std::move(nodes_ref));

		const auto avg_fun = std::make_shared<MeshPost2d_LaplacianSmoothingSurface_AdjEdges>();
		avg_fun->SetMetrics(theMetricPrcsr);

		const auto quality_fun = std::make_shared<MeshPost2d_QualityMapSurface_Vlrms2Ratio>();
		quality_fun->SetMetrics(theMetricPrcsr);

		const auto smoothing_alg = std::make_shared<MeshPost2d_LaplacianSmoothingSurface>();
		smoothing_alg->SetAvgFun(avg_fun);
		smoothing_alg->SetQualityFun(quality_fun);
		smoothing_alg->SetInfo(my_laplacian_smooth_info);
		smoothing_alg->SetNodes(nodes);

		if (my_smoothing_config->apply)
		{
			smoothing_alg->Perform();
		}

		Aft_Tools::CalcCood3d(nodes_ref, *theMetricPrcsr->Geometry());

		return std::move(elements);
	}

	auto mesh
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theMetricPrcsr,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theCalculator,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		const auto alg = std::make_shared<Aft2d_tModelSurfaceUniMetric>();
		alg->LoadMetricMap(theMetricPrcsr);
		alg->LoadBoundaryMetricMap(theMetricPrcsr);

		alg->LoadBoundaryEdges(theBoundaries);
		alg->LoadNodeCalculator(theCalculator);

		alg->SetMinDistFactor(0.4);
		{// timer scope [3/12/2022 Amir]
			Global_Timer timer;
			timer.SetInfo(Global_TimerInfo_s);

			alg->Perform();
		}

		const auto& elem_map = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elem_map.size());
		for (const auto& x : elem_map)
		{
			elements.push_back(x.second);
		}
		auto nodes_ref = Aft_Tools::RetrieveNodes(elements);
		const auto nodes = std::make_shared<std::vector<std::shared_ptr<Aft2d_NodeSurface>>>(std::move(nodes_ref));

		const auto avg_fun = std::make_shared<MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AdjEdges>();
		avg_fun->SetMetrics(theMetricPrcsr);

		const auto quality_fun = std::make_shared<MeshPost2d_QualityMapSurfaceUniMetric_Vlrms2Ratio>();
		quality_fun->SetMetrics(theMetricPrcsr);

		const auto smoothing_alg = std::make_shared<MeshPost2d_LaplacianSmoothingSurfaceUniMetric>();
		smoothing_alg->SetAvgFun(avg_fun);
		smoothing_alg->SetQualityFun(quality_fun);
		smoothing_alg->SetInfo(my_laplacian_smooth_info);
		smoothing_alg->SetNodes(nodes);

		if (my_smoothing_config->apply)
		{
			smoothing_alg->Perform();
		}

		Aft_Tools::CalcCood3d(nodes_ref, *theMetricPrcsr->Geometry());

		return std::move(elements);
	}

	auto project_mesh(const Entity3d_Triangulation& tri3d, const Handle(Geom_Surface)& theSurface, const Entity2d_Box& bounds)
	{
		const auto u_min = bounds.P0().X();
		const auto u_max = bounds.P1().X();
		const auto v_min = bounds.P0().Y();
		const auto v_max = bounds.P1().Y();
		// create the projector object
		GeomAPI_ProjectPointOnSurf projection(tri3d.Points().at(0), theSurface, u_min, u_max, v_min, v_max);
		std::vector<Pnt2d> pnts;
		pnts.reserve(tri3d.NbPoints());
		for (const auto& pt3d: tri3d.Points())
		{
			projection.Perform(pt3d);
			double u, v;
			projection.LowerDistanceParameters(u, v);
			pnts.emplace_back(u, v);
		}
		auto ids = tri3d.Connectivity();
		auto tri = std::make_shared<Entity2d_Triangulation>(std::move(pnts), std::move(ids));
		return std::move(tri);
	}

	auto mesh
	(
		const std::shared_ptr<TModel_Surface>& theSurface,
		const std::shared_ptr<Geo3d_SizeFunction>& theSizeFun,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theUniMetricCalculator,
		const std::shared_ptr<Aft2d_OptNodeSurface_Calculator>& theCalculator,
		const std::shared_ptr<Aft2d_BoundaryOfPlaneAnIso_Info>& theBndInfo,
		const std::shared_ptr<Aft_MetricPrcsrAnIso_Info>& theInfo
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
		auto tol = my_tol * d;

		auto metricCalculator = createMetricCalculator();

		std::vector<std::vector<std::shared_ptr<Aft2d_ElementSurface>>> meshes;
		std::vector<std::vector<std::shared_ptr<Aft2d_EdgeSurface>>> bMeshes;

		if (TModel_Tools::IsPlane(theSurface))
		{
			auto pln = TModel_Tools::GetParaPlane(theSurface, Precision::PConfusion());
			auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);

			auto gPlane = Handle(Geom_Plane)::DownCast(geometry);
			if (NOT gPlane)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "the geometry is not plane!" << endl
					<< abort(FatalError);
			}
			auto metricFun = std::make_shared<GeoMetricFun2d_Plane>(gPlane, box);

			//Aft2d_MetricPrcsrSurfaceUniMetric xx(sizeFun, metricFun, theInfo);
			/*auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurfaceUniMetric_RefineH>();
			metricPrcsr->SetCoeff(my_coeff);
			metricPrcsr->SetDelta(my_delta);
			metricPrcsr->SetSizeFun(sizeFun);
			metricPrcsr->SetMetricFun(metricFun);
			metricPrcsr->SetInfo(theInfo);
			metricPrcsr->SetDimSize(box.Diameter());
			metricPrcsr->SetGeometry(geometry);

			metricPrcsr->SetNodeCalculator(theUniMetricCalculator);*/

			auto metric_prcsr = std::make_shared<Aft2d_MetricPrcsrSurfaceUniMetric>(sizeFun, metricFun, theInfo);
			metric_prcsr->SetDimSize(box.Diameter());
			metric_prcsr->SetGeometry(geometry);

			if (auto optNodeAlg = std::dynamic_pointer_cast<Aft2d_OptNodeSurfaceUniMetric_Standard>(theUniMetricCalculator))
			{
				optNodeAlg->SetMetricMap(metric_prcsr);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid optimum point calculator has been detected!" << endl
					<< abort(FatalError);
			}

			auto plnRegion = Aft2d_tRegionPlaneSurfaceUniMetric::MakePlane(pln);
			//std::cout << "nb curves: " << plnRegion->Outer()->NbCurves() << std::endl;
			Aft2d_tBoundaryOfPlaneSurfaceUniMetric::verbose = 1;
			auto bnd = std::make_shared<Aft2d_tBoundaryOfPlaneSurfaceUniMetric>(theBndInfo);
			bnd->LoadMetricProcessor(metric_prcsr);
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
			auto elements = mesh(metric_prcsr, theUniMetricCalculator, ibMesh);
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

			auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);

			auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(geometry, box);
			/*auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurface_RefineH>();
			metricPrcsr->SetCoeff(my_coeff);
			metricPrcsr->SetDelta(my_delta);
			metricPrcsr->SetSizeFun(sizeFun);
			metricPrcsr->SetMetricFun(metricFun);
			metricPrcsr->SetInfo(theInfo);
			metricPrcsr->SetDimSize(box.Diameter());
			metricPrcsr->SetGeometry(geometry);*/
			auto metric_prcsr = std::make_shared<Aft2d_MetricPrcsrSurface>(sizeFun, metricFun, theInfo);
			metric_prcsr->SetDimSize(box.Diameter());
			metric_prcsr->SetGeometry(geometry);

			//metricPrcsr->SetNodeCalculator(theCalculator);

			if (auto optNodeAlg = std::dynamic_pointer_cast<Aft2d_OptNodeSurface_Altr>(theCalculator))
			{
				optNodeAlg->SetMetricMap(metric_prcsr);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid optimum point calculator has been detected!" << endl
					<< abort(FatalError);
			}

			auto bnd = std::make_shared<Aft2d_tBoundaryOfPlaneSurface>(theBndInfo);
			bnd->LoadMetricProcessor(metric_prcsr);
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
			auto elements = mesh(metric_prcsr, theCalculator, ibMesh);

			meshes.push_back(std::move(elements));
			bMeshes.push_back(std::move(ibMesh));

			auto t = std::make_pair(std::move(meshes), std::move(bMeshes));
			return std::move(t);
		}
	}

	auto retrieveTris3d(const std::shared_ptr<TModel_Surface>& surface, const Entity2d_Triangulation& theTris)
	{
		auto tris3d = Cad_Tools::Triangulation(*surface->GeomSurface()->Geometry(), theTris);
		return std::move(tris3d);
	}

	auto createSamples()
	{
		std::shared_ptr<Geo2d_SamplePoints> samples;
		switch (my_smaple_type)
		{
		case tnbLib::Geo2d_SamplePoints::Type::four_points:
			samples = std::make_shared<Geo2d_SamplePoints_4Pts>();
			break;
		case tnbLib::Geo2d_SamplePoints::Type::five_points:
			samples = std::make_shared<Geo2d_SamplePoints_5Pts>();
			break;
		case tnbLib::Geo2d_SamplePoints::Type::eight_points:
			samples = std::make_shared<Geo2d_SamplePoints_8Pts>();
			break;
		case tnbLib::Geo2d_SamplePoints::Type::nine_points:
			samples = std::make_shared<Geo2d_SamplePoints_9Pts>();
			break;
			/*case tnbLib::Geo2d_SamplePoints::Type::eight_points_2layer:
				samples = std::make_shared<Geo2d_SamplePoints_8Pts2ply>();
				break;*/
				/*case tnbLib::Geo2d_SamplePoints::Type::nine_points_2layer:
					samples = std::make_shared<Geo2d_SamplePoints_9Pts2ply>();
					break;*/
					/*case tnbLib::Geo2d_SamplePoints::Type::thirteen_points_2layer:
						samples = std::make_shared<Geo2d_SamplePoints_13Pts2ply>();
						break;*/
		default:
			FatalErrorIn(FunctionSIG)
				<< "unspecified type of samples has been detected!" << endl
				<< abort(FatalError);
			break;
		}
		return std::move(samples);
	}

	auto createCriterion(const std::shared_ptr<Cad_MetricCalculator>& calc)
	{
		auto alg = std::make_shared<cadLib::ApprxMetricCriterion_MinMax>(my_metric_approx_tol, calc);
		alg->SetTolerance(0.2);
		return std::move(alg);
	}

	void execute()
	{
		if (verbose)
		{
			MeshPost2d_LaplacianSmoothingSurface::verbose = verbose;
			MeshPost2d_LaplacianSmoothingSurfaceUniMetric::verbose = verbose;
			Aft2d_tBoundaryOfPlaneSurface::verbose = verbose;
			Aft2d_tBoundaryOfPlaneSurfaceUniMetric::verbose = verbose;
		}

		Mesh2d_CurveUniMetric::nbLevels_CheckingLength = 8;
		Mesh2d_CurveAnIso::nbLevels_CheckingLength = 8;

		//Aft2d_gModelSurface::verbose = 1;

		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& model = my_solu_data->Geometry();
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< "th model is null!" << endl
				<< abort(FatalError);
		}

		//myLaplacianSmoothInfo->SetNbLevels(smooth_nb_iters);
		//myLaplacianSmoothInfo->SetUnderRelaxation(smooth_ur);

		auto metricCalculator = createMetricCalculator();
		auto criterion = createCriterion(metricCalculator);
		auto samples = createSamples();

		//myMaxLev = 7;

		/*myMetricApproxInfo = std::make_shared<Cad_ApprxMetricInfo>();
		myMetricApproxInfo->SetMinLevel(myMinLev);
		myMetricApproxInfo->SetMaxLevel(myMaxLev);
		myMetricApproxInfo->SetUnbalancing(myUnBalance);

		myMetricApproxInfo->MergeInfoRef().SetRadius(myRadius);
		myMetricApproxInfo->MergeInfoRef().SetResolution(myRes);

		myMetricApproxInfo->OverrideSamples(samples);
		myMetricApproxInfo->OverrideCriterion(criterion);*/

		const auto& sizeFun3d = my_solu_data->SizeFunction();

		//auto fracInfo = std::make_shared<Aft_SizeCorr_FractionInfo>();

		//auto anIsoOptNodeInfo = std::make_shared<Aft2d_OptNodeAnIso_nonIterAdaptiveInfo>(iterInfo, fracInfo);
		//auto anIsoOptNodeUniMetric = std::make_shared<Aft2d_OptNodeSurfaceUniMetric_IterAdaptive>(iterInfo);
		auto anIsoOptNodeUniMetric = std::make_shared<Aft2d_OptNodeSurfaceUniMetric_Standard>();

		//auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_nonIterAdaptive>(anIsoOptNodeInfo);

		/*auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_MetricCorr>();
		anIsoOptNode_altrAlg->SetIterInfo(iterInfo);
		anIsoOptNode_altrAlg->SetMaxLev(5);*/

		auto nelderInfo = std::make_shared<NumAlg_NelderMeadInfo>();
		nelderInfo->SetMaxNbIterations(50);
		nelderInfo->SetTolerance(1.0E-3);

		/*auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_NelderMead>();
		anIsoOptNode_altrAlg->SetInfo(nelderInfo);*/

		/*auto bisectInfo = std::make_shared<NumAlg_BisectionSolver_Info>();
		bisectInfo->SetDelta(1.0E-4);
		bisectInfo->SetTolerance(1.0E-4);
		bisectInfo->SetMaxIterations(20);*/

		auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_SubTri>();
		anIsoOptNode_altrAlg->SetSizeCorrInfo(my_size_corr);
		anIsoOptNode_altrAlg->SetNealderMeadInfo(nelderInfo);
		anIsoOptNode_altrAlg->SetMaxLev(my_node_gen_config->max_sub_lev);

		auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_Altr>(anIsoOptNode_altrAlg, my_size_corr);
		//auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_Standard>(iterInfo);

		//my_solu_data->CurveInfo()->CorrAlgInfo()->SetMaxLevel(30);

		/*const auto& overallLenInfo = mySoluData->GlobalCurveInfo()->OverallLengthIntgInfo();
		overallLenInfo->SetTolerance(1.0E-8);
		overallLenInfo->SetMaxNbIterations(500);
		overallLenInfo->SetNbInitIterations(10);

		const auto& corrIntegInfo = mySoluData->GlobalCurveInfo()->CorrAlgInfo();
		corrIntegInfo->SetTolerance(1.0E-6);
		corrIntegInfo->SetMaxLevel(50);*/

		auto bndInfo = std::make_shared<Aft2d_BoundaryOfPlaneAnIso_Info>();
		bndInfo->SetOverrideInfo(Standard_False);
		bndInfo->OverrideGlobalCurve(my_solu_data->CurveInfo());
		bndInfo->SetMergeTolerance(1.0E-6);
		bndInfo->OverrideGlobalMetricPrcsr(my_solu_data->MetricProcessorInfo());

		my_solu_data->TrisRef().clear();

		std::vector<std::shared_ptr<TModel_Surface>> triSurfaces;
		Standard_Integer nbSurfaces = 0;

		for (const auto& x : model->RetrieveSurfaces())
		{
			//const TopoDS_Face& face = x->Face();
			//std::cout << face.IsNull() << std::endl;
			Debug_Null_Pointer(x);
			/*if (x->Face().IsNull())
			{
				continue;
			}*/

			if (Cad_Tools::HasTriangulation(x->Face()))
			{
				triSurfaces.push_back(x);
				x->SetIndex(++nbSurfaces);
			}
		}

		//OFstream myFile("boundaryCurves.plt");
		//OFstream myFile1("boundaryMesh.plt");

		if (triSurfaces.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "no triangulated surface has been found." << endl
				<< abort(FatalError);
		}

		std::map<int, int> already_meshed;

		for (const auto& x : triSurfaces)
		{
			Debug_Null_Pointer(x);
			if (verbose)
			{
				Info << endl
					<< "- meshing surface, " << x->Index() << endl;
			}
			/*if (x->Index() NOT_EQUAL 8)
			{
				continue;
			}*/
			//x->ExportPlaneCurvesToPlt(myFile);

			const TopoDS_Face& face = x->Face();

			/*auto ff = GModel_Tools::GetSurface(face);
			std::exit(1);*/

			if (auto paired = model->IsPairedSurface(x->Index()))
			{
				if (my_solu_data->Tris().find(x->Index()) != my_solu_data->TrisRef().end())
				{// registered mesh has been found
					continue; // skip the surface
				}
			}

			try
			{
				auto [plnMesh, bMesh] = mesh(x, sizeFun3d, anIsoOptNodeUniMetric, anIsoOptNode, bndInfo, my_solu_data->MetricProcessorInfo());

				/*for (const auto& ibMesh : bMesh)
				{
					auto bTri = Aft_Tools::RetrieveTriangleMesh(ibMesh);
					bTri->ExportToPlt(myFile1);
				}*/
				if (plnMesh.size() IS_EQUAL 1)
				{
					auto tris = Aft_Tools::RetrieveTriangleMesh(plnMesh.at(0));


					file::SaveTo(tris, "planar" + Entity2d_Triangulation::extension, 1);
					//std::exit(0);

					auto tris3d = retrieveTris3d(x, *tris);

					if (face.Orientation() IS_EQUAL TopAbs_Orientation::TopAbs_REVERSED)
					{
						Geo_Tools::Reverse(*tris3d);
					}

					std::cout << " - nb. of elements: " << tris3d->NbConnectivity() << std::endl;
					Global_Tools::Insert(x->Index(), tris3d, my_solu_data->TrisRef());
				}
				else
				{
					Entity2d_Triangulation mesh2d;
					for (const auto& m : plnMesh)
					{
						auto tris = Aft_Tools::RetrieveTriangleMesh(m);

						mesh2d.Add(*tris);
					}
					auto tris3d = retrieveTris3d(x, mesh2d);
					if (face.Orientation() IS_EQUAL TopAbs_Orientation::TopAbs_REVERSED)
					{
						Geo_Tools::Reverse(*tris3d);
					}
					if (const auto paired = model->IsPairedSurface(x->Index()))
					{
						auto paired_mesh = std::make_shared<Entity3d_Triangulation>(*tris3d);
						Global_Tools::Insert(paired, paired_mesh, my_solu_data->TrisRef());
					}
					std::cout << " - nb. of elements: " << tris3d->NbConnectivity() << std::endl;
					Global_Tools::Insert(x->Index(), tris3d, my_solu_data->TrisRef());
				}
			}
			catch (const error& x)
			{
				std::cout << x.message() << std::endl;
				PAUSE;
			}

			if (verbose)
			{
				Info << " - surface, " << x->Index() << ", is discretized, successfully!" << endl;
			}


		}
		exeTag = true;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "save_to");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "load_file");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "load_file");

		// settings

		// The smoothing algorithm's settings
		mod->add(chaiscript::fun([](const SmoothConfig& config, int n)-> void {set_nb_iters(config, n); }), "set_nb_iters");
		mod->add(chaiscript::fun([](const SmoothConfig& config, double ur)->void {set_ur(config, ur); }), "set_ur");
		mod->add(chaiscript::fun([](const SmoothConfig& config, bool apply)->void {set_apply(config, apply); }), "set_apply");

		// The edge mesh algorithm's settings
		mod->add(chaiscript::fun([](const EdgeMeshOverallLenConfig& config, int n)->void {set_max_nb_iters(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const EdgeMeshOverallLenConfig& config, int n)-> void {set_init_nb_iters(config, n); }), "set_init_nb_iters");
		mod->add(chaiscript::fun([](const EdgeMeshOverallLenConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");

		mod->add(chaiscript::fun([](const EdgeMeshIntegConfig& config, int n)->void {set_max_nb_iters(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const EdgeMeshIntegConfig& config, int n)->void {set_init_nb_iters(config, n); }), "set_init_nb_iters");
		mod->add(chaiscript::fun([](const EdgeMeshIntegConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");

		mod->add(chaiscript::fun([](const EdgeMeshIterConfig& config, int n)->void {set_max_nb_iters(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const EdgeMeshIterConfig& config, double small)->void {set_small(config, small); }), "set_small");
		mod->add(chaiscript::fun([](const EdgeMeshIterConfig& config, double zero)->void {set_zero(config, zero); }), "set_zero");
		mod->add(chaiscript::fun([](const EdgeMeshIterConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const EdgeMeshIterConfig& config, double ur)->void {set_ur(config, ur); }), "set_ur");

		mod->add(chaiscript::fun([](const EdgeMeshCorrConfig& config, int n)->void {set_max_lev(config, n); }), "set_max_lev");
		mod->add(chaiscript::fun([](const EdgeMeshCorrConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const EdgeMeshCorrConfig& config, double ur)->void {set_ur(config, ur); }), "set_ur");

		// The metric settings
		mod->add(chaiscript::fun([](const MetricConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const MetricConfig& config, int n)->void {set_nb_iters(config, n); }), "set_nb_iters");
		mod->add(chaiscript::fun([](const MetricConfig& config, int n)->void {set_nb_samples(config, n); }), "set_nb_samples");
		mod->add(chaiscript::fun([](const MetricIntegConfig& config, int n)->void {set_max_nb_iters(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const MetricIntegConfig& config, int n)->void {set_init_nb_iters(config, n); }), "set_init_nb_iters");
		mod->add(chaiscript::fun([](const MetricIntegConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");

		// The optimum node generator settings
		mod->add(chaiscript::fun([](const OptNodeGenConfig& config, bool condition)->void {set_conv_condition(config, condition); }), "set_conv_conditon");
		mod->add(chaiscript::fun([](const OptNodeGenConfig& config, int n)->void {set_max_nb_iters(config, n); }), "set_max_nb_iters");
		mod->add(chaiscript::fun([](const OptNodeGenConfig& config, double tol)->void {set_tol(config, tol); }), "set_tol");
		mod->add(chaiscript::fun([](const OptNodeGenConfig& config, double ur)->void {set_ur(config, ur); }), "set_ur");

		// operators
		mod->add(chaiscript::fun([]()->auto {return get_smooth_config(); }), "get_smooth_config");
		mod->add(chaiscript::fun([]()->auto {return get_edge_config(); }), "get_edge_mesh_config");
		mod->add(chaiscript::fun([]()->auto {return get_metric_config(); }), "get_metric_config");
		mod->add(chaiscript::fun([]()->auto {return get_node_gen_config(); }), "get_node_gen_config");
		
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
			Info << " This application is aimed to mesh the surfaces of a tModel." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
				<< " - saveTo(name [optional])" << endl << endl

				<< " # Settings: " << endl << endl

				<< " - doSmoothing(bool)" << endl << endl

				<< " - (Smooth).setNbIterations(n)" << endl
				<< " - (Smooth).setUnderRelaxation(x)" << endl << endl

				<< " - (Integ).setTolerance(x)" << endl
				<< " - (Integ).setMaxNbIterations(n)" << endl
				<< " - (Integ).setNbInitialIterations(n)" << endl << endl

				<< " - (Iter).setTolerance(x)" << endl
				<< " - (Iter).setMaxNbIterations(n)" << endl
				<< " - (Iter).setUnderRelaxation(x)" << endl
				<< " - (Iter).ignoreNonConvergency()" << endl << endl

				<< " - (Metrics).setTolerance(x)" << endl
				<< " - (Metrics).setNbSamples(n)" << endl
				<< " - (Metrics).setNbIerations(n)" << endl << endl

				<< " - setVerbose(unsigned int); Levels: 0, 1, 2" << endl << endl

				<< " # Operators:" << endl << endl

				<< " - [Smooth] getSmoothAlg()" << endl
				<< " - [Metrics] getMetrics()" << endl
				<< " - [Integ] getIntegAlg()" << endl
				<< " - [Iter] getIterAlg()" << endl << endl

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
				fileName myFileName(file::GetSystemFile("tnbMeshtSurfAft"));

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