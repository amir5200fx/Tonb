#include <Aft2d_gModelSurface.hxx>
#include <Aft2d_gModelSurfaceUniMetric.hxx>
#include <Aft2d_gSolutionDataSurface.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_MetricPrcsrSurface.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetric.hxx>
#include <Aft2d_gBoundaryOfPlaneSurfaceUniMetric.hxx>
#include <Aft2d_gBoundaryOfPlaneSurface.hxx>
#include <Aft2d_BoundaryOfPlaneAnIso_Info.hxx>
#include <Aft2d_gRegionPlaneSurfaceUniMetric.hxx>
#include <Aft2d_gRegionPlaneSurface.hxx>
#include <Aft2d_OptNodeSurface_Algs.hxx>
#include <Aft2d_AltrOptNodeSurface_MetricCorr.hxx>
#include <Aft2d_AltrOptNodeSurface_NelderMead.hxx>
#include <Aft2d_AltrOptNodeSurface_PerpenDir.hxx>
#include <Aft2d_AltrOptNodeSurface_SubTri.hxx>
#include <Aft2d_AltrOptNodeSurface_SubTri2.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_OptNodeAnIso_nonIterAdaptiveInfo.hxx>
#include <Aft_Tools.hxx>
#include <Aft_SizeCorr_IterativeInfo.hxx>
#include <Aft_SizeCorr_FractionInfo.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <Aft2d_gSegmentEdge.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh_Curve_Info.hxx>
#include <Mesh_CurveOptmPoint_Correction_Info.hxx>
#include <Cad_gSingularity.hxx>
#include <Cad_ApprxMetricInfo.hxx>
#include <Cad_ApprxMetric.hxx>
#include <Cad_ColorApprxMetric.hxx>
#include <Cad_ApprxMetricCriterion_MinMax.hxx>
#include <Cad_MetricCalculator_SizeFun.hxx>
#include <Cad_MetricCalculator_Std.hxx>
#include <Cad_SingularityHorizons.hxx>
#include <Cad_gSingularity.hxx>
#include <Cad_gModifySingularPlane.hxx>
#include <Cad_gApprxParaPlane.hxx>
#include <Cad_Tools.hxx>
#include <Cad_gMetricRepair.hxx>
#include <Cad_CharLength.hxx>
#include <Cad_gCommonSingularity.hxx>
#include <GModel_Tools.hxx>
#include <GModel_Surface.hxx>
#include <GModel_Plane.hxx>
#include <GModel_ParaCurve.hxx>
#include <GModel_ParaWire.hxx>
#include <Geo_Tools.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Cad_GeomSurface.hxx>
#include <GeoSizeFun2d_Surface.hxx>
#include <GeoMetricFun2d_ExactSurface.hxx>
#include <GeoMetricFun2d_Plane.hxx>
#include <Geo2d_SamplePoints.hxx>
//#include <Geo2d_SamplePoints_13Pts2ply.hxx>
#include <Geo2d_SamplePoints_4Pts.hxx>
#include <Geo2d_SamplePoints_5Pts.hxx>
#include <Geo2d_SamplePoints_8Pts.hxx>
//#include <Geo2d_SamplePoints_8Pts2ply.hxx>
#include <Geo2d_SamplePoints_9Pts.hxx>
//#include <Geo2d_SamplePoints_9Pts2ply.hxx>
#include <Entity2d_MeshValue.hxx>
#include <Cad_GModel.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <NumAlg_NelderMeadInfo.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>

#include <Entity2d_Box.hxx>
#include <Global_File.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <TopoDS_Face.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <Precision.hxx>

#include <Cad_gApprxParaPlane.hxx>

namespace tnbLib
{

	static const std::string extension = Aft2d_gSolutionDataSurface::extension;

	static unsigned short verbose = 0;
	static bool loadTag = false;
	static bool exeTag = false;

	static std::shared_ptr<Geo_ApprxCurve_Info> myCurveApproxInfo = std::make_shared<Geo_ApprxCurve_Info>();
	static std::shared_ptr<Cad_ApprxMetricInfo> myMetricApproxInfo;
	static std::shared_ptr<Geo3d_SizeFunction> mySizeFun;

	static double myDegenCrit = 1.0e-6;//Cad_SingularityHorizons::DEFAULT_DEGEN_CRITERION;
	static auto mySingZoneWeight = Cad_gSingularity::DEFAULT_WEIGHT;

	static std::shared_ptr<Aft2d_gSolutionDataSurface> mySoluData;
	static std::string myFileName;

	static double myTol = 1.0E-5;

	// approximation settings [4/25/2022 Amir]
	static auto myMinLev = Cad_ApprxMetricInfo::DEFAULT_MIN_LEVEL;
	static auto myMaxLev = Cad_ApprxMetricInfo::DEFAULT_MAX_LEVEL;
	static auto myUnBalance = Cad_ApprxMetricInfo::DEFAULT_UNBALANCING;

	static auto myRadius = Merge_PntInfo::DEFAULT_RADIUS;
	static auto myRes = Merge_PntInfo::DEFAULT_RESOLUTION;

	static auto mySampleType = Geo2d_SamplePoints::Type::five_points;
	static auto myMetricApproxTol = Cad_ApprxMetricCriterion::DEFAULT_TOLERANCE;

	void setVerbose(unsigned int i)
	{
		Info << endl;
		Info << " - the verbosity level is set to: " << i << endl;
		verbose = i;
	}

	void setTolerance(double x)
	{
		myTol = x;
		if (verbose)
		{
			Info << endl
				<< " - the tolerance is set to: " << myTol << endl;
		}
	}

	void loadFile(const std::string& name)
	{
		file::CheckExtension(name);

		mySoluData = file::LoadFile<std::shared_ptr<Aft2d_gSolutionDataSurface>>(name + extension, verbose);
		if (NOT mySoluData)
		{
			FatalErrorIn(FunctionSIG)
				<< "the data solution file is null!" << endl
				<< abort(FatalError);
		}

		mySizeFun = mySoluData->SizeFun();
		if (NOT mySizeFun)
		{
			FatalErrorIn(FunctionSIG)
				<< "no size map has been found!" << endl
				<< abort(FatalError);
		}

		loadTag = true;
	}

	void loadFile()
	{
		auto name = file::GetSingleFile(boost::filesystem::current_path(), extension).string();
		myFileName = name;
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

		file::SaveTo(mySoluData, name + extension, verbose);
	}

	void saveTo()
	{
		if (NOT exeTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "the application is not performed!" << endl
				<< abort(FatalError);
		}
		saveTo(myFileName);
	}

	auto calcSize(const Pnt3d& pt)
	{
		return mySizeFun->Value(pt);
	}

	auto createNonSizeMapMetricCalculator()
	{
		std::shared_ptr<Cad_MetricCalculator> alg =
			std::make_shared<cadLib::MetricCalculator_Std>();
		return std::move(alg);
	}

	auto createMetricCalculator()
	{
		/*std::shared_ptr<Cad_MetricCalculator> alg =
			std::make_shared<cadLib::MetricCalculator_Std>();
		return std::move(alg);*/
		if (mySizeFun)
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
		auto alg = std::make_shared<Aft2d_gModelSurface>();
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

		const auto& elemMap = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements.push_back(x.second);
		}
		return std::move(elements);
	}

	auto mesh
	(
		const std::shared_ptr<Aft2d_MetricPrcsrSurfaceUniMetric>& theMetricPrcsr,
		const std::shared_ptr<Aft2d_OptNodeSurfaceUniMetric_Calculator>& theCalculator,
		const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>& theBoundaries
	)
	{
		auto alg = std::make_shared<Aft2d_gModelSurfaceUniMetric>();
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

		const auto& elemMap = alg->RetrieveElements();
		std::vector<std::shared_ptr<Aft2d_ElementSurface>> elements;
		elements.reserve(elemMap.size());
		for (const auto& x : elemMap)
		{
			elements.push_back(x.second);
		}
		return std::move(elements);
	}

	auto mesh
	(
		const std::shared_ptr<GModel_Surface>& theSurface, 
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

		auto wire = GModel_Tools::GetOuterParaWire(theSurface);
		auto box = GModel_Tools::CalcBoundingBox(*wire);

		auto d = box.Diameter();
		auto tol = myTol * d;
		//auto tol = 1.0E-8 * d;
		//std::cout << "get para plane" << std::endl;
		
		//std::cout << "para plane is created!" << std::endl;
		
		auto metricCalculator = createMetricCalculator();

		std::vector<std::vector<std::shared_ptr<Aft2d_ElementSurface>>> meshes;

		/*std::cout << std::endl;
		std::cout << " - Is Plane? " << (GModel_Tools::IsPlane(theSurface) ? "YES" : "NO") << std::endl;
		std::cout << std::endl;*/

		if (GModel_Tools::IsPlane(theSurface))
		{
			auto pln = GModel_Tools::GetParaPlane(theSurface, Precision::PConfusion());
			//std::cout << " the plane is created." << std::endl;
			auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);

			auto gPlane = Handle(Geom_Plane)::DownCast(geometry);
			if (NOT gPlane)
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "the geometry is not plane!" << endl
					<< abort(FatalError);
			}
			auto metricFun = std::make_shared<GeoMetricFun2d_Plane>(gPlane, box);
			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurfaceUniMetric>(sizeFun, metricFun, theInfo);
			metricPrcsr->SetDimSize(box.Diameter());
			metricPrcsr->SetGeometry(geometry);

			if (auto optNodeAlg = std::dynamic_pointer_cast<Aft2d_OptNodeSurfaceUniMetric_nonIterAdaptive>(theUniMetricCalculator))
			{
				optNodeAlg->SetMetricMap(metricPrcsr);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "invalid optimum point calculator has been detected!" << endl
					<< abort(FatalError);
			}

			auto plnRegion = Aft2d_gRegionPlaneSurfaceUniMetric::MakePlane(pln);

			Aft2d_gBoundaryOfPlaneSurfaceUniMetric::verbose = 1;
			auto bnd = std::make_shared<Aft2d_gBoundaryOfPlaneSurfaceUniMetric>(theBndInfo);
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
			/*{
				auto upBnds = Global_Tools::UpCast<Aft2d_gSegmentEdgeUniMetric, Aft2d_EdgeSurface>(boundaries);
				auto nodes = Aft_Tools::RetrieveNodes(upBnds);
				auto pts = Aft_Tools::RetrieveGeometry(nodes);
				auto inds = Aft_Tools::RetrieveEdgeConnectivities(upBnds);
				auto chain = Entity2d_Chain(std::move(pts), std::move(inds));
				auto mm = Geo_Tools::Triangulation(chain);

				file::SaveTo(mm, "boundaryMesh" + Entity2d_Triangulation::extension, 1);
				std::exit(0);
			}*/
			Aft_Tools::Connect(boundaries);

			auto elements = mesh(metricPrcsr, theUniMetricCalculator, Aft_Tools::UpCast(boundaries));
			meshes.push_back(std::move(elements));
			return std::move(meshes);
		}
		else
		{

			{
				auto pln = GModel_Tools::GetParaPlane(theSurface, Precision::PConfusion());

				auto plnRegion = Aft2d_gRegionPlaneSurface::MakePlane(pln);

				auto singAlg = std::make_shared<Cad_gCommonSingularity>();
				singAlg->SetPlane(plnRegion);
				singAlg->SetSurface(theSurface);
				singAlg->SetTolerance(1.0E-6);

				singAlg->Perform();

				plnRegion = singAlg->Modified();

				auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);

				auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(geometry, box);
				auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurface>(sizeFun, metricFun, theInfo);
				metricPrcsr->SetDimSize(box.Diameter());
				metricPrcsr->SetGeometry(geometry);

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

				auto bnd = std::make_shared<Aft2d_gBoundaryOfPlaneSurface>(theBndInfo);
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

				/*{
					auto upBnds = Global_Tools::UpCast<Aft2d_gSegmentEdge, Aft2d_EdgeSurface>(boundaries);
					auto nodes = Aft_Tools::RetrieveNodes(upBnds);
					auto pts = Aft_Tools::RetrieveGeometry(nodes);
					auto inds = Aft_Tools::RetrieveEdgeConnectivities(upBnds);
					auto chain = Entity2d_Chain(std::move(pts), std::move(inds));
					auto mm = Geo_Tools::Triangulation(chain);

					file::SaveTo(mm, "boundaryMesh" + Entity2d_Triangulation::extension, 1);
					std::exit(0);
				}*/

				Aft_Tools::Connect(boundaries);

				auto elements = mesh(metricPrcsr, theCalculator, Aft_Tools::UpCast(boundaries));

				meshes.push_back(std::move(elements));
				return std::move(meshes);
			}

			auto surface = theSurface;
			std::shared_ptr<GModel_Plane> pln;

			gp_Trsf2d trans;
			trans.SetScale(box.P0(), 1.0);

			Standard_Boolean isTransf = Standard_False;

			auto bspline = Handle(Geom_BSplineSurface)::DownCast(geometry);
			if (bspline)
			{
				auto charLen = std::make_shared<Cad_CharLength>();
				charLen->SetDomain(std::make_shared<Entity2d_Box>(box));
				charLen->SetSurface(geometry);

				charLen->Perform();
				Debug_If_Condition_Message(NOT charLen->IsDone(), "the application is not performed");

				const auto uLen = charLen->LengthU();
				const auto vLen = charLen->LengthV();
				//std::cout << "uLen: " << uLen << ", vLen: " << vLen << std::endl;
				auto scaleRepair = std::make_shared<Cad_gMetricRepair>();
				scaleRepair->SetCharLenU(uLen);
				scaleRepair->SetCharLenV(vLen);
				scaleRepair->SetDomain(std::make_shared<Entity2d_Box>(box));
				scaleRepair->SetPatch(theSurface);

				scaleRepair->Perform();
				
				trans = scaleRepair->Trsf().Inverted();
				isTransf = Standard_True;

				Debug_If_Condition_Message(NOT scaleRepair->IsDone(), "the application is not performed");

				surface = scaleRepair->Reparameterized();

				geometry = surface->GeomSurface()->Geometry();

				wire = GModel_Tools::GetOuterParaWire(surface);
				box = GModel_Tools::CalcBoundingBox(*wire);

				pln = GModel_Tools::GetParaPlane(surface, tol);
			}
			else
			{
				pln = GModel_Tools::GetParaPlane(theSurface, tol);
			}
			auto sizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);

			auto metricFun = std::make_shared<GeoMetricFun2d_ExactSurface>(geometry, box);
			auto metricPrcsr = std::make_shared<Aft2d_MetricPrcsrSurface>(sizeFun, metricFun, theInfo);
			metricPrcsr->SetDimSize(box.Diameter());

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

			auto surfSizeFun = std::make_shared<GeoSizeFun2d_Surface>(geometry, theSizeFun, box);
			auto apprxMetricAlg = std::make_shared<Cad_ApprxMetric>(geometry, std::make_shared<Entity2d_Box>(box));
			apprxMetricAlg->OverrideInfo(myMetricApproxInfo);

			apprxMetricAlg->Perform();
			auto field = Cad_ApprxMetric::CalcDeterminants(apprxMetricAlg->Triangulation(), metricCalculator, geometry);
			//OFstream myFieldFile("metric_field.plt");
			//geoLib::ExportToPlt(*field, myFieldFile, "det");
			Standard_Real myMaxDet = 0;
			if (mySizeFun)
			{
				auto[maxDet, minDet] = Cad_Tools::CalcMaxMinMetrics(geometry, *apprxMetricAlg->Triangulation(), &calcSize);
				myMaxDet = maxDet;
			}
			else
			{
				auto[maxDet, minDet] = Cad_Tools::CalcMaxMinMetrics(geometry, *apprxMetricAlg->Triangulation());
				myMaxDet = maxDet;
			}
			for (auto& x : field->ValuesRef())
			{
				x /= myMaxDet;
			}
			//geoLib::ExportToPlt(*field, myFieldFile, "det1");
			//std::exit(1);
			auto colors = std::make_shared<Cad_ColorApprxMetric>();

			colors->SetCriterion(myDegenCrit);
			colors->SetMaxDet(myMaxDet);

			colors->LoadGeoemtry(geometry);
			colors->LoadApproximation(apprxMetricAlg->Triangulation());
			colors->LoadMetricCalculator(metricCalculator);

			colors->Perform();
			if (NOT colors->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}

			auto horizonAlg = std::make_shared<Cad_SingularityHorizons>();

			horizonAlg->SetDegeneracyCriterion(myDegenCrit);
			horizonAlg->SetMaxDet(myMaxDet);

			horizonAlg->LoadGeometry(geometry);
			horizonAlg->LoadApproximation(apprxMetricAlg->Triangulation());
			horizonAlg->LoadMetricCalculato(metricCalculator);

			horizonAlg->Perform();
			if (NOT horizonAlg->IsDone())
			{
				FatalErrorIn(FunctionSIG)
					<< "the application is not performed!" << endl
					<< abort(FatalError);
			}
			/*{
				auto approxInfo = std::make_shared<Geo_ApprxCurve_Info>();
				Cad_gApprxParaPlane approxAlg(pln, approxInfo);
				approxAlg.Perform();

				for (const auto& x : approxAlg.Polygons())
				{
					x->ExportToPlt(myFieldFile);
				}
				auto horizons = Cad_SingularityHorizons::RetrieveHorizons(*horizonAlg);
				for (const auto& x : horizons)
				{
					x->ExportToPlt(myFieldFile);
				}
			}
			std::exit(1);*/
			std::cout << "nb of horizons: " << horizonAlg->NbHorizons() << std::endl;
			if (horizonAlg->HasHorizon())
			{
				auto regionPln = Aft2d_gRegionPlaneSurface::MakePlane(pln);

				auto zonesAlg = std::make_shared<Cad_gSingularity>();

				zonesAlg->LoadColors(colors);
				zonesAlg->LoadHorizons(horizonAlg);
				zonesAlg->LoadSizeFun(surfSizeFun);

				zonesAlg->LoadParaPlane(regionPln);

				zonesAlg->SetWeight(mySingZoneWeight);
				std::cout << "zone alg..." << std::endl;
				PAUSE;
				zonesAlg->Perform();
				if (NOT zonesAlg->IsDone())
				{
					FatalErrorIn(FunctionSIG)
						<< "the application is not performed!" << endl
						<< abort(FatalError);
				}
				PAUSE;
				auto modifyAlg = std::make_shared<Cad_gModifySingularPlane>();

				modifyAlg->LoadColors(std::move(colors));
				modifyAlg->LoadZones(zonesAlg->Zones());
				modifyAlg->LoadPlane(regionPln);
				modifyAlg->LoadSurface(surface);
				modifyAlg->LoadApproxInfo(myCurveApproxInfo);

				modifyAlg->SetTolerance(myTol);

				modifyAlg->Perform();
				if (NOT modifyAlg->IsDone())
				{
					FatalErrorIn(FunctionSIG)
						<< "the application is not performed!" << endl
						<< abort(FatalError);
				}

				const auto& modifiedPlns = modifyAlg->ModifiedPlanes();
				//OFstream myFile("plane.plt");
				for (const auto& ip : modifiedPlns)
				{
					
					/*{
						auto orgPln = Aft2d_gRegionPlaneSurface::MakeOrignPlane<GModel_Plane>(ip);
						std::cout << "original" << std::endl;
						auto appxInfo = std::make_shared<Geo_ApprxCurve_Info>();
						Cad_gApprxParaPlane appxAlg(orgPln, appxInfo);
						appxAlg.Perform();

						const auto& polys = appxAlg.Polygons();
						std::cout << "nb of polys: " << polys.size() << std::endl;

						for (const auto& x : polys)
						{
							x->ExportToPlt(myFile);
						}
					}
					std::exit(1);*/
					auto bnd = std::make_shared<Aft2d_gBoundaryOfPlaneSurface>(theBndInfo);
					bnd->LoadMetricProcessor(metricPrcsr);
					bnd->LoadPlane(ip);

					theBndInfo->SetMergeTolerance(tol);  // added to adapt the merging tolerance [5/16/2022 Amir]

					bnd->Perform();
					if (NOT bnd->IsDone())
					{
						FatalErrorIn(FunctionSIG)
							<< "the application is not performed!" << endl
							<< abort(FatalError);
					}

					const auto& boundaries = bnd->Boundaries();
					
					/*{
						auto upBnds = Global_Tools::UpCast<Aft2d_gSegmentEdge, Aft2d_EdgeSurface>(boundaries);
						auto nodes = Aft_Tools::RetrieveNodes(upBnds);
						auto pts = Aft_Tools::RetrieveGeometry(nodes);
						auto inds = Aft_Tools::RetrieveEdgeConnectivities(upBnds);
						auto chain = Entity2d_Chain(std::move(pts), std::move(inds));
						auto mm = Geo_Tools::Triangulation(chain);

						file::SaveTo(mm, "boundaryMesh" + Entity2d_Triangulation::extension, 1);
						std::exit(0);
					}*/
					Aft_Tools::Connect(boundaries);

					auto elements = mesh(metricPrcsr, theCalculator, Aft_Tools::UpCast(boundaries));
					if (isTransf)
					{
						auto nodes = Aft_Tools::RetrieveNodes(elements);
						for (const auto& nd : nodes)
						{
							nd->Coord().Transform(trans);
						}
					}
					meshes.push_back(std::move(elements));
				}
				return std::move(meshes);
			}
			else
			{
				auto plnRegion = Aft2d_gRegionPlaneSurface::MakePlane(pln);

				auto bnd = std::make_shared<Aft2d_gBoundaryOfPlaneSurface>(theBndInfo);
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

				/*{
					auto upBnds = Global_Tools::UpCast<Aft2d_gSegmentEdge, Aft2d_EdgeSurface>(boundaries);
					auto nodes = Aft_Tools::RetrieveNodes(upBnds);
					auto pts = Aft_Tools::RetrieveGeometry(nodes);
					auto inds = Aft_Tools::RetrieveEdgeConnectivities(upBnds);
					auto chain = Entity2d_Chain(std::move(pts), std::move(inds));
					auto mm = Geo_Tools::Triangulation(chain);

					file::SaveTo(mm, "boundaryMesh" + Entity2d_Triangulation::extension, 1);
					std::exit(0);
				}*/

				Aft_Tools::Connect(boundaries);

				auto elements = mesh(metricPrcsr, theCalculator, Aft_Tools::UpCast(boundaries));
				if (isTransf)
				{
					auto nodes = Aft_Tools::RetrieveNodes(elements);
					for (const auto& nd : nodes)
					{
						nd->Coord().Transform(trans);
					}
				}

				meshes.push_back(std::move(elements));
				return std::move(meshes);
			}
		}
	}

	auto retrieveTris3d(const std::shared_ptr<GModel_Surface>& surface, const Entity2d_Triangulation& theTris)
	{
		auto tris3d = Cad_Tools::Triangulation(*surface->GeomSurface()->Geometry(), theTris);
		return std::move(tris3d);
	}

	auto createSamples()
	{
		std::shared_ptr<Geo2d_SamplePoints> samples;
		switch (mySampleType)
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
		auto alg = std::make_shared<cadLib::ApprxMetricCriterion_MinMax>(myMetricApproxTol, calc);
		alg->SetTolerance(0.2);
		return std::move(alg);
	}

	void execute()
	{
		Aft2d_gBoundaryOfPlaneSurface::verbose = 1;
		//Aft2d_gModelSurface::verbose = 1;

		if (NOT loadTag)
		{
			FatalErrorIn(FunctionSIG)
				<< "no file has been loaded!" << endl
				<< abort(FatalError);
		}

		const auto& model = mySoluData->Geometry();
		if (NOT model)
		{
			FatalErrorIn(FunctionSIG)
				<< "th model is null!" << endl
				<< abort(FatalError);
		}

		auto metricCalculator = createMetricCalculator();
		auto criterion = createCriterion(metricCalculator);
		auto samples = createSamples();

		myMaxLev = 7;

		myMetricApproxInfo = std::make_shared<Cad_ApprxMetricInfo>();
		myMetricApproxInfo->SetMinLevel(myMinLev);
		myMetricApproxInfo->SetMaxLevel(myMaxLev);
		myMetricApproxInfo->SetUnbalancing(myUnBalance);

		myMetricApproxInfo->MergeInfoRef().SetRadius(myRadius);
		myMetricApproxInfo->MergeInfoRef().SetResolution(myRes);

		myMetricApproxInfo->OverrideSamples(samples);
		myMetricApproxInfo->OverrideCriterion(criterion);

		const auto& sizeFun3d = mySoluData->SizeFun();

		auto integInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
		integInfo->SetMaxNbIterations(200);
		integInfo->SetNbInitIterations(4);
		integInfo->SetTolerance(1.0E-5);

		auto iterInfo = std::make_shared<Aft_SizeCorr_IterativeInfo>();
		iterInfo->SetIgnoreNonConvergency(Standard_True);
		iterInfo->SetMaxNbIters(40);  // default: 30 [5/24/2022 Amir]
		iterInfo->SetTolerance(1.0E-4);  // default: 1.0E-3 [5/24/2022 Amir]
		iterInfo->SetUnderRelaxation(0.95);  // default: 0.85 [5/24/2022 Amir]

		auto fracInfo = std::make_shared<Aft_SizeCorr_FractionInfo>();

		auto anIsoOptNodeInfo = std::make_shared<Aft2d_OptNodeAnIso_nonIterAdaptiveInfo>(iterInfo, fracInfo);
		auto anIsoOptNodeUniMetric = std::make_shared<Aft2d_OptNodeSurfaceUniMetric_nonIterAdaptive>(anIsoOptNodeInfo);
		//auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_nonIterAdaptive>(anIsoOptNodeInfo);

		/*auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_MetricCorr>();
		anIsoOptNode_altrAlg->SetIterInfo(iterInfo);
		anIsoOptNode_altrAlg->SetMaxLev(5);*/

		auto nelderInfo = std::make_shared<NumAlg_NelderMeadInfo>();
		nelderInfo->SetMaxNbIterations(50);
		nelderInfo->SetTolerance(1.0E-3);

		/*auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_NelderMead>();
		anIsoOptNode_altrAlg->SetInfo(nelderInfo);*/

		auto bisectInfo = std::make_shared<NumAlg_BisectionSolver_Info>();
		bisectInfo->SetDelta(1.0E-4);
		bisectInfo->SetTolerance(1.0E-4);
		bisectInfo->SetMaxIterations(20);

		auto anIsoOptNode_altrAlg = std::make_shared<Aft2d_AltrOptNodeSurface_SubTri>();
		anIsoOptNode_altrAlg->SetSizeCorrInfo(iterInfo);
		anIsoOptNode_altrAlg->SetNealderMeadInfo(nelderInfo);
		anIsoOptNode_altrAlg->SetMaxLev(3);

		auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_Altr>(anIsoOptNode_altrAlg, iterInfo);
		//auto anIsoOptNode = std::make_shared<Aft2d_OptNodeSurface_Standard>(iterInfo);

		auto metricPrcsrInfo = std::make_shared<Aft_MetricPrcsrAnIso_Info>();
		metricPrcsrInfo->SetNbIters(5);  // default: 5 [5/24/2022 Amir]
		metricPrcsrInfo->SetNbSamples(3);  // default: 3 [5/24/2022 Amir]
		metricPrcsrInfo->SetTolerance(0.001);  // default: 0.0025 [5/24/2022 Amir]
		metricPrcsrInfo->OverrideIntegInfo(integInfo);
		
		//mySoluData->GlobalCurveInfo()->NewtonIterInfo()->SetMaxIterations(150);
		//mySoluData->GlobalCurveInfo()->NewtonIterInfo()->SetUnderRelaxation(0.85);
		//mySoluData->GlobalCurveInfo()->NewtonIterInfo()->SetTolerance(0.0005);
		//mySoluData->GlobalCurveInfo()->SetIgnoreNonConvergency(Standard_True);
		mySoluData->GlobalCurveInfo()->CorrAlgInfo()->SetMaxLevel(30);
		auto bndInfo = std::make_shared<Aft2d_BoundaryOfPlaneAnIso_Info>();
		bndInfo->SetOverrideInfo(Standard_False);
		bndInfo->OverrideGlobalCurve(mySoluData->GlobalCurveInfo());
		bndInfo->SetMergeTolerance(1.0E-6);
		bndInfo->OverrideGlobalMetricPrcsr(metricPrcsrInfo);
		
		mySoluData->TrisRef().clear();

		std::vector<std::shared_ptr<GModel_Surface>> triSurfaces;
		Standard_Integer nbSurfaces = 0;
		for (const auto& x : model->Surfaces())
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

		for (const auto& x : triSurfaces)
		{
			Debug_Null_Pointer(x);
			if (verbose)
			{
				Info << endl
					<< "- meshing surface, " << x->Index() << endl;
			}
			/*if (x->Index() NOT_EQUAL 1)
			{
				continue;
			}*/
			/*if (x->Index() IS_EQUAL 13)
			{
				continue;
			}
			if (x->Index() IS_EQUAL 31)
			{
				continue;
			}
			if (x->Index() IS_EQUAL 32)
			{
				continue;
			}
			if (x->Index() IS_EQUAL 44)
			{
				continue;
			}*/
			/*if (x->Index() > 24)
			{
				continue;
			}*/

			const TopoDS_Face& face = x->Face();

			/*auto ff = GModel_Tools::GetSurface(face);
			std::exit(1);*/
\
			try
			{
				auto plnMesh = mesh(x, sizeFun3d, anIsoOptNodeUniMetric, anIsoOptNode, bndInfo, metricPrcsrInfo);
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
					Global_Tools::Insert(x->Index(), tris3d, mySoluData->TrisRef());
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
					std::cout << " - nb. of elements: " << tris3d->NbConnectivity() << std::endl;
					Global_Tools::Insert(x->Index(), tris3d, mySoluData->TrisRef());
				}
			}
			catch (const error& x)
			{
				std::cout << x.message() << std::endl;
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
		mod->add(chaiscript::fun([](const std::string& name)-> void {saveTo(name); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {saveTo(); }), "saveTo");
		mod->add(chaiscript::fun([]()-> void {loadFile(); }), "loadFile");
		mod->add(chaiscript::fun([](const std::string& name)-> void {loadFile(name); }), "loadFile");

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

int main(int argc, char *argv[])
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
			Info << " This application is aimed to create plane boundary info." << endl << endl;
			Info << endl
				<< " Function list:" << endl << endl

				<< " # IO functions: " << endl << endl

				<< " - loadFile(name [optional])" << endl
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
				fileName myFileName(file::GetSystemFile("tnbMeshgSurfAft"));

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